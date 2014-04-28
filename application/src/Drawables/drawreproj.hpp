#ifndef DRAWREPROJ_HPP
#define DRAWREPROJ_HPP

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
class DrawReproj : public Drawable
{
private:
    /// \brief Vector to store the points.
    ///Store the four reference points plus the height point.
    cv::Point2f points[4];
    /// \brief Number of points inserted so far.
    int npoints;

    bool calculated;
    cv::Mat persptransf;

    double referential_width;
    double referential_height;
    double height;
    double ratio;
public:
    /// \brief Simple constructor.
    DrawReproj();
    ~DrawReproj();
    void press(cv::Point);
    void release(cv::Point pi2);
    void draw(cv::Mat& frame);
    void move(cv::Point);
    bool isDone();

    std::string getDescription();

    bool isCalculated();
    void calcUndistort();
    void undistort(cv::Mat& frame);
};

#endif // DRAWHEIGHT_HPP
