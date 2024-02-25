//Custom header files
#include"discern/color_node.hpp"

//ros2
#include<rclcpp/qos.hpp>
#include<cv_bridge/cv_bridge.h>
#include<sensor_msgs/image_encodings.hpp>
//opencv
#include<opencv2/imgproc.hpp>
#include<opencv2/highgui.hpp>
namespace Identify
{

    Id_node::Id_node(const rclcpp::NodeOptions & options):Node("armor_tracker", options)
    {
    //RCLCPP_INFO(this->get_logger(),"%s : is working!",name.c_str());
    Sub_ = this->create_subscription<sensor_msgs::msg::Image>(
        "/image_raw",rclcpp::SensorDataQoS(),std::bind(&Id_node::sub_callback,this,std::placeholders::_1)
    );
    Pub_ = this->create_publisher<sensor_msgs::msg::Image>
    (
        "/image_pub",rclcpp::SensorDataQoS()
    );

    double max = this->declare_parameter("max_area", 100.0);

    double min = this->declare_parameter("min_area", 4500.0);

    double art = this->declare_parameter("artio", 1.5);

    Feature_ = std::make_unique<Feature>(min, max,art);
    }


    void Id_node::sub_callback(const sensor_msgs::msg::Image::SharedPtr msg)
    {
    //The image format is converted from ros2  to opencv   
    cv::Mat src = cv_bridge::toCvShare(msg,"bgr8")->image;

    //Treating processes
    cv::Mat src_hsv;

    cv::cvtColor(src,src_hsv,cv::COLOR_BGR2HSV);


   
    sensor_msgs::msg::Image image;
  
    std_msgs::msg::Header header;
    //The image format is converted from opencv to ros2
    try
    {
        Pub_->publish(
            *cv_bridge::CvImage(header,sensor_msgs::image_encodings::BGR8,src).toImageMsg()
        );
    }
    catch(const cv_bridge::Exception& e)
    {
        RCLCPP_ERROR(this->get_logger(),"Couldn't convert cv to ros2 !");
    }  
    }
}

#include "rclcpp_components/register_node_macro.hpp"
 

RCLCPP_COMPONENTS_REGISTER_NODE(Identify::Id_node)