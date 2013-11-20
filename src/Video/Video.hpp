// OpenCV
#ifndef OPENCV_INC
#define OPENCV_INC
#include <opencv2/opencv.hpp>
#endif

#ifndef INC_FRAME
#define INC_FRAME
#include "../Frame/Frame.hpp"
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
	
public:
	// Constructor
	Video();
};
#endif

