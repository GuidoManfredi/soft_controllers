
(cl:in-package :asdf)

(defsystem "pr2_soft_controller-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "SM_TRAJ_AXIS_STR_ROS" :depends-on ("_package_SM_TRAJ_AXIS_STR_ROS"))
    (:file "_package_SM_TRAJ_AXIS_STR_ROS" :depends-on ("_package"))
    (:file "SM_SEGMENT_STR_ROS" :depends-on ("_package_SM_SEGMENT_STR_ROS"))
    (:file "_package_SM_SEGMENT_STR_ROS" :depends-on ("_package"))
    (:file "SM_TRAJ_STR_ROS" :depends-on ("_package_SM_TRAJ_STR_ROS"))
    (:file "_package_SM_TRAJ_STR_ROS" :depends-on ("_package"))
  ))