
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

  actionlib::SimpleActionClient<soft_move_base::SoftMoveBaseAction> ac("soft_move_base", true);

/*
  // send a goal to the action
  soft_move_base::SoftMoveBaseGoal goal;

  SM_TRAJ traj;
  SM_TRAJ_STR smTraj;

  goal.traj = smTrajROS_;
  ac.sendGoal(goal);
*/
  ROS_INFO("Stopping all goals on soft_move_base action server.");
  ac.cancelAllGoals();
  //exit
  return 0;
}



