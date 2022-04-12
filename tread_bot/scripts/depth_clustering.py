#!/usr/bin/env python3
import rospy
from sensor_msgs.msg import Image
from geometry_msgs.msg import Twist
from cv_bridge import CvBridge
import cv2
import numpy as np


class DepthCluster:
    def __init__(self):
        # Params
        self.image = None
        self.twist = Twist()
        self.br = CvBridge()

        self.blur_rad = 11
        self.near_threshold = 400

        # Node cycle rate (in Hz)
        self.loop_rate = rospy.Rate(4)

        # Publishers
        self.pub = rospy.Publisher("cmd_vels", Twist, queue_size=10)

        # Subscribers
        rospy.Subscriber("/camera/depth/image_rect_raw", Image, self.callback)  # /camera/color/image_raw

    def callback(self, msg):
        #rospy.loginfo("Image received with encoding " + str(msg.encoding))
        self.image = self.br.imgmsg_to_cv2(msg, "16UC1")

    def start(self):
        rospy.loginfo("Starting depth clustering")

        while not rospy.is_shutdown():
            
            if self.image is not None:
                
                self.process_image()
                self.pub.publish( self.twist )
                
                #cv2.imshow('ImageWindow', self.image)
                #cv2.waitKey(0.1)

            self.loop_rate.sleep()
    
    def process_image(self):
        self.image[self.image == 0] = self.near_threshold*2
        self.blur = cv2.GaussianBlur(self.image, (self.blur_rad, self.blur_rad), cv2.BORDER_DEFAULT)
        self.cropped = self.blur[0:round(self.blur.shape[1]*0.4), :]

        (minVal, maxVal, minLoc, maxLoc) = cv2.minMaxLoc(self.cropped)

        if minVal < self.near_threshold:
            self.twist.linear.x = 0
            rospy.loginfo(str(minLoc))
            rospy.loginfo(str(self.cropped.shape[1]/2))
            if minLoc[0] < (self.cropped.shape[1]/2):
                self.twist.angular.z = 3
            else:
                self.twist.angular.z = -3
            rospy.loginfo("Nearby obstacle - angular vel set to " + str(self.twist.angular.z))
        else:
            self.twist.linear.x = 0.5
            self.twist.angular.z = ((self.cropped.shape[1]/2) - maxLoc[0]) * 0.01
            rospy.loginfo("Seeking far - angular vel set to " + str(self.twist.angular.z))


if __name__ == "__main__":
    rospy.init_node("depth_clusterer", anonymous=True)
    cluster_node = DepthCluster()
    cluster_node.start()