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

#ifndef VIDEO_H
#define VIDEO_H
class Frame;

/*
 * Class that holds the VideoCapture handler and that provides frames
 */
class Video {
private:
	cv::VideoCapture cap;
	std::list<Frame> frames;
	std::string filename;
	
public:
	// Atributes
	BackgroundSubtractor * bg;
	
	// Constructors
	Video();
	Video(cv::VideoCapture capture);
	Video(std::string filename);
	
	// Destructors
	~Video();
	
	// Capture functions
	bool check_cap();
	bool get_frame(cv::Mat &frame);
	
	// BackgroundSubtraction functions
	void bgSubInit(int hist, int varThresh, bool bShadowDet);
	void bgSubDelete();
};
#endif
