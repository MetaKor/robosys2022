#!/usr/bin/env python
import rospy
from geometry_msgs.msg import Twist

def vel_pub():
    pub = rospy.Publisher('cmd_vels', Twist, queue_size=10)
    rospy.init_node('vel_publisher', anonymous=True)
    rate = rospy.Rate(1) # 5hz
    
    i = 0
    while not rospy.is_shutdown():
        
        cmd_twist = Twist()
        cmd_twist.linear.x = (i % 100)*10.0
        cmd_twist.angular.z = (i % 100)*10.0

        rospy.loginfo(cmd_twist)
        pub.publish(cmd_twist)
        rate.sleep()
        i += 1

if __name__ == '__main__':
    try:
        vel_pub()
    except rospy.ROSInterruptException:
        pass