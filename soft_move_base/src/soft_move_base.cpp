//Action server includes
#include <ros/ros.h>
#include <actionlib/server/simple_action_server.h>
#include <soft_move_base/SoftMoveBaseAction.h>
//Move forward includes
#include <geometry_msgs/Twist.h>
#include <std_msgs/Float64.h>
#include <tf/transform_listener.h>

#include "softMotion/softMotion.h"
#include "softMotion/Sm_Traj.h"
#include "softMotion/softMotionStruct.h"
#include "softMotion/softMotionStructGenom.h"
#include "pr2_soft_controller/SM_TRAJ_STR_ROS.h"

#include <vector>

class SoftMoveBaseAction
{
protected:

  ros::NodeHandle nh_;
  actionlib::SimpleActionServer<soft_move_base::SoftMoveBaseAction> as_;
  std::string action_name_;
  // We will be publishing to the "cmd_vel" topic to issue commands
  ros::Publisher cmd_vel_pub;
  // We will be listening to TF transforms as well
  tf::TransformListener _listener;
  //we will record transforms here
  tf::StampedTransform world_transform;

  // the main traj container
  SM_TRAJ _newTraj;
  // time elapsed from the trajectory start
  double _timeFromStart;
  double _tmpTimeFromStart;
  double _timer;
  // time step on the main trajectory
  double _dt;
  //double _tmpTrajDt;
  // tolerance regarding the final position
  double _tolerance[3];
  
  // A cond is a set of joints with, for each
  // joint a position, a velocity and an acceleration. 

  // the next position of the robot along the main traj
  // (in world frame)
  std::vector<SM_COND> _nextRobotCond_w; 
  // the next cond of the robot along the main traj
  // (in robot frame)
  std::vector<SM_COND> _nextRobotCond_r;
  // the current cond of the robot (in robot frame)
  std::vector<SM_COND> _currRobotCond_r;
  // the new cond to send to the robot 
  std::vector<SM_COND> _newRobotCond_r;
  // the last velocities for the 6 dofs
  double _lastVel[6];
  // the last accelerations for the 6 dofs
  double _lastAcc[6];
  // Limits for velocity, acceleration and jerk
  SM_LIMITS limit;
  std::vector<SM_LIMITS> limits;
  ros::Subscriber timeScaleSub_;
  double timeScale_;

public:

  /**
   * @brief This action server uses the softMotion-libs to move the robot
   *        along a main trajectory described in its goal.
   *        It correct errors by computing small trajectories to correct
   *        its motion and stick to the main trajectory.
  **/
  SoftMoveBaseAction(std::string name) :
    as_(nh_, name, boost::bind(&SoftMoveBaseAction::executeCB, this, _1), false),
    action_name_(name)
  {
    as_.start();
    _dt = 0.1;
    //_tmpTrajDt = 1.0;
    _timeFromStart = 0;
    _tmpTimeFromStart = 0;
    _timer = 0;
    _tolerance[0] = 0.01;
    _tolerance[1] = 0.01;
    _tolerance[2] = 0.5;
    // last velocity and acceleration sent init
    for(int i =0; i<6; ++i)
    {
      _lastVel[i] = 0.0;
      _lastAcc[i] = 0.0;
    }

    _nextRobotCond_r.resize(6);
    _newRobotCond_r.resize(6);
    _currRobotCond_r.resize(6);

    // initialize the limits, there are updated for 
    // each new received trajectory
    for(int i=0; i<6; ++i)
    {
      limit.maxJerk = 0.9;
      limit.maxAcc =  0.3;
      limit.maxVel =  0.6;
      limits.push_back(limit);
    }

    //wait for the listener to get the first message
    _listener.waitForTransform("map", "base_footprint", 
                               ros::Time(0), ros::Duration(1.0));

    //set up the publisher for the cmd_vel topic
    cmd_vel_pub = nh_.advertise<geometry_msgs::Twist>("base_controller/command", 1);
  
    timeScaleSub_ = nh_.subscribe<std_msgs::Float64>("soft_move_base/timescale", 1, &SoftMoveBaseAction::timeScaleCB, this);
    timeScale_ = 1;

    ROS_INFO("soft_move_base action server up and ready");
  }

  ~SoftMoveBaseAction(void)
  {
  }

  int executeCB(const soft_move_base::SoftMoveBaseGoalConstPtr &goal)
  {
    ROS_INFO("Received new trajectory");
    SM_TRAJ tmpTraj;
    ros::Rate _loop_rate(1/_dt);
    _timeFromStart= 0;
    _tmpTimeFromStart= 0;
    _timer = 0;
    loadNewTraj(goal->traj); 
    double duration = 0.0;
    duration =  _newTraj.getDuration();


    limits.clear();
    for(int i=0; i<6; ++i)
    {
      limit.maxJerk = _newTraj.jmax[i] * 1.1;
      limit.maxAcc =  _newTraj.amax[i] * 1.1;
      limit.maxVel =  _newTraj.vmax[i] * 1.1;
      limits.push_back(limit);
    }

    //double t = 0;
    //FILE* file;
    //file  = fopen("baseExperiment.dat", "w");


   bool cont = true;
   do {
     // end if goal canceled
     if( as_.isPreemptRequested())
		break;

     getNextRobotCond(_timeFromStart + _dt);
     //printCond(_nextRobotCond_w);

     getPoseInRobotFrame(_nextRobotCond_w);
     //printCond(_nextRobotCond_r);

     _currRobotCond_r[0].x = 0;
     _currRobotCond_r[0].v = _lastVel[0];
     _currRobotCond_r[0].a = _lastAcc[0];
     _currRobotCond_r[1].x = 0;
     _currRobotCond_r[1].v = _lastVel[1];
     _currRobotCond_r[1].a = _lastAcc[1];
     _currRobotCond_r[5].x = 0;
     _currRobotCond_r[5].v = _lastVel[5];
     _currRobotCond_r[5].a = _lastAcc[5];
     //printCond(_currRobotCond_r);

     ROS_INFO("TMP TIME:%f", _tmpTimeFromStart);

     if( _timeFromStart == 0.0) 
     {
       //correction
       tmpTraj.clear(); 

       boundsCond(_currRobotCond_r);
       boundsCond(_nextRobotCond_r);
       tmpTraj.computeTraj(_currRobotCond_r, _nextRobotCond_r, limits, SM_TRAJ::SM_INDEPENDANT);
  
       _tmpTimeFromStart = _dt;
       //printCond( _newRobotCond_r);
     }
     else if(_timer - 0.5 >= 0.0001 
            || _tmpTimeFromStart > tmpTraj.getDuration())
     {
       _timer = 0;

       //correction
       tmpTraj.clear(); 
       tmpTraj.computeTraj(_currRobotCond_r, _nextRobotCond_r, limits, SM_TRAJ::SM_INDEPENDANT);
  
       _tmpTimeFromStart = _dt;
     }

     tmpTraj.getMotionCond(_tmpTimeFromStart,_newRobotCond_r);
     _lastVel[0]= _newRobotCond_r[0].v;
     _lastVel[1]= _newRobotCond_r[1].v;
     _lastVel[5]= _newRobotCond_r[5].v;
     _lastAcc[0]= _newRobotCond_r[0].a;
     _lastAcc[1]= _newRobotCond_r[1].a;
     _lastAcc[5]= _newRobotCond_r[5].a;

     //printCond(_newRobotCond_r);
    
     publishNewCond(_newRobotCond_r);

     _timeFromStart += _dt;
     _tmpTimeFromStart += _dt;
     _timer += _dt;
     if(_timeFromStart > _newTraj.getDuration())
       _timeFromStart = _newTraj.getDuration();

     _loop_rate.sleep();

     if(_timeFromStart >= _newTraj.getDuration())
     {
       cont = fabs(_newRobotCond_r[0].x) > _tolerance[0]
              || fabs(_newRobotCond_r[1].x) > _tolerance[1]
              || fabs(_newRobotCond_r[5].x) > _tolerance[2];
     }
     
     ros::spinOnce();
     
   } while(cont);

    soft_move_base::SoftMoveBaseResult result;
    result.result = true;
    as_.setSucceeded(result);

    return 0;
  } 
  
  void loadNewTraj(const pr2_soft_controller::SM_TRAJ_STR_ROS& msg)
  {
    SM_TRAJ_STR tmpTraj;

    //copy of the msg in a softmotion structure
    tmpTraj.trajId= msg.trajId;
    tmpTraj.nbAxis= msg.nbAxis;
    //tmpTraj.timePreserved= msg.timePreserved;
    for(size_t i=0; i<(unsigned int)msg.nbAxis; ++i){
      tmpTraj.qStart[i] = msg.qStart[i];
      tmpTraj.qGoal[i] = msg.qGoal[i];
      tmpTraj.jmax[i] = msg.jmax[i];
      tmpTraj.amax[i] = msg.amax[i];
      tmpTraj.vmax[i] = msg.vmax[i];
      tmpTraj.traj[i].nbSeg= msg.traj[i].nbSeg;
      tmpTraj.traj[i].unsused= msg.traj[i].unsused;
      for(size_t j=0; j<(unsigned int)msg.traj[i].nbSeg; ++j){
        tmpTraj.traj[i].seg[j].lpId= msg.traj[i].seg[j].lpId;
        tmpTraj.traj[i].seg[j].unused= msg.traj[i].seg[j].unused;
        tmpTraj.traj[i].seg[j].timeOnTraj= msg.traj[i].seg[j].timeOnTraj;
        tmpTraj.traj[i].seg[j].time= msg.traj[i].seg[j].time;
        tmpTraj.traj[i].seg[j].ic_a= msg.traj[i].seg[j].ic_a;
        tmpTraj.traj[i].seg[j].ic_v= msg.traj[i].seg[j].ic_v;
        tmpTraj.traj[i].seg[j].ic_x= msg.traj[i].seg[j].ic_x;
        tmpTraj.traj[i].seg[j].jerk= msg.traj[i].seg[j].jerk;
      }
    }

    _newTraj.importFromSM_TRAJ_STR( &tmpTraj );
  }

  void getNextRobotCond(double time)
  {
    _newTraj.getMotionCond(time, _nextRobotCond_w);
  }

  void getPoseInRobotFrame(std::vector<SM_COND> nextRobotCond_w)
  { 
    //transforming position into robot frame
    geometry_msgs::PoseStamped goal;
    geometry_msgs::PoseStamped yawMapRobot;
    geometry_msgs::PoseStamped goalRobotFrame;

    // position
    goal.header.stamp= ros::Time(0);
    goal.header.frame_id= "map";
    goal.pose.position.x= nextRobotCond_w[0].x;
    goal.pose.position.y= nextRobotCond_w[1].x;
    goal.pose.position.z= 0.0;
    tf::Quaternion q = tf::createQuaternionFromRPY(0.0,0.0,nextRobotCond_w[5].x);
    tf::quaternionTFToMsg(q,goal.pose.orientation);
    
    _listener.waitForTransform("base_footprint", "map",
                               ros::Time(0), ros::Duration(1.0));
    _listener.transformPose("base_footprint", goal, goalRobotFrame); 
  
    _nextRobotCond_r[0].x = goalRobotFrame.pose.position.x;
    _nextRobotCond_r[1].x = goalRobotFrame.pose.position.y; 
    _nextRobotCond_r[5].x = tf::getYaw(goalRobotFrame.pose.orientation);

    // velocity and acceleration
    //record the starting transform from the odometry to the base frame
    _listener.lookupTransform("map", "base_footprint",
                              ros::Time(0), world_transform);
    
    double roll, pitch, yaw;
    q = world_transform.getRotation();
    btMatrix3x3(q).getRPY(roll, pitch, yaw);

    _nextRobotCond_r[0].v = cos(yaw)*nextRobotCond_w[0].v + sin(yaw)*nextRobotCond_w[1].v;
    _nextRobotCond_r[1].v = -sin(yaw)*nextRobotCond_w[0].v + cos(yaw)*nextRobotCond_w[1].v; 
    _nextRobotCond_r[5].v = nextRobotCond_w[5].v;

    _nextRobotCond_r[0].a = cos(yaw)*nextRobotCond_w[0].a + sin(yaw)*nextRobotCond_w[1].a;
    _nextRobotCond_r[1].a = -sin(yaw)*nextRobotCond_w[0].a + cos(yaw)*nextRobotCond_w[1].a;
    _nextRobotCond_r[5].a = nextRobotCond_w[5].a;
    
  }

  void publishNewCond(std::vector<SM_COND> nextRobotCond_r)
  {
    geometry_msgs::Twist cmd;
    cmd.linear.x= nextRobotCond_r[0].v;
    cmd.linear.y= nextRobotCond_r[1].v;
    cmd.linear.z= 0;
    cmd.angular.x= 0;
    cmd.angular.y= 0;
    cmd.angular.z= nextRobotCond_r[5].v;
    cmd_vel_pub.publish(cmd);
  }

  void printCond(std::vector<SM_COND> cond)
  {
    ROS_INFO("POSE: %f %f %f", cond[0].x, cond[1].x, cond[5].x);
    ROS_INFO("VEL: %f %f %f", cond[0].v, cond[1].v, cond[5].v);
    ROS_INFO("ACC: %f %f %f", cond[0].a, cond[1].a, cond[5].a);
  }

  void timeScaleCB(const std_msgs::Float64ConstPtr& msg)
  {
    timeScale_ = msg->data;
  }

  void boundsCond(std::vector<SM_COND> &cond) 
  {
    for(unsigned int i=0; i< cond.size(); i++){
      if(fabs(cond[i].a) > limits[i].maxAcc) {
	cond[i].a = sign(cond[i].a) *  limits[i].maxAcc; 
      }
      if(fabs(cond[i].v) > limits[i].maxVel) {
	cond[i].v = sign(cond[i].v) *  limits[i].maxVel; 
      }
    }
  }
  int sign(double v)
  {
    return v > 0 ? 1 : (v < 0 ? -1 : 0);
  }
};

int main(int argc, char** argv)
{
  ros::init(argc, argv, "soft_move_base");

  SoftMoveBaseAction softmotion(ros::this_node::getName());
  ros::spin();

  return 0;
}

