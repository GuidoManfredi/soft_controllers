
(cl:in-package :asdf)

(defsystem "head_tracking_soft_controller-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "PanTilt" :depends-on ("_package_PanTilt"))
    (:file "_package_PanTilt" :depends-on ("_package"))
  ))