#ifndef DRAWHEIGHT_HPP
#define DRAWHEIGHT_HPP

// OpenCV
#ifndef OPENCV_INC
#define OPENCV_INC
#include <opencv2/opencv.hpp>
#endif

#include "drawable.hpp"

class DrawHeight : public Drawable
{
private:
    cv::Point points[4];
    unsigned int npoints;
public:
    DrawHeight();
    void press(cv::Point pi1);
    bool release(cv::Point pi2);
    void draw(cv::Point pi2, cv::Mat& frame);
    void apply();
};

#endif // DRAWHEIGHT_HPP
