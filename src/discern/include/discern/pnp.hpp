#ifndef PNP_HPP
#define PNP_HPP
#include"discern/object_feature.hpp"
namespace Identify
{
    class pnp
    {
    public:
    explicit pnp(){};
    ~pnp(){}
    double distance;
    double angle;
    void solvepnp(const Feature & F);
    private:
  
    cv::Mat cameraMatrix = (cv::Mat_<double>(3,3)<<
    1750.345804, 0.000000, 642.779064,
    0.000000 ,1751.749379 ,492.265888,
    0.000000, 0.000000 ,1.000000
    );
     cv::Mat disCoeffs = (cv::Mat_<double>(1,5)<<
    -0.067513, 0.257146 ,-0.001437 ,-0.000258 ,0.000000
    );
    cv::Mat rvec;
    cv::Mat tvec;
    };
    }
#endif