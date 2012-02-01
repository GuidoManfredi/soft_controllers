; Auto-generated. Do not edit!


(cl:in-package pr2_soft_controller-msg)


;//! \htmlinclude SM_SEGMENT_STR_ROS.msg.html

(cl:defclass <SM_SEGMENT_STR_ROS> (roslisp-msg-protocol:ros-message)
  ((lpId
    :reader lpId
    :initarg :lpId
    :type cl:integer
    :initform 0)
   (unused
    :reader unused
    :initarg :unused
    :type cl:integer
    :initform 0)
   (timeOnTraj
    :reader timeOnTraj
    :initarg :timeOnTraj
    :type cl:float
    :initform 0.0)
   (time
    :reader time
    :initarg :time
    :type cl:float
    :initform 0.0)
   (ic_a
    :reader ic_a
    :initarg :ic_a
    :type cl:float
    :initform 0.0)
   (ic_v
    :reader ic_v
    :initarg :ic_v
    :type cl:float
    :initform 0.0)
   (ic_x
    :reader ic_x
    :initarg :ic_x
    :type cl:float
    :initform 0.0)
   (jerk
    :reader jerk
    :initarg :jerk
    :type cl:float
    :initform 0.0))
)

(cl:defclass SM_SEGMENT_STR_ROS (<SM_SEGMENT_STR_ROS>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <SM_SEGMENT_STR_ROS>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'SM_SEGMENT_STR_ROS)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name pr2_soft_controller-msg:<SM_SEGMENT_STR_ROS> is deprecated: use pr2_soft_controller-msg:SM_SEGMENT_STR_ROS instead.")))

(cl:ensure-generic-function 'lpId-val :lambda-list '(m))
(cl:defmethod lpId-val ((m <SM_SEGMENT_STR_ROS>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader pr2_soft_controller-msg:lpId-val is deprecated.  Use pr2_soft_controller-msg:lpId instead.")
  (lpId m))

(cl:ensure-generic-function 'unused-val :lambda-list '(m))
(cl:defmethod unused-val ((m <SM_SEGMENT_STR_ROS>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader pr2_soft_controller-msg:unused-val is deprecated.  Use pr2_soft_controller-msg:unused instead.")
  (unused m))

(cl:ensure-generic-function 'timeOnTraj-val :lambda-list '(m))
(cl:defmethod timeOnTraj-val ((m <SM_SEGMENT_STR_ROS>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader pr2_soft_controller-msg:timeOnTraj-val is deprecated.  Use pr2_soft_controller-msg:timeOnTraj instead.")
  (timeOnTraj m))

(cl:ensure-generic-function 'time-val :lambda-list '(m))
(cl:defmethod time-val ((m <SM_SEGMENT_STR_ROS>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader pr2_soft_controller-msg:time-val is deprecated.  Use pr2_soft_controller-msg:time instead.")
  (time m))

(cl:ensure-generic-function 'ic_a-val :lambda-list '(m))
(cl:defmethod ic_a-val ((m <SM_SEGMENT_STR_ROS>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader pr2_soft_controller-msg:ic_a-val is deprecated.  Use pr2_soft_controller-msg:ic_a instead.")
  (ic_a m))

(cl:ensure-generic-function 'ic_v-val :lambda-list '(m))
(cl:defmethod ic_v-val ((m <SM_SEGMENT_STR_ROS>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader pr2_soft_controller-msg:ic_v-val is deprecated.  Use pr2_soft_controller-msg:ic_v instead.")
  (ic_v m))

(cl:ensure-generic-function 'ic_x-val :lambda-list '(m))
(cl:defmethod ic_x-val ((m <SM_SEGMENT_STR_ROS>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader pr2_soft_controller-msg:ic_x-val is deprecated.  Use pr2_soft_controller-msg:ic_x instead.")
  (ic_x m))

(cl:ensure-generic-function 'jerk-val :lambda-list '(m))
(cl:defmethod jerk-val ((m <SM_SEGMENT_STR_ROS>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader pr2_soft_controller-msg:jerk-val is deprecated.  Use pr2_soft_controller-msg:jerk instead.")
  (jerk m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <SM_SEGMENT_STR_ROS>) ostream)
  "Serializes a message object of type '<SM_SEGMENT_STR_ROS>"
  (cl:let* ((signed (cl:slot-value msg 'lpId)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'unused)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'timeOnTraj))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'time))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'ic_a))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'ic_v))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'ic_x))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'jerk))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <SM_SEGMENT_STR_ROS>) istream)
  "Deserializes a message object of type '<SM_SEGMENT_STR_ROS>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'lpId) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'unused) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'timeOnTraj) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'time) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'ic_a) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'ic_v) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'ic_x) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'jerk) (roslisp-utils:decode-double-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<SM_SEGMENT_STR_ROS>)))
  "Returns string type for a message object of type '<SM_SEGMENT_STR_ROS>"
  "pr2_soft_controller/SM_SEGMENT_STR_ROS")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SM_SEGMENT_STR_ROS)))
  "Returns string type for a message object of type 'SM_SEGMENT_STR_ROS"
  "pr2_soft_controller/SM_SEGMENT_STR_ROS")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<SM_SEGMENT_STR_ROS>)))
  "Returns md5sum for a message object of type '<SM_SEGMENT_STR_ROS>"
  "1177219c152dc7e2bdf63b0d409cf1a3")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'SM_SEGMENT_STR_ROS)))
  "Returns md5sum for a message object of type 'SM_SEGMENT_STR_ROS"
  "1177219c152dc7e2bdf63b0d409cf1a3")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<SM_SEGMENT_STR_ROS>)))
  "Returns full string definition for message of type '<SM_SEGMENT_STR_ROS>"
  (cl:format cl:nil "int32 lpId~%int32 unused~%float64 timeOnTraj~%float64 time~%float64 ic_a~%float64 ic_v~%float64 ic_x~%float64 jerk~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'SM_SEGMENT_STR_ROS)))
  "Returns full string definition for message of type 'SM_SEGMENT_STR_ROS"
  (cl:format cl:nil "int32 lpId~%int32 unused~%float64 timeOnTraj~%float64 time~%float64 ic_a~%float64 ic_v~%float64 ic_x~%float64 jerk~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <SM_SEGMENT_STR_ROS>))
  (cl:+ 0
     4
     4
     8
     8
     8
     8
     8
     8
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <SM_SEGMENT_STR_ROS>))
  "Converts a ROS message object to a list"
  (cl:list 'SM_SEGMENT_STR_ROS
    (cl:cons ':lpId (lpId msg))
    (cl:cons ':unused (unused msg))
    (cl:cons ':timeOnTraj (timeOnTraj msg))
    (cl:cons ':time (time msg))
    (cl:cons ':ic_a (ic_a msg))
    (cl:cons ':ic_v (ic_v msg))
    (cl:cons ':ic_x (ic_x msg))
    (cl:cons ':jerk (jerk msg))
))
