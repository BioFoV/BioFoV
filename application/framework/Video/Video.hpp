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

#ifndef INC_LIST
#define INC_LIST
#include <list>
#endif

#ifndef INC_STRING
#define INC_STRING
#include <string>
#endif

#ifndef INC_PLAYER
#define INC_PLAYER
#include "../player.hpp"
#endif

class Frame;
class Event;

/*
 * Class that holds the VideoCapture handler and that provides frames
 */
class Video : public Player {
private:
    cv::VideoCapture cap;
    std::deque<Frame*> frames;
    std::deque<Event*> events;
	std::string filename;
    double fps;
    double resolution[2];
    double position;
    double lengthFrames;
	
public:
	// Atributes
	BackgroundSubtractor * bg;

	// Constructors
	Video();
    Video(cv::VideoCapture capture);
	Video(std::string name);
	
	// Destructors
	~Video();

    // Set and Get
    void setFileName(std::string);
    std::string getFileName();
    void setCapture(cv::VideoCapture capture);
    cv::VideoCapture getCapture();
	
	// Capture functions
    double readAll();
	bool check_cap();
    bool setFramePos(double frameNum);
    double getFramePos();
    cv::Mat* getFrame();
    cv::Mat* getPrevFrame();

    // Properties
    double getFrameInt();
    double getFPS();
    double getLengthTime();
    double getLengthFrames();
	
	// BackgroundSubtraction functions
	void bgSubInit(int hist, int varThresh, bool bShadowDet);
	void bgSubDelete();

    // Event autoDetection
    std::deque<Event *> autoDetectEvents();
};
#endif
