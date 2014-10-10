#ifndef VIDEO_H
#define VIDEO_H

// OpenCV
#ifndef OPENCV_INC
#define OPENCV_INC
#include <opencv2/opencv.hpp>
#endif

#ifndef INC_FRAME
#define INC_FRAME
#include <Frame/Frame.hpp>
#endif

#ifndef INC_BGSUB
#define INC_BGSUB
#include "BackgroundSubtraction.hpp"
#endif

#ifndef INC_EVENT
#define INC_EVENT
#include <Event/Event.hpp>
#endif

#ifndef INC_CAMERA
#define INC_CAMERA
#include <camera.hpp>
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

#ifndef INC_DIALOGSETTINGS
#define INC_DIALOGSETTINGS
#include "QdialogSettings.hpp"
#endif

//#include "QitemVideo.hpp"

#define NOTCALIBRATED -1

#include <QObject>

#include <QCoreApplication>

class Frame;
class Event;
/**
 * @brief EventPtr
 */
typedef QSharedPointer<Event> EventPtr;

class Camera;

class Video;
/**
 * @brief VideoPtr
 */
typedef QSharedPointer<Video> VideoPtr;

/**
 * @brief Class that holds the VideoCapture handler and that provides frames
 */
class Video : public QObject, public Player {
    Q_OBJECT

signals:
    void startProgress(unsigned int min, unsigned int max);
    void progressChanged(unsigned int val);
    QdialogSettings* getSettings();

private:
    /**
     * @brief CV Capture interface of this Video.
     */
    cv::VideoCapture cap;

    /**
     * @brief Video file name.
     */
	std::string filename;

    /**
     * @brief Video frame rate.
     */
    double fps;

    /**
     * @brief Video resolution.
     */
    cv::Size resolution;

    /**
     * @brief Camera of the Video.
     * Describes the camera model of the Video capture device (camera in real
     * life). One camera may be associated with several videos.
     */
    Camera* cam;

    /**
     * @brief toCancel
     */
    bool toCancel;

    std::string getCacheDir();

    void canceled();

public:
	// Atributes
    /// \brief CV Background Subtractor object.
    /// Does the heavy lifting of the background subtraction.
	BackgroundSubtractor * bg;

    Video();
    Video(cv::VideoCapture capture);
	Video(std::string name);
	
    virtual ~Video();

    // Set and Get
    void setFileName(std::string name);
    std::string getFileName();
    void setCapture(cv::VideoCapture capture);
    cv::VideoCapture getCapture();
	
    // Capture functions implemented by player
	bool check_cap();
    bool setFramePos(double frameNum);
    double getFramePos();
    bool getFrame(cv::Mat &frame);
    bool getPrevFrame(cv::Mat &frame);
    bool getNextFrame(cv::Mat &frame);
    FramePtr getCurrentFrameRef();
    uint getCurrentFrameNumber();

    bool stepForward();
    bool stepBackwards();

    // Properties
    double getFrameInt();
    double getFPS();
    double getLengthTime();
    double getLengthFrames();

    void mousePressEvent(cv::Point);
    void mouseReleaseEvent(cv::Point);
    void mouseMoveEvent(cv::Point);

    void save(std::string /*fname*/);

    cv::Size getSize();
    bool isCalibrated();
	
    // BackgroundSubtraction functions
	void bgSubInit(int hist, int varThresh, bool bShadowDet);
	void bgSubDelete();

    EventPtr convertToEvent(std::string path);

    std::deque<EventPtr> autoDetectEvents(double threshold,
                                         double maxcount,
                                         double mincount,
                                         int history,
                                         int varThreshold,
                                         bool bShadowDetection,
                                         std::string path);

    void calibrate(int nBoards, int frameStep, int boardW,
                   int boardH, int iterations, unsigned int flags);
    void deleteCalibration();

    Camera* getCamera();
    bool importCamera();

    void flip_horizontally();
    void flip_vertically();

signals:
    void updateValues();

public slots:
    void cancel();
};
#endif
