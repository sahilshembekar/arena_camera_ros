#include <arena_camera/converter_test.h>


ConverterTest::ConverterTest(ros::NodeHandle *nh)
{
    img_sub = nh->subscribe("/arena_camera_node/image_raw", 10, 
                            &ConverterTest::imageCallback,
                            this);
    img_pub = nh->advertise<sensor_msgs::Image>("/converted_image", 100);
} 
   
void ConverterTest::imageCallback(const sensor_msgs::Image &msg)
{
    cv_bridge::CvImagePtr cv_ptr_1_;
    cv_bridge::CvImagePtr cv_ptr_2_;
    
    try
    {
        std::cout << "before cv_ptr_1" << std::endl;
        cv_ptr_1_ = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::MONO16);
        std::cout << "before cv_ptr_2" << std::endl;
        cv_ptr_2_ = cv_bridge::toCvCopy(cv_ptr_1_, sensor_msgs::image_encodings::RGB8);
    }

    catch (cv_bridge::Exception& e)
    {
        ROS_ERROR("cv_bridge exception: %s", e.what());
        return;
    }
    std::cout << "before publish" << std::endl;
    img_pub.publish(cv_ptr_2_->image);

    // cv_ptr->image;
    // cv::Mat ImgColor = imread("1. jpg", IMREAD_COLOR); 
    // cv::Mat ImgGray = imread("1. jpg", IMREAD_GRAYSCALE); 
    // std::cout << "original" << std::endl;
    // std::cout << "ImgColor.type()" << cv_ptr->image->type () << std::endl;
    // std::cout << "ImgGray.type()" << ImgGray.type() << std::endl << std::endl;
    
    // cv::Mat ImgColorC3;
    // cv::Mat ImgGrayC3;
    // ImgColor.convertTo(ImgColorC3, CV_16UC3);
    // ImgGray.convertTo(ImgGrayC3, CV_16UC3); 
    // std::cout << "convertTo CV 16UC3" << std::endl;
    // std::cout << "ImgColorC3.type() " << ImgColorC3.type() << std::endl; 
    // std::cout << "ImgGrayC3.type() " << ImgGrayC3.type() << std::endl << std::endl;
    
    // cv::Mat ImgColorC1;
    // cv::Mat ImgGrayC1;
    // ImgColor.convertTo(ImgColorC1, CV_16UC1);
    // ImgGray. convertTo (ImgGrayC1, CV_16UC1); 
    // std::cout << "convertTo CV_16UC1" << std::endl;
    // std::cout << "ImgColorC1.type() " << ImgColorC1.type() << std::endl; 
    // std::cout << "ImgGrayC1. type()" << ImgGrayC1.type() << std::endl << std::endl;

    // ImgColor.convertTo(ImgColor, CV_16UC3);
    // ImgGray.convertTo(ImgGray, CV_16UC3);
    // std::cout << "in place" << std::endl;
    // std::cout << "ImgColor.type() " << ImgColor.type() << std::endl; 
    // std::cout << "ImgGray.type()" << ImgGray.type() << std::endl << std::endl;    
}


int main(int argc, char **argv)
{
    // initialise ROS stuff
    ros::init(argc, argv, "converter_test_node");
    ros::NodeHandle nh("~");

    int seed = time(NULL);
    srand(seed);

    // set up controller object
    ConverterTest converter_test(&nh);
    ROS_INFO("Converter Test: initialised");

    ros::Rate rate(10);
    while (ros::ok())
    {
        ros::spinOnce();
        rate.sleep();
    }

    ROS_INFO("Converter Test node: finished safely");
    return 0;
}