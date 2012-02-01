#ifndef HEAD_SOFT_CONTROLLER
#define HEAD_SOFT_CONTROLLER

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

namespace controller{

class HeadSoftController: public pr2_controller_interface::Controller
{
public:
  HeadSoftController();
  ~HeadSoftController();

  bool init(pr2_mechanism_model::RobotState *robot,
                   ros::NodeHandle &n);
  void starting();
  void update();

private:
  void commandCB(const pr2_soft_controller::SM_TRAJ_STR_ROSConstPtr& 
trajectory_msg);
  void timeScaleCB(const std_msgs::Float64ConstPtr& timeScale);
  void inhibitionCB(const std_msgs::Float64ConstPtr& inhibitionPoints);

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
  ros::Subscriber inhibitionSub_;
  ros::Publisher inhibitionPub_;
  int inhibitionPoints_;

  boost::scoped_ptr<
    realtime_tools::RealtimePublisher<
      pr2_controllers_msgs::JointTrajectoryControllerState> > controller_state_publisher_;

  realtime_tools::RealtimeBox<
    boost::shared_ptr<SM_TRAJ> > current_trajectory_box_;

  std::vector<double> q, qd, qdd;

  // Soft motion part
  double timeScale_;
  double timeFromStart_;
  SM_COND timeScaleCond_;
  SM_LIMITS limits_;
};

}

#endif
