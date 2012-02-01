
(cl:in-package :asdf)

(defsystem "soft_move_base-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :actionlib_msgs-msg
               :pr2_soft_controller-msg
               :std_msgs-msg
)
  :components ((:file "_package")
    (:file "SoftMoveBaseActionFeedback" :depends-on ("_package_SoftMoveBaseActionFeedback"))
    (:file "_package_SoftMoveBaseActionFeedback" :depends-on ("_package"))
    (:file "SoftMoveBaseFeedback" :depends-on ("_package_SoftMoveBaseFeedback"))
    (:file "_package_SoftMoveBaseFeedback" :depends-on ("_package"))
    (:file "SoftMoveBaseActionResult" :depends-on ("_package_SoftMoveBaseActionResult"))
    (:file "_package_SoftMoveBaseActionResult" :depends-on ("_package"))
    (:file "SoftMoveBaseActionGoal" :depends-on ("_package_SoftMoveBaseActionGoal"))
    (:file "_package_SoftMoveBaseActionGoal" :depends-on ("_package"))
    (:file "SoftMoveBaseAction" :depends-on ("_package_SoftMoveBaseAction"))
    (:file "_package_SoftMoveBaseAction" :depends-on ("_package"))
    (:file "SoftMoveBaseGoal" :depends-on ("_package_SoftMoveBaseGoal"))
    (:file "_package_SoftMoveBaseGoal" :depends-on ("_package"))
    (:file "SoftMoveBaseResult" :depends-on ("_package_SoftMoveBaseResult"))
    (:file "_package_SoftMoveBaseResult" :depends-on ("_package"))
  ))