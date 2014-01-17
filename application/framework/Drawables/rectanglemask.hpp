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
    /// \brief Simple Destructor.
    ~RectangleMask();
    // Click
    /// \brief Stores the 1st Point.
    /// \param pi1 Point where the left mouse button was clicked.
    void press(cv::Point pi1);
    /// \brief Stores the 2nd Point.
    /// \param pi2 Point where the left mouse button was released.
    /// \return Always returns false since there is not needed any more Points.
    bool release(cv::Point pi2);

    // Draw
    /// \brief Draws the rectangle in the image.
    /// \param pi2 Point where the cursor is at the moment.
    /// \param frame Image on which to draw the rectangle.
    void draw(cv::Point pi2, cv::Mat& frame);

    // Apply
    double apply(cv::Mat &frame);
};

#endif // RECTANGLEMASK_HPP
