#ifndef HEAD_TRACKING_SOFT_CONTROLLER
#define HEAD_TRACKING_SOFT_CONTROLLER

#include <algorithm>
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

#include "std_msgs/Float64.h"

#include "pr2_controllers_msgs/QueryTrajectoryState.h"
#include "pr2_controllers_msgs/JointTrajectoryControllerState.h"
#include "head_tracking_soft_controller/PanTilt.h"

namespace controller{

class HeadTrackingSoftController: public pr2_controller_interface::Controller
{
public:
  HeadTrackingSoftController();
  ~HeadTrackingSoftController();

  bool init(pr2_mechanism_model::RobotState *robot,
                   ros::NodeHandle &n);
  void starting();
  void update();

private:
  bool queryStateService( pr2_controllers_msgs::QueryTrajectoryState::Request &req,
    pr2_controllers_msgs::QueryTrajectoryState::Response &resp);
  void commandCB(const head_tracking_soft_controller::PanTiltConstPtr& command);
  void timeScaleCB(const std_msgs::Float64ConstPtr& timeScale);
  void inhibitionCB(const std_msgs::Float64ConstPtr& inhibitionPoints);


  // ROS controller part
  int loop_count_;
  pr2_mechanism_model::RobotState *robot_;
  ros::Time last_time_;
  std::vector<pr2_mechanism_model::JointState*> joints_;
  std::vector<control_toolbox::Pid> pids_;

  ros::NodeHandle node_;
  ros::ServiceServer queryStateService_;
  ros::Subscriber commandSub_;
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
  std::vector<SM_COND> ic_, fc_;

  // Soft motion part
  std::vector<double> lastAcc_;
  std::vector<double> lastVel_;
  double timeScale_;
  double timeFromStart_;
  SM_COND timeScaleCond_;
  std::vector<SM_LIMITS> limits_;
  SM_LIMITS timescaleLimits_;
};

}

#endif
