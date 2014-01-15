#ifndef RECTANGLEMASK_HPP
#define RECTANGLEMASK_HPP

// OpenCV
#ifndef OPENCV_INC
#define OPENCV_INC
#include <opencv2/opencv.hpp>
#endif

#include "drawable.hpp"

///
/// \brief Select a rectangle area end exclude it from background subtraction.
///Implementation of Drawable.
///
class RectangleMask : public Drawable
{
private:
    /// \brief p Points that define the rectangle.
    cv::Point p[2];

public:
    /// \brief Simple Constructor.
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
