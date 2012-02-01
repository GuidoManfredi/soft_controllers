; Auto-generated. Do not edit!


(cl:in-package pr2_soft_controller-msg)


;//! \htmlinclude SM_TRAJ_AXIS_STR_ROS.msg.html

(cl:defclass <SM_TRAJ_AXIS_STR_ROS> (roslisp-msg-protocol:ros-message)
  ((nbSeg
    :reader nbSeg
    :initarg :nbSeg
    :type cl:integer
    :initform 0)
   (unsused
    :reader unsused
    :initarg :unsused
    :type cl:integer
    :initform 0)
   (seg
    :reader seg
    :initarg :seg
    :type (cl:vector pr2_soft_controller-msg:SM_SEGMENT_STR_ROS)
   :initform (cl:make-array 0 :element-type 'pr2_soft_controller-msg:SM_SEGMENT_STR_ROS :initial-element (cl:make-instance 'pr2_soft_controller-msg:SM_SEGMENT_STR_ROS))))
)

(cl:defclass SM_TRAJ_AXIS_STR_ROS (<SM_TRAJ_AXIS_STR_ROS>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <SM_TRAJ_AXIS_STR_ROS>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'SM_TRAJ_AXIS_STR_ROS)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name pr2_soft_controller-msg:<SM_TRAJ_AXIS_STR_ROS> is deprecated: use pr2_soft_controller-msg:SM_TRAJ_AXIS_STR_ROS instead.")))

(cl:ensure-generic-function 'nbSeg-val :lambda-list '(m))
(cl:defmethod nbSeg-val ((m <SM_TRAJ_AXIS_STR_ROS>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader pr2_soft_controller-msg:nbSeg-val is deprecated.  Use pr2_soft_controller-msg:nbSeg instead.")
  (nbSeg m))

(cl:ensure-generic-function 'unsused-val :lambda-list '(m))
(cl:defmethod unsused-val ((m <SM_TRAJ_AXIS_STR_ROS>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader pr2_soft_controller-msg:unsused-val is deprecated.  Use pr2_soft_controller-msg:unsused instead.")
  (unsused m))

(cl:ensure-generic-function 'seg-val :lambda-list '(m))
(cl:defmethod seg-val ((m <SM_TRAJ_AXIS_STR_ROS>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader pr2_soft_controller-msg:seg-val is deprecated.  Use pr2_soft_controller-msg:seg instead.")
  (seg m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <SM_TRAJ_AXIS_STR_ROS>) ostream)
  "Serializes a message object of type '<SM_TRAJ_AXIS_STR_ROS>"
  (cl:let* ((signed (cl:slot-value msg 'nbSeg)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'unsused)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'seg))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'seg))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <SM_TRAJ_AXIS_STR_ROS>) istream)
  "Deserializes a message object of type '<SM_TRAJ_AXIS_STR_ROS>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'nbSeg) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'unsused) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'seg) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'seg)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'pr2_soft_controller-msg:SM_SEGMENT_STR_ROS))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<SM_TRAJ_AXIS_STR_ROS>)))
  "Returns string type for a message object of type '<SM_TRAJ_AXIS_STR_ROS>"
  "pr2_soft_controller/SM_TRAJ_AXIS_STR_ROS")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SM_TRAJ_AXIS_STR_ROS)))
  "Returns string type for a message object of type 'SM_TRAJ_AXIS_STR_ROS"
  "pr2_soft_controller/SM_TRAJ_AXIS_STR_ROS")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<SM_TRAJ_AXIS_STR_ROS>)))
  "Returns md5sum for a message object of type '<SM_TRAJ_AXIS_STR_ROS>"
  "46d28de6583e6d91193c1deecfbc745d")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'SM_TRAJ_AXIS_STR_ROS)))
  "Returns md5sum for a message object of type 'SM_TRAJ_AXIS_STR_ROS"
  "46d28de6583e6d91193c1deecfbc745d")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<SM_TRAJ_AXIS_STR_ROS>)))
  "Returns full string definition for message of type '<SM_TRAJ_AXIS_STR_ROS>"
  (cl:format cl:nil "int32 nbSeg~%int32 unsused~%SM_SEGMENT_STR_ROS[] seg~%~%~%================================================================================~%MSG: pr2_soft_controller/SM_SEGMENT_STR_ROS~%int32 lpId~%int32 unused~%float64 timeOnTraj~%float64 time~%float64 ic_a~%float64 ic_v~%float64 ic_x~%float64 jerk~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'SM_TRAJ_AXIS_STR_ROS)))
  "Returns full string definition for message of type 'SM_TRAJ_AXIS_STR_ROS"
  (cl:format cl:nil "int32 nbSeg~%int32 unsused~%SM_SEGMENT_STR_ROS[] seg~%~%~%================================================================================~%MSG: pr2_soft_controller/SM_SEGMENT_STR_ROS~%int32 lpId~%int32 unused~%float64 timeOnTraj~%float64 time~%float64 ic_a~%float64 ic_v~%float64 ic_x~%float64 jerk~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <SM_TRAJ_AXIS_STR_ROS>))
  (cl:+ 0
     4
     4
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'seg) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <SM_TRAJ_AXIS_STR_ROS>))
  "Converts a ROS message object to a list"
  (cl:list 'SM_TRAJ_AXIS_STR_ROS
    (cl:cons ':nbSeg (nbSeg msg))
    (cl:cons ':unsused (unsused msg))
    (cl:cons ':seg (seg msg))
))
