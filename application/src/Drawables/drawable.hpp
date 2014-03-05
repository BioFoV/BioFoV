#ifndef DRAWABLE_HPP
#define DRAWABLE_HPP

// OpenCV
#ifndef OPENCV_INC
#define OPENCV_INC
#include <opencv2/opencv.hpp>
#endif

typedef std::pair<std::string, double> TStrDoublePair;
typedef std::deque<TStrDoublePair> TStrDoubleMap;

///
/// \brief The Drawable class implements a point and click modifier to allow
///measurements or input by the user in the Player.
///
class Drawable
{
public:
    Drawable();
    /// \brief Function to be called on cursor press.
    /// \param pi1 Point where cursor was pressed.
    virtual void press(cv::Point pi1) = 0;
    /// \brief Function to be called on cursor release.
    /// \param pi2 Point where cursor was released.
    /// \return Whether there is the need for more points or not.
    virtual void release(cv::Point pi2) = 0;

    /// \brief Draw something.
    /// \param pi2 Point where mouse is at the moment of draw.
    /// \param frame Reference to the image where to draw
    virtual void draw(cv::Mat& frame) = 0;

    virtual void move(cv::Point point) = 0;

    virtual bool isDone() = 0;

    virtual std::string getDescription() = 0;

    TStrDoubleMap getValues();

    bool isVisible();
    void setVisible(bool value);

protected:
    TStrDoubleMap values;
    bool visible;
};

#endif // DRAWABLE_HPP
