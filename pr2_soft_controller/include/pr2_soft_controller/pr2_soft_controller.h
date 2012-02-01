#ifndef PR2_SOFT_CONTROLLER
#define PR2_SOFT_CONTROLLER

#include <vector>
#include <boost/scoped_ptr.hpp>
#include <boost/thread/recursive_mutex.hpp>
#include <boost/thread/condition.hpp>

#include <ros/node_handle.h>
#include <control_toolbox/pid.h>
#include <pr2_controller_interface/controller.h>
#include <realtime_tools/realtime_publisher.h>
#include <realtime_tools/realtime_box.h>

#include "softMotion/softMotion.h"
#include "softMotion/softMotionStruct.h"
#include "softMotion/softMotionStructGenom.h"

#include "pr2_soft_controller/SM_TRAJ_STR_ROS.h"
#include "std_msgs/Float64.h"

#include "pr2_controllers_msgs/QueryTrajectoryState.h"
#include "pr2_controllers_msgs/JointTrajectoryControllerState.h"
#include <pr2_gripper_sensor_msgs/PR2GripperEventDetectorAction.h>
#include <pr2_gripper_sensor_msgs/PR2GripperEventDetectorData.h>
#include <pr2_gripper_sensor_msgs/PR2GripperEventDetectorCommand.h>


namespace controller{

class Pr2SoftController: public pr2_controller_interface::Controller
{
public:
  Pr2SoftController();
  ~Pr2SoftController();

  bool init(pr2_mechanism_model::RobotState *robot,
                   ros::NodeHandle &n);
  void starting();
  void update();

private:
  void commandCB(const pr2_soft_controller::SM_TRAJ_STR_ROSConstPtr& 
trajectory_msg);
  void timeScaleCB(const std_msgs::Float64ConstPtr& timeScale);

  // ROS controller part
  int loop_count_;
  pr2_mechanism_model::RobotState *robot_;
  ros::Time last_time_;
  std::vector<pr2_mechanism_model::JointState*> joints_;
  std::vector<control_toolbox::Pid> pids_;

  ros::NodeHandle node_;
  ros::Subscriber commandSub_;
  ros::Subscriber accTreshSub_;
  ros::Subscriber timeScaleSub_;
  ros::Subscriber headInhibitionSub_;
  ros::Publisher headInhibitionPub_;

  pr2_gripper_sensor_msgs::PR2GripperEventDetectorCommand event_command_;

  boost::scoped_ptr<
    realtime_tools::RealtimePublisher<
      pr2_controllers_msgs::JointTrajectoryControllerState> > controller_state_publisher_;

  realtime_tools::RealtimeBox<
    boost::shared_ptr<SM_TRAJ> > current_trajectory_box_;

  std::vector<double> q, qd, qdd;
  bool PIDreset_;

  // Soft motion part
  bool cantMove_;
  double timeScale_;
  double timeFromStart_;
  SM_TRAJ_STR holdTraj_;
  SM_COND timeScaleCond_;
  SM_LIMITS limits_;
};

}

#endif
