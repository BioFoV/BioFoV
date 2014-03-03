#ifndef PLAYER_HPP
#define PLAYER_HPP

#ifndef INC_FRAME
#define INC_FRAME
#include "Frame/Frame.hpp"
#endif

// OpenCV
#ifndef OPENCV_INC
#define OPENCV_INC
#include <opencv2/opencv.hpp>
#endif

///
/// \brief Interface for VideoPlayer.
/// The Player class functions as a purelly virtual class intended to
///make a single interface for reading frames and getting data from both Video
///and Event, and actually anything else that comes after.
///
class Player
{
public:
    // Capture functions
    /// \brief checks whether the capture interface is valid or not.
    /// \return whether the capture interface is valid or not.
    virtual bool check_cap() = 0;

    /// \brief Jumps the Player to the given frameNum.
    /// \param frameNum Number of the frame to jump to.
    /// \return Whether the provided frameNum was valid (in bounds).
    virtual bool setFramePos(double frameNum) = 0;

    /// \brief Gets the current position of Player.
    /// \return Current frame number.
    virtual double getFramePos() = 0;

    /// \brief Gets the next frame available in the Player.
    /// \param frame Reference of the cv::Mat object where to put the read
    ///frame.
    /// \return Wheather the Player was successful into fetching the new frame.
    virtual bool getFrame(cv::Mat &frame) = 0;

    /// \brief Gets the next frame available in the Player.
    /// \param frame Reference of the cv::Mat object where to put the read
    ///frame.
    /// \param direction true is forward, false is rewind.
    /// \return Wheather the Player was successful into fetching the new frame.
    virtual bool getNextFrame(cv::Mat &frame) = 0;

    /// \brief Gets the previous frame available in the Player.
    /// \param frame Reference of the cv::Mat object where to put the read
    ///frame.
    /// \return Wheather the Player was successful into fetching the new frame.
    virtual bool getPrevFrame(cv::Mat &frame) = 0;

    // Properties
    /// \brief Gets the interval between frames in seconds.
    /// \return Interval between frames in seconds.
    virtual double getFrameInt() = 0;

    /// \brief Gets the frame per second count.
    /// \return FPS.
    virtual double getFPS() = 0;

    /// \brief Gets the length of the video in seconds.
    /// \return Length of the video in seconds.
    virtual double getLengthTime() = 0;

    /// \brief Gets the length of the video in frames.
    /// \return Length of the video in frames.
    virtual double getLengthFrames() = 0;

    virtual void* getCurrentFrameRef() = 0;

    virtual void mousePressEvent(cv::Point point) = 0;
    virtual void mouseReleaseEvent(cv::Point point) = 0;
    virtual void mouseMoveEvent(cv::Point point) = 0;
};

#endif // PLAYER_HPP
