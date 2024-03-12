; Auto-generated. Do not edit!


(cl:in-package robot_msg-msg)


;//! \htmlinclude Decision.msg.html

(cl:defclass <Decision> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (yaw
    :reader yaw
    :initarg :yaw
    :type cl:float
    :initform 0.0)
   (pitch
    :reader pitch
    :initarg :pitch
    :type cl:float
    :initform 0.0)
   (target_lock
    :reader target_lock
    :initarg :target_lock
    :type cl:fixnum
    :initform 0)
   (fire_command
    :reader fire_command
    :initarg :fire_command
    :type cl:fixnum
    :initform 0)
   (fire_mode
    :reader fire_mode
    :initarg :fire_mode
    :type cl:fixnum
    :initform 0)
   (score
    :reader score
    :initarg :score
    :type cl:fixnum
    :initform 0))
)

(cl:defclass Decision (<Decision>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Decision>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Decision)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name robot_msg-msg:<Decision> is deprecated: use robot_msg-msg:Decision instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <Decision>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader robot_msg-msg:header-val is deprecated.  Use robot_msg-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'yaw-val :lambda-list '(m))
(cl:defmethod yaw-val ((m <Decision>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader robot_msg-msg:yaw-val is deprecated.  Use robot_msg-msg:yaw instead.")
  (yaw m))

(cl:ensure-generic-function 'pitch-val :lambda-list '(m))
(cl:defmethod pitch-val ((m <Decision>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader robot_msg-msg:pitch-val is deprecated.  Use robot_msg-msg:pitch instead.")
  (pitch m))

(cl:ensure-generic-function 'target_lock-val :lambda-list '(m))
(cl:defmethod target_lock-val ((m <Decision>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader robot_msg-msg:target_lock-val is deprecated.  Use robot_msg-msg:target_lock instead.")
  (target_lock m))

(cl:ensure-generic-function 'fire_command-val :lambda-list '(m))
(cl:defmethod fire_command-val ((m <Decision>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader robot_msg-msg:fire_command-val is deprecated.  Use robot_msg-msg:fire_command instead.")
  (fire_command m))

(cl:ensure-generic-function 'fire_mode-val :lambda-list '(m))
(cl:defmethod fire_mode-val ((m <Decision>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader robot_msg-msg:fire_mode-val is deprecated.  Use robot_msg-msg:fire_mode instead.")
  (fire_mode m))

(cl:ensure-generic-function 'score-val :lambda-list '(m))
(cl:defmethod score-val ((m <Decision>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader robot_msg-msg:score-val is deprecated.  Use robot_msg-msg:score instead.")
  (score m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Decision>) ostream)
  "Serializes a message object of type '<Decision>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'yaw))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'pitch))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let* ((signed (cl:slot-value msg 'target_lock)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 256) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'fire_command)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 256) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'fire_mode)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 256) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'score)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 256) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Decision>) istream)
  "Deserializes a message object of type '<Decision>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'yaw) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'pitch) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'target_lock) (cl:if (cl:< unsigned 128) unsigned (cl:- unsigned 256))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'fire_command) (cl:if (cl:< unsigned 128) unsigned (cl:- unsigned 256))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'fire_mode) (cl:if (cl:< unsigned 128) unsigned (cl:- unsigned 256))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'score) (cl:if (cl:< unsigned 128) unsigned (cl:- unsigned 256))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Decision>)))
  "Returns string type for a message object of type '<Decision>"
  "robot_msg/Decision")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Decision)))
  "Returns string type for a message object of type 'Decision"
  "robot_msg/Decision")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Decision>)))
  "Returns md5sum for a message object of type '<Decision>"
  "76db552330cdcb44ee352383281c2d0d")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Decision)))
  "Returns md5sum for a message object of type 'Decision"
  "76db552330cdcb44ee352383281c2d0d")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Decision>)))
  "Returns full string definition for message of type '<Decision>"
  (cl:format cl:nil "Header header~%float32 yaw~%float32 pitch~%int8 target_lock~%int8 fire_command~%int8 fire_mode~%int8 score~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Decision)))
  "Returns full string definition for message of type 'Decision"
  (cl:format cl:nil "Header header~%float32 yaw~%float32 pitch~%int8 target_lock~%int8 fire_command~%int8 fire_mode~%int8 score~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Decision>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     4
     4
     1
     1
     1
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Decision>))
  "Converts a ROS message object to a list"
  (cl:list 'Decision
    (cl:cons ':header (header msg))
    (cl:cons ':yaw (yaw msg))
    (cl:cons ':pitch (pitch msg))
    (cl:cons ':target_lock (target_lock msg))
    (cl:cons ':fire_command (fire_command msg))
    (cl:cons ':fire_mode (fire_mode msg))
    (cl:cons ':score (score msg))
))
