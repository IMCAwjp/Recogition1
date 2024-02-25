#include"discern/pnp.hpp"
namespace Identify
{
    void pnp::solvepnp(const Feature & F)
    {
    std::vector<cv::Point2f> imagepoints;
    imagepoints.push_back(F.image_points.right_top);
    imagepoints.push_back(F.image_points.right_buttom);
    imagepoints.push_back(F.image_points.left_top);
    imagepoints.push_back(F.image_points.left_buttom);

    cv::Point3f Left_Top = cv::Point3f(-25.0,35.0,0.0);
    cv::Point3f Left_Bottom =cv::Point3f (-25.0,-35.0,0.0);
    cv::Point3f Right_Top = cv::Point3f(25.0,35.0,0.0);
    cv::Point3f Right_Bottom = cv::Point3f(25.0,-35.0,0.0);
    std::vector<cv::Point3f> objectpoints;
    objectpoints.push_back(Right_Top);
    objectpoints.push_back(Right_Bottom);
    objectpoints.push_back(Left_Top);
    objectpoints.push_back(Left_Bottom);

    

    cv::solvePnP(objectpoints,imagepoints,cameraMatrix,disCoeffs,rvec,tvec);
    

    distance = sqrt(std::pow(tvec.at<double>(0,0),2)+std::pow(tvec.at<double>(0,0),2)+std::pow(tvec.at<double>(0,0),2)) / 10;
    
    double tan_value = tvec.at<double>(0,0) / tvec.at<double>(2,0);
    angle = 180.0/M_PI * atan(tan_value);


    }
    
    
}