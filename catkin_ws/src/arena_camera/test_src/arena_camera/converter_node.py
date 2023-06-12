#! /usr/bin/env python3

import rospy
from sensor_msgs.msg import Image
from cv_bridge import CvBridge, CvBridgeError
import cv2

class ConverterNode:
    def __init__(self):
        rospy.init_node('converter_node')
        rospy.Subscriber("arena_camera_node/image_raw", Image, self.image_callback)
        self.image_pub = rospy.Publisher('converted_image', Image, queue_size=10)
        self.bridge = CvBridge()

    def image_callback(self, msg):
        try:
            # Convert the ROS Image message to OpenCV format
            cv_image = self.bridge.imgmsg_to_cv2(msg, desired_encoding='passthrough')
            cv2.imshow('cv_image', cv_image)
            
            # cv_image is 16UC4 

            # cv_image_3d = cv2.Mat
            # cv_image_2d = cv2.Mat
            # cv_image_3d = cv_image  

            # cv_image_3d.convertTo(cv_image_2d, CV_8U)
            # Convert the image data from '16UC4' to 'rgb8' format
            cv_image_rgb = cv2.cvtColor(cv_image, cv2.COLOR_BGR2RGB)

            # Process the converted image
            self.image_pub.publish(cv_image_rgb)

        except CvBridgeError as e:
            rospy.logerr(e)

