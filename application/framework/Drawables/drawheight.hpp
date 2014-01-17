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

///
/// \brief Calculate the height/width of a certain object/person.
///Implementation of Drawable class.
///
class DrawHeight : public Drawable
{
private:
    /// \brief Vector to store the points.
    ///Store the four reference points plus the height point.
    cv::Point2f points[5];
    /// \brief Number of points inserted so far.
    unsigned int npoints;
public:
    /// \brief Simple constructor.
    DrawHeight();
    ~DrawHeight();
    void press(cv::Point pi1);
    bool release(cv::Point pi2);
    void draw(cv::Point pi2, cv::Mat& frame);
    double apply(cv::Mat &frame);
};

#endif // DRAWHEIGHT_HPP
