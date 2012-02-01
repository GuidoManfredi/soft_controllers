#include "pr2_soft_controller/pr2_soft_controller.h"
#include <sstream>
#include <pluginlib/class_list_macros.h>


// Register controller to pluginlib
PLUGINLIB_DECLARE_CLASS(pr2_soft_controller,Pr2SoftController, controller::Pr2SoftController, pr2_controller_interface::Controller)

namespace controller {

Pr2SoftController::Pr2SoftController()
  : loop_count_(0), robot_(NULL)
{

}

Pr2SoftController::~Pr2SoftController()
{
  commandSub_.shutdown();
  accTreshSub_.shutdown();
  timeScaleSub_.shutdown();
}

void Pr2SoftController::commandCB(const pr2_soft_controller::SM_TRAJ_STR_ROSConstPtr& msg)
{
  boost::shared_ptr<SM_TRAJ> newMotionPtr(new SM_TRAJ);
  SM_TRAJ &newMotion = *newMotionPtr;

  SM_TRAJ_STR tmpTraj;

  //copy of the msg in a softmotion structure
  tmpTraj.trajId= msg->trajId;
  tmpTraj.nbAxis= msg->nbAxis;
  tmpTraj.timePreserved= msg->timePreserved;
  for(size_t i=0; i<(unsigned int)msg->nbAxis; ++i){
    tmpTraj.qStart[i] = msg->qStart[i];
    tmpTraj.qGoal[i] = msg->qGoal[i];
    tmpTraj.jmax[i] = msg->jmax[i];
    tmpTraj.amax[i] = msg->amax[i];
    tmpTraj.vmax[i] = msg->vmax[i];
    tmpTraj.traj[i].nbSeg= msg->traj[i].nbSeg;
    tmpTraj.traj[i].unsused= msg->traj[i].unsused;
    for(size_t j=0; j<(unsigned int)msg->traj[i].nbSeg; ++j){
      tmpTraj.traj[i].seg[j].lpId= msg->traj[i].seg[j].lpId;
      tmpTraj.traj[i].seg[j].unused= msg->traj[i].seg[j].unused;
      tmpTraj.traj[i].seg[j].timeOnTraj= msg->traj[i].seg[j].timeOnTraj;
      tmpTraj.traj[i].seg[j].time= msg->traj[i].seg[j].time;
      tmpTraj.traj[i].seg[j].ic_a= msg->traj[i].seg[j].ic_a;
      tmpTraj.traj[i].seg[j].ic_v= msg->traj[i].seg[j].ic_v;
      tmpTraj.traj[i].seg[j].ic_x= msg->traj[i].seg[j].ic_x;
      tmpTraj.traj[i].seg[j].jerk= msg->traj[i].seg[j].jerk;
    }
  }

  newMotion.importFromSM_TRAJ_STR( &tmpTraj );
  current_trajectory_box_.set( newMotionPtr );

  //check if trajectory is empty. If so, go to hold position
  if (newMotion.traj.empty()){
    ROS_WARN("Controller received empty trajectory");
    starting();
    return;
  }
	
  timeFromStart_ = 0.0;
  timeScale_ = 1;
}

void Pr2SoftController::timeScaleCB(const std_msgs::Float64ConstPtr& msg)
{
  timeScale_ = msg->data;
}

// Controller initialization in non-realtime
bool Pr2SoftController::init(pr2_mechanism_model::RobotState *robot,
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

  commandSub_= node_.subscribe<pr2_soft_controller::SM_TRAJ_STR_ROS>("command", 1, &Pr2SoftController::commandCB, this);
  timeScaleSub_ = node_.subscribe<std_msgs::Float64>("timescale", 1, &Pr2SoftController::timeScaleCB, this);

  //creating hold trajectory
  holdTraj_.trajId= -1;
  holdTraj_.nbAxis= joints_.size();
  holdTraj_.timePreserved= 0;
  for(size_t i=0; i<joints_.size(); ++i){
    holdTraj_.qStart[i] = joints_[i]->position_;
    holdTraj_.qGoal[i] = joints_[i]->position_;
    holdTraj_.traj[i].nbSeg= 1;
    holdTraj_.traj[i].unsused= 0;
    for(size_t j=0; j<(size_t)holdTraj_.traj[i].nbSeg; ++j){
      holdTraj_.traj[i].seg[0].lpId= 0;
      holdTraj_.traj[i].seg[0].unused= 0;
      holdTraj_.traj[i].seg[0].timeOnTraj= 0;
      holdTraj_.traj[i].seg[0].time= 69;
      holdTraj_.traj[i].seg[0].ic_a= 0;
      holdTraj_.traj[i].seg[0].ic_v= 0;
      holdTraj_.traj[i].seg[0].ic_x= joints_[i]->position_;
      holdTraj_.traj[i].seg[0].jerk= 0;
    }
  }

  timeScale_ = 1;

  timeScaleCond_.x= 1;
  timeScaleCond_.v= timeScale_;
  timeScaleCond_.a= 0;

  // in order for softmotion to work correctly, the following inequality must remain true:
  // maxVel/maxAcc = maxAcc/maxJerk
  limits_.maxJerk= 9;
  limits_.maxAcc= 3;
  limits_.maxVel= 1;

  /********************************************************************************************/

  timeFromStart_ = 0.0;

  return true;
}


// Controller startup in realtime
void Pr2SoftController::starting()
{
  boost::shared_ptr<SM_TRAJ> newMotionPtr(new SM_TRAJ);
  SM_TRAJ &newMotion = *newMotionPtr;

  last_time_ = robot_->getTime();

  for (size_t i = 0; i < pids_.size(); ++i)
    pids_[i].reset();

  // Updating hold trajectory.
  for(size_t i=0; i<joints_.size(); ++i){
    holdTraj_.qStart[i] = joints_[i]->position_;
    holdTraj_.qGoal[i] = joints_[i]->position_;
    for(size_t j=0; j<(size_t)holdTraj_.traj[i].nbSeg; ++j){
      holdTraj_.traj[i].seg[0].ic_x= joints_[i]->position_;
    }
  }

  newMotion.importFromSM_TRAJ_STR( &holdTraj_ );
	
  current_trajectory_box_.set(newMotionPtr);
}


// Controller update loop in realtime
void Pr2SoftController::update()
{
  boost::shared_ptr<SM_TRAJ> newMotion;
  current_trajectory_box_.get(newMotion);

  if (!newMotion)
    ROS_FATAL("The current trajectory can never be null");

  // only beause they do so in ros controllers
  SM_TRAJ &currentMotion= *newMotion;

  std::vector<SM_COND> cond;

  //Calculating time since last update
  ros::Time time = robot_->getTime();
  ros::Duration dt = time - last_time_;
  last_time_ = time;

  /************************** Soft motion part ***************************************/
  // Time smoother, takes time speed, tic, limits and returns conditions.
  sm_ComputeSmoothedStepVel(timeScale_, dt.toSec(), limits_, &timeScaleCond_);

  timeFromStart_ += dt.toSec()*timeScaleCond_.v;

  if (timeFromStart_ < 0)
  {
    timeFromStart_ = 0;
    currentMotion.getMotionCond(0.0, cond);
    for (size_t i = 0; i < joints_.size(); ++i) {
      q[i] = cond[i].x;
      qd[i] = 0;
      qdd[i] = 0;
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
    }
  }
  else
  {
    currentMotion.getMotionCond(timeFromStart_, cond);
    for (size_t i = 0; i < joints_.size(); ++i) {
      q[i] = cond[i].x;
      qd[i] = cond[i].v;
      qdd[i] = cond[i].a;
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

