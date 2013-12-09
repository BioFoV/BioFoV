#ifndef PLAYER_HPP
#define PLAYER_HPP

// OpenCV
#ifndef OPENCV_INC
#define OPENCV_INC
#include <opencv2/opencv.hpp>
#endif

/*******************************************************************************
 * Purelly virtual class intended to make a single interface for reading frames
 *for both Video and Event, and actually anything else that comes after
 ******************************************************************************/
class Player
{
public:
    // Capture functions
    virtual bool check_cap() = 0;
    virtual bool setFramePos(double frameNum) = 0;
    virtual double getFramePos() = 0;
    virtual cv::Mat* getFrame() = 0;
    virtual bool getPrevFrame(cv::Mat &frame) = 0;

    // Properties
    virtual double getFrameInt() = 0;
    virtual double getFPS() = 0;
    virtual double getLengthTime() = 0;
    virtual double getLengthFrames() = 0;
};

#endif // PLAYER_HPP
