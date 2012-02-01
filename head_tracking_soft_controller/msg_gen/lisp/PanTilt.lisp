; Auto-generated. Do not edit!


(cl:in-package head_tracking_soft_controller-msg)


;//! \htmlinclude PanTilt.msg.html

(cl:defclass <PanTilt> (roslisp-msg-protocol:ros-message)
  ((data
    :reader data
    :initarg :data
    :type (cl:vector cl:float)
   :initform (cl:make-array 2 :element-type 'cl:float :initial-element 0.0)))
)

(cl:defclass PanTilt (<PanTilt>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <PanTilt>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'PanTilt)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name head_tracking_soft_controller-msg:<PanTilt> is deprecated: use head_tracking_soft_controller-msg:PanTilt instead.")))

(cl:ensure-generic-function 'data-val :lambda-list '(m))
(cl:defmethod data-val ((m <PanTilt>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader head_tracking_soft_controller-msg:data-val is deprecated.  Use head_tracking_soft_controller-msg:data instead.")
  (data m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <PanTilt>) ostream)
  "Serializes a message object of type '<PanTilt>"
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let ((bits (roslisp-utils:encode-double-float-bits ele)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream)))
   (cl:slot-value msg 'data))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <PanTilt>) istream)
  "Deserializes a message object of type '<PanTilt>"
  (cl:setf (cl:slot-value msg 'data) (cl:make-array 2))
  (cl:let ((vals (cl:slot-value msg 'data)))
    (cl:dotimes (i 2)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:aref vals i) (roslisp-utils:decode-double-float-bits bits)))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<PanTilt>)))
  "Returns string type for a message object of type '<PanTilt>"
  "head_tracking_soft_controller/PanTilt")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'PanTilt)))
  "Returns string type for a message object of type 'PanTilt"
  "head_tracking_soft_controller/PanTilt")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<PanTilt>)))
  "Returns md5sum for a message object of type '<PanTilt>"
  "a64ac68384ecd108c6beb460bc157ad2")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'PanTilt)))
  "Returns md5sum for a message object of type 'PanTilt"
  "a64ac68384ecd108c6beb460bc157ad2")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<PanTilt>)))
  "Returns full string definition for message of type '<PanTilt>"
  (cl:format cl:nil "float64[2] data~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'PanTilt)))
  "Returns full string definition for message of type 'PanTilt"
  (cl:format cl:nil "float64[2] data~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <PanTilt>))
  (cl:+ 0
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'data) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 8)))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <PanTilt>))
  "Converts a ROS message object to a list"
  (cl:list 'PanTilt
    (cl:cons ':data (data msg))
))
