; Auto-generated. Do not edit!


(cl:in-package robot_msg-msg)


;//! \htmlinclude Vision.msg.html

(cl:defclass <Vision> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (id
    :reader id
    :initarg :id
    :type cl:fixnum
    :initform 0)
   (pitch
    :reader pitch
    :initarg :pitch
    :type cl:float
    :initform 0.0)
   (yaw
    :reader yaw
    :initarg :yaw
    :type cl:float
    :initform 0.0)
   (roll
    :reader roll
    :initarg :roll
    :type cl:float
    :initform 0.0)
   (quaternion
    :reader quaternion
    :initarg :quaternion
    :type (cl:vector cl:float)
   :initform (cl:make-array 0 :element-type 'cl:float :initial-element 0.0))
   (shoot_spd
    :reader shoot_spd
    :initarg :shoot_spd
    :type cl:float
    :initform 0.0))
)

(cl:defclass Vision (<Vision>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Vision>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Vision)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name robot_msg-msg:<Vision> is deprecated: use robot_msg-msg:Vision instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <Vision>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader robot_msg-msg:header-val is deprecated.  Use robot_msg-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'id-val :lambda-list '(m))
(cl:defmethod id-val ((m <Vision>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader robot_msg-msg:id-val is deprecated.  Use robot_msg-msg:id instead.")
  (id m))

(cl:ensure-generic-function 'pitch-val :lambda-list '(m))
(cl:defmethod pitch-val ((m <Vision>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader robot_msg-msg:pitch-val is deprecated.  Use robot_msg-msg:pitch instead.")
  (pitch m))

(cl:ensure-generic-function 'yaw-val :lambda-list '(m))
(cl:defmethod yaw-val ((m <Vision>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader robot_msg-msg:yaw-val is deprecated.  Use robot_msg-msg:yaw instead.")
  (yaw m))

(cl:ensure-generic-function 'roll-val :lambda-list '(m))
(cl:defmethod roll-val ((m <Vision>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader robot_msg-msg:roll-val is deprecated.  Use robot_msg-msg:roll instead.")
  (roll m))

(cl:ensure-generic-function 'quaternion-val :lambda-list '(m))
(cl:defmethod quaternion-val ((m <Vision>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader robot_msg-msg:quaternion-val is deprecated.  Use robot_msg-msg:quaternion instead.")
  (quaternion m))

(cl:ensure-generic-function 'shoot_spd-val :lambda-list '(m))
(cl:defmethod shoot_spd-val ((m <Vision>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader robot_msg-msg:shoot_spd-val is deprecated.  Use robot_msg-msg:shoot_spd instead.")
  (shoot_spd m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Vision>) ostream)
  "Serializes a message object of type '<Vision>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'id)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'id)) ostream)
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'pitch))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'yaw))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'roll))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'quaternion))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let ((bits (roslisp-utils:encode-single-float-bits ele)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)))
   (cl:slot-value msg 'quaternion))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'shoot_spd))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Vision>) istream)
  "Deserializes a message object of type '<Vision>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'id)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'id)) (cl:read-byte istream))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'pitch) (roslisp-utils:decode-single-float-bits bits)))
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
    (cl:setf (cl:slot-value msg 'roll) (roslisp-utils:decode-single-float-bits bits)))
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'quaternion) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'quaternion)))
    (cl:dotimes (i __ros_arr_len)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:aref vals i) (roslisp-utils:decode-single-float-bits bits))))))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'shoot_spd) (roslisp-utils:decode-single-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Vision>)))
  "Returns string type for a message object of type '<Vision>"
  "robot_msg/Vision")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Vision)))
  "Returns string type for a message object of type 'Vision"
  "robot_msg/Vision")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Vision>)))
  "Returns md5sum for a message object of type '<Vision>"
  "e9ed3a3b641ae2139fa852e5cf4f6219")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Vision)))
  "Returns md5sum for a message object of type 'Vision"
  "e9ed3a3b641ae2139fa852e5cf4f6219")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Vision>)))
  "Returns full string definition for message of type '<Vision>"
  (cl:format cl:nil "  Header header~%  uint16 id         # 1:蓝 2:红 ~%  float32 pitch~%  float32 yaw~%  float32 roll~%  float32[] quaternion~%  float32 shoot_spd~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Vision)))
  "Returns full string definition for message of type 'Vision"
  (cl:format cl:nil "  Header header~%  uint16 id         # 1:蓝 2:红 ~%  float32 pitch~%  float32 yaw~%  float32 roll~%  float32[] quaternion~%  float32 shoot_spd~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Vision>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     2
     4
     4
     4
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'quaternion) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 4)))
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Vision>))
  "Converts a ROS message object to a list"
  (cl:list 'Vision
    (cl:cons ':header (header msg))
    (cl:cons ':id (id msg))
    (cl:cons ':pitch (pitch msg))
    (cl:cons ':yaw (yaw msg))
    (cl:cons ':roll (roll msg))
    (cl:cons ':quaternion (quaternion msg))
    (cl:cons ':shoot_spd (shoot_spd msg))
))
