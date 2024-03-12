;; Auto-generated. Do not edit!


(when (boundp 'robot_msg::omni_perception)
  (if (not (find-package "ROBOT_MSG"))
    (make-package "ROBOT_MSG"))
  (shadow 'omni_perception (find-package "ROBOT_MSG")))
(unless (find-package "ROBOT_MSG::OMNI_PERCEPTION")
  (make-package "ROBOT_MSG::OMNI_PERCEPTION"))

(in-package "ROS")
;;//! \htmlinclude omni_perception.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass robot_msg::omni_perception
  :super ros::object
  :slots (_header _x _y _z _yaw _id _score _target_lock ))

(defmethod robot_msg::omni_perception
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:x __x) 0.0)
    ((:y __y) 0.0)
    ((:z __z) 0.0)
    ((:yaw __yaw) 0.0)
    ((:id __id) 0)
    ((:score __score) 0)
    ((:target_lock __target_lock) 0)
    )
   (send-super :init)
   (setq _header __header)
   (setq _x (float __x))
   (setq _y (float __y))
   (setq _z (float __z))
   (setq _yaw (float __yaw))
   (setq _id (round __id))
   (setq _score (round __score))
   (setq _target_lock (round __target_lock))
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:x
   (&optional __x)
   (if __x (setq _x __x)) _x)
  (:y
   (&optional __y)
   (if __y (setq _y __y)) _y)
  (:z
   (&optional __z)
   (if __z (setq _z __z)) _z)
  (:yaw
   (&optional __yaw)
   (if __yaw (setq _yaw __yaw)) _yaw)
  (:id
   (&optional __id)
   (if __id (setq _id __id)) _id)
  (:score
   (&optional __score)
   (if __score (setq _score __score)) _score)
  (:target_lock
   (&optional __target_lock)
   (if __target_lock (setq _target_lock __target_lock)) _target_lock)
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; float32 _x
    4
    ;; float32 _y
    4
    ;; float32 _z
    4
    ;; float32 _yaw
    4
    ;; int8 _id
    1
    ;; int8 _score
    1
    ;; int8 _target_lock
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; float32 _x
       (sys::poke _x (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _y
       (sys::poke _y (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _z
       (sys::poke _z (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _yaw
       (sys::poke _yaw (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; int8 _id
       (write-byte _id s)
     ;; int8 _score
       (write-byte _score s)
     ;; int8 _target_lock
       (write-byte _target_lock s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; float32 _x
     (setq _x (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _y
     (setq _y (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _z
     (setq _z (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _yaw
     (setq _yaw (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; int8 _id
     (setq _id (sys::peek buf ptr- :char)) (incf ptr- 1)
     (if (> _id 127) (setq _id (- _id 256)))
   ;; int8 _score
     (setq _score (sys::peek buf ptr- :char)) (incf ptr- 1)
     (if (> _score 127) (setq _score (- _score 256)))
   ;; int8 _target_lock
     (setq _target_lock (sys::peek buf ptr- :char)) (incf ptr- 1)
     (if (> _target_lock 127) (setq _target_lock (- _target_lock 256)))
   ;;
   self)
  )

(setf (get robot_msg::omni_perception :md5sum-) "bcf02bf291fe4deb8dd921151076c58f")
(setf (get robot_msg::omni_perception :datatype-) "robot_msg/omni_perception")
(setf (get robot_msg::omni_perception :definition-)
      "Header header
float32 x
float32 y
float32 z
float32 yaw
int8 id
int8 score
int8 target_lock
================================================================================
MSG: std_msgs/Header
# Standard metadata for higher-level stamped data types.
# This is generally used to communicate timestamped data 
# in a particular coordinate frame.
# 
# sequence ID: consecutively increasing ID 
uint32 seq
#Two-integer timestamp that is expressed as:
# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')
# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')
# time-handling sugar is provided by the client library
time stamp
#Frame this data is associated with
string frame_id

")



(provide :robot_msg/omni_perception "bcf02bf291fe4deb8dd921151076c58f")


