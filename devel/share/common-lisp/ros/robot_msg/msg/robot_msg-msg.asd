
(cl:in-package :asdf)

(defsystem "robot_msg-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :std_msgs-msg
)
  :components ((:file "_package")
    (:file "PTZ_Yaw" :depends-on ("_package_PTZ_Yaw"))
    (:file "_package_PTZ_Yaw" :depends-on ("_package"))
    (:file "PTZ_perception" :depends-on ("_package_PTZ_perception"))
    (:file "_package_PTZ_perception" :depends-on ("_package"))
    (:file "Robot_ctrl" :depends-on ("_package_Robot_ctrl"))
    (:file "_package_Robot_ctrl" :depends-on ("_package"))
    (:file "Vision" :depends-on ("_package_Vision"))
    (:file "_package_Vision" :depends-on ("_package"))
    (:file "omni_perception" :depends-on ("_package_omni_perception"))
    (:file "_package_omni_perception" :depends-on ("_package"))
  ))