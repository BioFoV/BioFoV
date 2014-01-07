#ifndef DRAWABLE_HPP
#define DRAWABLE_HPP

// OpenCV
#ifndef OPENCV_INC
#define OPENCV_INC
#include <opencv2/opencv.hpp>
#endif

class Drawable
{
public:
    // Click
    virtual void press(cv::Point pi1) = 0;
    virtual void release(cv::Point pi2) = 0;

    // Draw
    virtual void draw(cv::Point pi2, cv::Mat& frame) = 0;

    // Apply
    virtual void apply() = 0;
};

#endif // DRAWABLE_HPP
