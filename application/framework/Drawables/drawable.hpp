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
    ///
    /// \brief function to be called on cursor release.
    /// \param pi2 Point where cursor was released.
    /// \return Whether there is the need for more points or not.
    ///
    virtual bool release(cv::Point pi2) = 0;

    // Draw
    virtual void draw(cv::Point pi2, cv::Mat& frame) = 0;

    // Apply
    virtual void apply(cv::Mat &frame) = 0;
};

#endif // DRAWABLE_HPP
