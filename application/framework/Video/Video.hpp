#ifndef VIDEO_H
#define VIDEO_H

// OpenCV
#ifndef OPENCV_INC
#define OPENCV_INC
#include <opencv2/opencv.hpp>
#endif

#ifndef INC_FRAME
#define INC_FRAME
#include "../Frame/Frame.hpp"
#endif

#ifndef INC_BGSUB
#define INC_BGSUB
#include "BackgroundSubtraction.hpp"
#endif

#ifndef INC_EVENT
#define INC_EVENT
#include "../Event/Event.hpp"
#endif

#ifndef INC_CAMERA
#define INC_CAMERA
#include "../camera.hpp"
#endif

//#ifndef INC_LIST
//#define INC_LIST
//#include <list>
//#endif

#ifndef INC_STRING
#define INC_STRING
#include <string>
#endif

#ifndef INC_PLAYER
#define INC_PLAYER
#include "../player.hpp"
#endif

#define NOTCALIBRATED -1

class Frame;
class Event;
class Camera;

///
/// \brief Class that holds the VideoCapture handler and that provides frames
///
class Video : public Player {
private:
    /// \brief CV Capture interface of this Video.
    cv::VideoCapture cap;

    /// \brief deque of the ordered frames.
    std::deque<Frame*> frames;

    /// \brief deque of the ordered events.
    std::deque<Event*> events;

    /// \brief Video file name.
	std::string filename;

    /// \brief Video frame rate.
    double fps;

    /// \brief Video resolution.
    cv::Size resolution;

    /// \brief Camera of the Video.
    /// Describes the camera model of the Video capture device (camera in real
    /// life). One camera may be associated with several videos.
    Camera* cam;

    /// \brief Is the video calibrated or not?
    /// If this variable is true, then there should be a Camera pointed by cam.
    bool calibrated;
	
public:
	// Atributes
    /// \brief CV Background Subtractor object.
    /// Does the heavy lifting of the background subtraction.
	BackgroundSubtractor * bg;

	// Constructors
    /// \brief Plain Video constructor.
	Video();

    /// \brief Video constructer providing cv VideoCapture.
    /// \param capture CV capture object.
    Video(cv::VideoCapture capture);

    /// \brief Video constructor providing a file name.
    /// \param name file name.
	Video(std::string name);
	
	// Destructors
    /// \brief Video destructor.
	~Video();

    // Set and Get
    /// \brief Changes the filename to the string provided.
    /// \param name new filename.
    void setFileName(std::string name);

    /// \brief Get filename variable.
    /// \return filename of the Video if there is one, otherwise returns NULL.
    std::string getFileName();

    /// \brief Changes the CV VideoCapture object to a new one.
    /// \param capture new CV VideoCapture object of the Video.
    void setCapture(cv::VideoCapture capture);

    /// \brief Get CV VideoCapture object.
    /// \return CV VideoCapture object of the Video.
    cv::VideoCapture getCapture();
	
    // Capture functions implemented by player
	bool check_cap();
    bool setFramePos(double frameNum);
    double getFramePos();
    bool getFrame(cv::Mat &frame);
    bool getPrevFrame(cv::Mat &frame);

    // Properties
    double getFrameInt();
    double getFPS();
    double getLengthTime();
    double getLengthFrames();
    cv::Size getSize();
    bool isCalibrated();
	
	// BackgroundSubtraction functions
    /// \brief Initializes the CV background subtractor object.
    /// \param hist
    /// \param varThresh
    /// \param bShadowDet
	void bgSubInit(int hist, int varThresh, bool bShadowDet);

    /// \brief Purges the CV background subtractor object linked to this Video.
	void bgSubDelete();

    // Event autoDetection
    /// \brief Automatically splits the video into several events provided the
    /// given parameters.
    /// \param threshold
    /// \param maxcount
    /// \param mincount
    /// \param history
    /// \param varThreshold
    /// \param bShadowDetection
    /// \return
    std::deque<Event *> autoDetectEvents(double threshold,
                                         double maxcount,
                                         double mincount,
                                         int history,
                                         int varThreshold,
                                         bool bShadowDetection);

    // Calibration
    /// \brief Calibrates the camera based on this Video.
    /// If this Video has enough chessboard pattern frames on it, and they are
    /// described by the arguments given to the function, the function will
    /// calibrate the video and after the call, all other player implemented
    /// functions that ask for a frame will have an undistorted frame.
    /// \param nBoards Maximum number of boards to be detected.
    /// After this number, it stops. Use frameStep to skip frames if there are a
    /// lot of frames with similar pattern positions.
    /// \param frameStep Steps frames to avoid similar ones.
    /// \param boardW Number of inner corners of the pattern, on width.
    /// \param boardH Number of inner corners of the pattern, on height.
    /// \param iterations Number of iterations to be passed to the
    /// BackgroundSubtractor object.
    /// 1~5 is normally enough.
    void calibrate(int nBoards, int frameStep, int boardW,
                   int boardH, int iterations);
};
#endif
