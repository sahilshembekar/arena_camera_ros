// ROS
#include <stdlib.h>
#include <ros/ros.h>
#include <sensor_msgs/CameraInfo.h>
#include <sensor_msgs/Image.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/opencv.hpp>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>

class ConverterTest
{
    public:
    ConverterTest(ros::NodeHandle *nh);
    ros::Publisher img_pub;

    private:
    ros::Subscriber img_sub;
    void imageCallback(const sensor_msgs::Image &msg);

};