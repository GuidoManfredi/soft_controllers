; Auto-generated. Do not edit!


(cl:in-package soft_move_base-msg)


;//! \htmlinclude SoftMoveBaseActionGoal.msg.html

(cl:defclass <SoftMoveBaseActionGoal> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (goal_id
    :reader goal_id
    :initarg :goal_id
    :type actionlib_msgs-msg:GoalID
    :initform (cl:make-instance 'actionlib_msgs-msg:GoalID))
   (goal
    :reader goal
    :initarg :goal
    :type soft_move_base-msg:SoftMoveBaseGoal
    :initform (cl:make-instance 'soft_move_base-msg:SoftMoveBaseGoal)))
)

(cl:defclass SoftMoveBaseActionGoal (<SoftMoveBaseActionGoal>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <SoftMoveBaseActionGoal>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'SoftMoveBaseActionGoal)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name soft_move_base-msg:<SoftMoveBaseActionGoal> is deprecated: use soft_move_base-msg:SoftMoveBaseActionGoal instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <SoftMoveBaseActionGoal>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader soft_move_base-msg:header-val is deprecated.  Use soft_move_base-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'goal_id-val :lambda-list '(m))
(cl:defmethod goal_id-val ((m <SoftMoveBaseActionGoal>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader soft_move_base-msg:goal_id-val is deprecated.  Use soft_move_base-msg:goal_id instead.")
  (goal_id m))

(cl:ensure-generic-function 'goal-val :lambda-list '(m))
(cl:defmethod goal-val ((m <SoftMoveBaseActionGoal>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader soft_move_base-msg:goal-val is deprecated.  Use soft_move_base-msg:goal instead.")
  (goal m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <SoftMoveBaseActionGoal>) ostream)
  "Serializes a message object of type '<SoftMoveBaseActionGoal>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'goal_id) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'goal) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <SoftMoveBaseActionGoal>) istream)
  "Deserializes a message object of type '<SoftMoveBaseActionGoal>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'goal_id) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'goal) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<SoftMoveBaseActionGoal>)))
  "Returns string type for a message object of type '<SoftMoveBaseActionGoal>"
  "soft_move_base/SoftMoveBaseActionGoal")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SoftMoveBaseActionGoal)))
  "Returns string type for a message object of type 'SoftMoveBaseActionGoal"
  "soft_move_base/SoftMoveBaseActionGoal")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<SoftMoveBaseActionGoal>)))
  "Returns md5sum for a message object of type '<SoftMoveBaseActionGoal>"
  "59208ee2e3dc4e794d85f7b90e9d2097")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'SoftMoveBaseActionGoal)))
  "Returns md5sum for a message object of type 'SoftMoveBaseActionGoal"
  "59208ee2e3dc4e794d85f7b90e9d2097")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<SoftMoveBaseActionGoal>)))
  "Returns full string definition for message of type '<SoftMoveBaseActionGoal>"
  (cl:format cl:nil "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======~%~%Header header~%actionlib_msgs/GoalID goal_id~%SoftMoveBaseGoal goal~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.secs: seconds (stamp_secs) since epoch~%# * stamp.nsecs: nanoseconds since stamp_secs~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: actionlib_msgs/GoalID~%# The stamp should store the time at which this goal was requested.~%# It is used by an action server when it tries to preempt all~%# goals that were requested before a certain time~%time stamp~%~%# The id provides a way to associate feedback and~%# result message with specific goal requests. The id~%# specified must be unique.~%string id~%~%~%================================================================================~%MSG: soft_move_base/SoftMoveBaseGoal~%# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======~%#goal definition~%pr2_soft_controller/SM_TRAJ_STR_ROS traj~%~%================================================================================~%MSG: pr2_soft_controller/SM_TRAJ_STR_ROS~%int32 trajId~%int32 nbAxis~%float64 timePreserved~%float64[] qStart~%float64[] qGoal~%float64[] jmax~%float64[] amax~%float64[] vmax~%SM_TRAJ_AXIS_STR_ROS[] traj~%~%================================================================================~%MSG: pr2_soft_controller/SM_TRAJ_AXIS_STR_ROS~%int32 nbSeg~%int32 unsused~%SM_SEGMENT_STR_ROS[] seg~%~%~%================================================================================~%MSG: pr2_soft_controller/SM_SEGMENT_STR_ROS~%int32 lpId~%int32 unused~%float64 timeOnTraj~%float64 time~%float64 ic_a~%float64 ic_v~%float64 ic_x~%float64 jerk~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'SoftMoveBaseActionGoal)))
  "Returns full string definition for message of type 'SoftMoveBaseActionGoal"
  (cl:format cl:nil "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======~%~%Header header~%actionlib_msgs/GoalID goal_id~%SoftMoveBaseGoal goal~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.secs: seconds (stamp_secs) since epoch~%# * stamp.nsecs: nanoseconds since stamp_secs~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: actionlib_msgs/GoalID~%# The stamp should store the time at which this goal was requested.~%# It is used by an action server when it tries to preempt all~%# goals that were requested before a certain time~%time stamp~%~%# The id provides a way to associate feedback and~%# result message with specific goal requests. The id~%# specified must be unique.~%string id~%~%~%================================================================================~%MSG: soft_move_base/SoftMoveBaseGoal~%# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======~%#goal definition~%pr2_soft_controller/SM_TRAJ_STR_ROS traj~%~%================================================================================~%MSG: pr2_soft_controller/SM_TRAJ_STR_ROS~%int32 trajId~%int32 nbAxis~%float64 timePreserved~%float64[] qStart~%float64[] qGoal~%float64[] jmax~%float64[] amax~%float64[] vmax~%SM_TRAJ_AXIS_STR_ROS[] traj~%~%================================================================================~%MSG: pr2_soft_controller/SM_TRAJ_AXIS_STR_ROS~%int32 nbSeg~%int32 unsused~%SM_SEGMENT_STR_ROS[] seg~%~%~%================================================================================~%MSG: pr2_soft_controller/SM_SEGMENT_STR_ROS~%int32 lpId~%int32 unused~%float64 timeOnTraj~%float64 time~%float64 ic_a~%float64 ic_v~%float64 ic_x~%float64 jerk~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <SoftMoveBaseActionGoal>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'goal_id))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'goal))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <SoftMoveBaseActionGoal>))
  "Converts a ROS message object to a list"
  (cl:list 'SoftMoveBaseActionGoal
    (cl:cons ':header (header msg))
    (cl:cons ':goal_id (goal_id msg))
    (cl:cons ':goal (goal msg))
))
