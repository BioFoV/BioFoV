#ifndef RECTANGLEMASK_HPP
#define RECTANGLEMASK_HPP

// OpenCV
#ifndef OPENCV_INC
#define OPENCV_INC
#include <opencv2/opencv.hpp>
#endif

#ifndef INC_DRAWABLE
#define INC_DRAWABLE
#include "drawable.hpp"
#endif

/**
 * @brief Select a rectangle area end exclude it from background subtraction.
 * Implementation of Drawable.
 */
class RectangleMask : public Drawable
{
private:
    /**
     * @brief Points that define the rectangle.
     */
    cv::Point p[2];

    /**
     * @brief finished
     */
    bool finished;

public:
    RectangleMask();
    ~RectangleMask();

    void press(cv::Point pi1);
    void release(cv::Point pi2);
    void draw(cv::Mat& frame);
    void move(cv::Point point);
    bool isDone();

    std::string getDescription();
    std::string getIcon();
};

#endif // RECTANGLEMASK_HPP
