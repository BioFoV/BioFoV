#ifndef DRAWLENGTH_HPP
#define DRAWLENGTH_HPP

// OpenCV
#ifndef OPENCV_INC
#define OPENCV_INC
#include <opencv2/opencv.hpp>
#endif

#ifndef INC_DRAWABLE
#define INC_DRAWABLE
#include "drawable.hpp"
#endif

/// Defines the radius of the clicked point markers (independent of image
///resolution.
#define CIRCLE_RATIO .01
/// Defines the thickness of the lines (independent of image resolution.
#define LINE_RATIO .002

class DrawLength : public Drawable
{
private:
    cv::Point2f points[2];
    int npoints;
    double result;

public:
    DrawLength();
    ~DrawLength();
    void press(cv::Point);
    void release(cv::Point pi2);
    void draw(cv::Mat& frame);
    void move(cv::Point);
    bool isDone();

    std::string getDescription();
};

#endif // DRAWLENGTH_HPP
