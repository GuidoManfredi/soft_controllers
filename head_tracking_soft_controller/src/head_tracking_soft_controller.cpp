#include "head_tracking_soft_controller/head_tracking_soft_controller.h"
#include <sstream>
#include <pluginlib/class_list_macros.h>

// Register controller to pluginlib
PLUGINLIB_DECLARE_CLASS(head_tracking_soft_controller,HeadTrackingSoftController, controller::HeadTrackingSoftController, pr2_controller_interface::Controller)

namespace controller {

HeadTrackingSoftController::HeadTrackingSoftController()
  : loop_count_(0), robot_(NULL)
{

}

HeadTrackingSoftController::~HeadTrackingSoftController()
{
  commandSub_.shutdown();
  timeScaleSub_.shutdown();
  queryStateService_.shutdown();
}

void HeadTrackingSoftController::commandCB(const head_tracking_soft_controller::PanTiltConstPtr& command)
{
  boost::shared_ptr<SM_TRAJ> newMotionPtr(new SM_TRAJ);
  SM_TRAJ &newMotion = *newMotionPtr; 

  for (size_t i = 0; i < joints_.size(); ++i)
  {
    ic_[i].a = lastAcc_[i];       
    ic_[i].v = lastVel_[i];       
    ic_[i].x = joints_[i]->position_; 

    fc_[i].a = 0.0;
    fc_[i].v = 0.0;
    fc_[i].x = command->data[i];  
  }

  newMotion.computeTraj(ic_, fc_, limits_, SM_TRAJ::SM_INDEPENDANT);

  if(newMotion.traj.empty()){
    ROS_WARN("Controller computed empty trajectory");
    starting();
    return;
  }

  current_trajectory_box_.set(newMotionPtr);
  //set timeFromStart to 0 once the trajectory has been changed
  timeFromStart_ = 0.0;

  inhibitionPoints_ = 2;

  std_msgs::Float64 zero;
  zero.data = 0.0;
  inhibitionPub_.publish(zero);
}

void HeadTrackingSoftController::timeScaleCB(const std_msgs::Float64ConstPtr& msg)
{
  timeScale_ = msg->data;
}

void HeadTrackingSoftController::inhibitionCB(const std_msgs::Float64ConstPtr& inhibitionPoints)
{
  --inhibitionPoints_;
}

// Controller initialization in non-realtime
bool HeadTrackingSoftController::init(pr2_mechanism_model::RobotState *robot,
                            ros::NodeHandle &n)
{
  using namespace XmlRpc;
  node_ = n;
  robot_ = robot;

  /************************************** Gets all of the joints ******************************/ 
  XmlRpc::XmlRpcValue joint_names;
  if (!node_.getParam("joints", joint_names))
  {
    ROS_ERROR("No joints given. (namespace: %s)", node_.getNamespace().c_str());
    return false;
  }
  if (joint_names.getType() != XmlRpc::XmlRpcValue::TypeArray)
  {
    ROS_ERROR("Malformed joint specification.  (namespace: %s)", node_.getNamespace().c_str());
    return false;
  }
  for (int i = 0; i < joint_names.size(); ++i)
  {
    XmlRpcValue &name_value = joint_names[i];
    if (name_value.getType() != XmlRpcValue::TypeString)
    {
      ROS_ERROR("Array of joint names should contain all strings.  (namespace: %s)",
                node_.getNamespace().c_str());
      return false;
    }

    pr2_mechanism_model::JointState *j = robot->getJointState((std::string)name_value);
    if (!j) {
      ROS_ERROR("Joint not found: %s. (namespace: %s)",
                ((std::string)name_value).c_str(), node_.getNamespace().c_str());
      return false;
    }
    joints_.push_back(j);
  }
  /********************************************************************************************/



  /******************* Ensures that all the joints are calibrated. ****************************/
  
  for (size_t i = 0; i < joints_.size(); ++i)
  {
    if (!joints_[i]->calibrated_)
    {
      ROS_ERROR("Joint %s was not calibrated (namespace: %s)",
                joints_[i]->joint_->name.c_str(), node_.getNamespace().c_str());
      return false;
    }
  }
  
  /********************************************************************************************/


  /***************************** Sets up pid controllers for all of the joints ****************/
  
  std::string gains_ns;
  if (!node_.getParam("gains", gains_ns))
    gains_ns = node_.getNamespace() + "/gains";
  pids_.resize(joints_.size());
  for (size_t i = 0; i < joints_.size(); ++i)
    if (!pids_[i].init(ros::NodeHandle(gains_ns + "/" + joints_[i]->joint_->name)))
      return false;
  
  /********************************************************************************************/


  /******************************* Allocate space *********************************/
  
  q.resize(joints_.size());
  qd.resize(joints_.size());
  qdd.resize(joints_.size());

  ic_.resize(joints_.size());
  fc_.resize(joints_.size());

  controller_state_publisher_.reset(
    new realtime_tools::RealtimePublisher<pr2_controllers_msgs::JointTrajectoryControllerState>
    (node_, "state", 1));
  controller_state_publisher_->lock();
  for (size_t j = 0; j < joints_.size(); ++j)
    controller_state_publisher_->msg_.joint_names.push_back(joints_[j]->joint_->name);
  controller_state_publisher_->msg_.desired.positions.resize(joints_.size());
  controller_state_publisher_->msg_.desired.velocities.resize(joints_.size());
  controller_state_publisher_->msg_.desired.accelerations.resize(joints_.size());
  controller_state_publisher_->msg_.actual.positions.resize(joints_.size());
  controller_state_publisher_->msg_.actual.velocities.resize(joints_.size());
  controller_state_publisher_->msg_.error.positions.resize(joints_.size());
  controller_state_publisher_->msg_.error.velocities.resize(joints_.size());
  controller_state_publisher_->unlock();
  
  /********************************************************************************************/

/********************************* Connexion to trajectory and timescale topics ***************/

  commandSub_= node_.subscribe<head_tracking_soft_controller::PanTilt>("command", 1, &HeadTrackingSoftController::commandCB, this);
  inhibitionSub_ = node_.subscribe<std_msgs::Float64>("/controllers_inhibition", 1, &HeadTrackingSoftController::inhibitionCB, this);
  inhibitionPub_ = node_.advertise<std_msgs::Float64>("/controllers_inhibition", 1);
 
  SM_LIMITS tmpLim;
  for(size_t j = 0; j < joints_.size(); ++j)
  {
    tmpLim.maxJerk= 9; //60;//0.6;
    tmpLim.maxAcc= 1; //20;//0.2;
    tmpLim.maxVel= 1; //1;//0.3; // max 6
    limits_.push_back(tmpLim);
  }

  timescaleLimits_.maxJerk = 9;
  timescaleLimits_.maxAcc = 3;
  timescaleLimits_.maxVel = 1;

  lastAcc_.resize(joints_.size());
  lastVel_.resize(joints_.size());
  /********************************************************************************************/

  timeScale_ = 1.0;
  timeFromStart_ = 0.0;
  inhibitionPoints_= 0;

  timeScaleCond_.x= 1;
  timeScaleCond_.v= timeScale_;
  timeScaleCond_.a= 0;


  return true;
}


// Controller startup in realtime
void HeadTrackingSoftController::starting()
{
  boost::shared_ptr<SM_TRAJ> newMotionPtr(new SM_TRAJ);
  SM_TRAJ &newMotion = *newMotionPtr;

  last_time_ = robot_->getTime();

  for (size_t i = 0; i < pids_.size(); ++i)
    pids_[i].reset();

  // Hold position
  for (size_t i = 0; i < joints_.size(); ++i)
  {
    ic_[i].a = lastAcc_[i];
    ic_[i].v = lastVel_[i];
    ic_[i].x = joints_[i]->position_;

    fc_[i].a = 0.0;
    fc_[i].v = 0.0;
    fc_[i].x = joints_[i]->position_;
  }

  newMotion.computeTraj(ic_, fc_, limits_, SM_TRAJ::SM_INDEPENDANT);
 
  current_trajectory_box_.set(newMotionPtr);
}


// Controller update loop in realtime
void HeadTrackingSoftController::update(){
//Calculating time since last update
ros::Time time = robot_->getTime();
ros::Duration dt = time - last_time_;
last_time_ = time;

if(inhibitionPoints_ > 0){

  boost::shared_ptr<SM_TRAJ> newMotion; 
  current_trajectory_box_.get(newMotion);
  if (!newMotion)
    ROS_FATAL("The current trajectory can never be null");

  // only beause they do so in ros controllers
  SM_TRAJ &currentMotion= *newMotion;

  std::vector<SM_COND> cond;

  /************************** Soft motion part ***************************************/

  // TODO replace limits_[0] 
  sm_ComputeSmoothedStepVel(timeScale_, dt.toSec(), timescaleLimits_, &timeScaleCond_);

  //Calculating current time since trajectory started
  timeFromStart_ += dt.toSec()*timeScaleCond_.v; 

  if (timeFromStart_ < 0)
  {
    timeFromStart_ = 0;
    currentMotion.getMotionCond(0.0, cond);
    for (size_t i = 0; i < joints_.size(); ++i) {
      q[i] = cond[i].x;
      qd[i] = 0;
      qdd[i] = 0;
      lastVel_[i] = 0;
      lastAcc_[i] = 0;
    }
  }
  else if (timeFromStart_ >= currentMotion.getDuration())
  {
    //time is blocked to the trajectory end time
    timeFromStart_ = currentMotion.getDuration();
    currentMotion.getMotionCond(timeFromStart_, cond);
    for (size_t i = 0; i < joints_.size(); ++i) {
      q[i] = cond[i].x;
      qd[i] = 0;
      qdd[i] = 0;
      lastVel_[i] = 0;
      lastAcc_[i] = 0;
    }
  }
  else
  {
    currentMotion.getMotionCond(timeFromStart_, cond);
    for (size_t i = 0; i < joints_.size(); ++i) {
      q[i] = cond[i].x;
      qd[i] = cond[i].v;
      qdd[i] = cond[i].a;
      lastVel_[i] = cond[i].v;
      lastAcc_[i] = cond[i].a;
    }
  }


  /********************************************************************************************/

  // ------ Trajectory Following
  std::vector<double> error(joints_.size());
  for (size_t i = 0; i < joints_.size(); ++i)
  {
    error[i] = joints_[i]->position_ - q[i];
    joints_[i]->commanded_effort_ += pids_[i].updatePid(error[i], joints_[i]->velocity_ - qd[i], dt);
  }

  // ------ State publishing
  if (loop_count_ % 10 == 0)
  {
    if (controller_state_publisher_ && controller_state_publisher_->trylock())
    {
      controller_state_publisher_->msg_.header.stamp = time;
      for (size_t j = 0; j < joints_.size(); ++j)
      {
        controller_state_publisher_->msg_.desired.positions[j] = q[j];
        controller_state_publisher_->msg_.desired.velocities[j] = qd[j];
        controller_state_publisher_->msg_.desired.accelerations[j] = qdd[j];
        controller_state_publisher_->msg_.actual.positions[j] = joints_[j]->position_;
        controller_state_publisher_->msg_.actual.velocities[j] = joints_[j]->velocity_;
        controller_state_publisher_->msg_.actual.time_from_start= ros::Duration(timeFromStart_);
        controller_state_publisher_->msg_.error.positions[j] = error[j];
        controller_state_publisher_->msg_.error.velocities[j] = joints_[j]->velocity_ - qd[j];
      }
      controller_state_publisher_->unlockAndPublish();
    }
  }

  ++loop_count_;

}
}
}
