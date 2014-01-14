#ifndef RECTANGLEMASK_HPP
#define RECTANGLEMASK_HPP

// OpenCV
#ifndef OPENCV_INC
#define OPENCV_INC
#include <opencv2/opencv.hpp>
#endif

#include "drawable.hpp"

class RectangleMask : public Drawable
{
private:
    cv::Point p1, p2;

public:
    RectangleMask();
    // Click
    void press(cv::Point pi1);
    bool release(cv::Point pi2);

    // Draw
    void draw(cv::Point pi2, cv::Mat& frame);

    // Apply
    double apply(cv::Mat &frame);
};

#endif // RECTANGLEMASK_HPP
