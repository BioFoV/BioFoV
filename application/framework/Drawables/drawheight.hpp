#ifndef DRAWHEIGHT_HPP
#define DRAWHEIGHT_HPP

// OpenCV
#ifndef OPENCV_INC
#define OPENCV_INC
#include <opencv2/opencv.hpp>
#endif

#include "drawable.hpp"

/// Defines the radius of the clicked point markers (independent of image
///resolution.
#define CIRCLE_RATIO .01
/// Defines the thickness of the lines (independent of image resolution.
#define LINE_RATIO .002

class DrawHeight : public Drawable
{
private:
    cv::Point2f points[4];
    unsigned int npoints;
public:
    DrawHeight();
    void press(cv::Point pi1);
    bool release(cv::Point pi2);
    void draw(cv::Point pi2, cv::Mat& frame);
    void apply(cv::Mat &frame);
};

#endif // DRAWHEIGHT_HPP
