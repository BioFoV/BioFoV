#ifndef DRAWHEIGHT_HPP
#define DRAWHEIGHT_HPP

// OpenCV
#ifndef OPENCV_INC
#define OPENCV_INC
#include <opencv2/opencv.hpp>
#endif

#ifndef INC_DRAWABLE
#define INC_DRAWABLE
#include <Drawables/drawable.hpp>
#endif

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
    cv::Point2f points[2];

    /// \brief Vector to store the auxiliar points used in the drawing.
    cv::Point2f auxpoints[2];

    /// \brief Number of points inserted so far.
    int npoints;

    bool calculated;
    cv::Mat persptransf;

public:
    /// \brief Simple constructor.
    DrawHeight();
    ~DrawHeight();
    void press(cv::Point);
    void release(cv::Point pi2);
    void draw(cv::Mat& frame);
    void move(cv::Point);
    bool isDone();

    std::string getDescription();
};

#endif // DRAWHEIGHT_HPP
