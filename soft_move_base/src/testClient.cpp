#include <ros/ros.h>
#include <actionlib/client/simple_action_client.h>
#include <actionlib/client/terminal_state.h>

#include <soft_move_base/SoftMoveBaseAction.h>
#include "softMotion/softMotion.h"
#include "softMotion/softMotionStruct.h"
#include "softMotion/softMotionStructGenom.h"
#include "pr2_soft_controller/SM_TRAJ_STR_ROS.h"

int main (int argc, char **argv)
{
  ros::init(argc, argv, "test_fibonacci");

  // create the action client
  // true causes the client to spin its own thread
  actionlib::SimpleActionClient<soft_move_base::SoftMoveBaseAction> ac("soft_move_base", true);

  ROS_INFO("Waiting for action server to start.");
  // wait for the action server to start
  ac.waitForServer(); //will wait for infinite time

  ROS_INFO("Action server started, sending goal.");
  // send a goal to the action
  soft_move_base::SoftMoveBaseGoal goal;

  SM_TRAJ traj;
  SM_TRAJ_STR smTraj;
  //load test traj
  traj.load("/u/magharbi/softMotion.traj", NULL);
  //traj.plot();
  //convert it
  traj.convertToSM_TRAJ_STR(&smTraj);

  pr2_soft_controller::SM_TRAJ_STR_ROS smTrajROS_;

  smTrajROS_.trajId= 0;
  //we use only a subset of the total joints set
  smTrajROS_.nbAxis= 6;
  smTrajROS_.qStart.resize(smTrajROS_.nbAxis);
  smTrajROS_.qGoal.resize(smTrajROS_.nbAxis);
  smTrajROS_.traj.resize(smTrajROS_.nbAxis);
  // we need the joints trajectory between debut and fin
  for(int i=0, n=0; i<smTrajROS_.nbAxis; ++i, ++n){
      smTrajROS_.qStart[n] = smTraj.qStart[i];
      smTrajROS_.qGoal[n] = smTraj.qGoal[i];
      smTrajROS_.traj[n].nbSeg= smTraj.traj[i].nbSeg;
      smTrajROS_.traj[n].unsused= smTraj.traj[i].unsused;
      smTrajROS_.traj[n].seg.resize(smTrajROS_.traj[n].nbSeg);
     for(int j=0; j<smTraj.traj[i].nbSeg; ++j){
        smTrajROS_.traj[n].seg[j].lpId= smTraj.traj[i].seg[j].lpId;
        smTrajROS_.traj[n].seg[j].unused= 0;
        smTrajROS_.traj[n].seg[j].timeOnTraj= smTraj.traj[i].seg[j].timeOnTraj;
        smTrajROS_.traj[n].seg[j].time= smTraj.traj[i].seg[j].time;
        smTrajROS_.traj[n].seg[j].ic_a= smTraj.traj[i].seg[j].ic_a;
        smTrajROS_.traj[n].seg[j].ic_v= smTraj.traj[i].seg[j].ic_v;
        smTrajROS_.traj[n].seg[j].ic_x= smTraj.traj[i].seg[j].ic_x;
        smTrajROS_.traj[n].seg[j].jerk= smTraj.traj[i].seg[j].jerk;
      }
  }

  goal.traj = smTrajROS_;
  ac.sendGoal(goal);

  //wait for the action to return
  bool finished_before_timeout = ac.waitForResult(ros::Duration(30.0));

  if (finished_before_timeout)
  {
    actionlib::SimpleClientGoalState state = ac.getState();
    ROS_INFO("Action finished: %s",state.toString().c_str());
  }
  else
    ROS_INFO("Action did not finish before the time out.");

  //exit
  return 0;
}


