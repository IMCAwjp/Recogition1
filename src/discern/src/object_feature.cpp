#include"discern/object_feature.hpp"
#include"discern/color_staus.hpp"
namespace Identify
{

        Feature::Feature(double min, double max, double ratio) : success(false), min_area(min), max_area(max),ratio(ratio) {};

        void Feature::red_find(const cv::Mat & src)
        {
            cv::inRange(src,red_low,red_high,mask);
        }

        void Feature::blue_find(const cv::Mat & src)
        {
            cv::inRange(src,blue_low,blue_high,mask);
        }

        void Feature::green_find(const cv::Mat & src)
        {
            cv::inRange(src,green_low,green_high,mask);
        }

        bool Feature::select()
        {
            std::vector<std::vector<cv::Point2f>> contours;

            cv::findContours(mask,contours,cv::RETR_EXTERNAL,cv::CHAIN_APPROX_NONE);

            contours.erase(
            std::remove_if(
            contours.begin(), contours.end(),
            [this](const std::vector<cv::Point2f> & a) {
                double area = cv::contourArea(a);
            return area < min_area || area > max_area;
                }),
            contours.end());

            contours.erase(
            std::remove_if(
            contours.begin(), contours.end(),
            [this](const std::vector<cv::Point2f> & a) {
                cv::RotatedRect rect = cv::minAreaRect(a);
                double it_ratio = rect.size.height>rect.size.width ? rect.size.height / rect.size.width : rect.size.width/rect.size.height;
                return it_ratio > ratio;
                }),
            contours.end());
            if(!contours.empty())
            {

            sort(contours.begin(),contours.end(),[](const std::vector<cv::Point2f> & a,const std::vector<cv::Point2f> & b)
            {return cv::contourArea(a) > cv::contourArea(b);});
            
            cv::RotatedRect rect = cv::minAreaRect(contours[0]);

            contours.clear();

            cv::Point2f p[4];

            rect.points(p);

            if(rect.size.height > rect.size.width)
            {
            image_points.right_top = p[2];

            image_points.right_buttom = p[3];

            image_points.left_top = p[1];

            image_points.left_buttom = p[0];
            }
            else
            {

            image_points.right_top = p[3];

            image_points.right_buttom = p[0];

            image_points.left_top = p[2];

            image_points.left_buttom = p[1];

            }

            success = true;
            
            return true;
            }
            else return false;
        }
}

            