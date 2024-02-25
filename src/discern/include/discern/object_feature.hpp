#ifndef OBJECT_FEATURE_HPP
#define OBJECT_FEATURE_HPP
#include<opencv2/opencv.hpp>
namespace Identify
{
    class Feature
    {

    public:
    explicit Feature(double min ,double max ,double ratio);

    struct points
    {
        cv::Point2f right_top;
        cv::Point2f right_buttom;
        cv::Point2f left_top;
        cv::Point2f left_buttom;
    };

    points image_points;
    
    cv::Mat mask;
    
    //Any sign of the target object
    bool success;
    
    //
    void red_find(const cv::Mat & src);

    void blue_find(const cv::Mat & src);
    
    void green_find(const cv::Mat & src);
    
    //Detects the target object and returns a value of type bool
    bool select();
    
    private:
    
    //Screeninng condition
    double min_area;

    double max_area;

    double ratio;

    };
}
#endif