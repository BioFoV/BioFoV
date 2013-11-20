// OpenCV
#ifndef OPENCV_INC
#define OPENCV_INC
#include <opencv2/opencv.hpp>
#endif

#ifndef INC_FRAME
#define INC_FRAME
#include "../Frame/Frame.cpp"
#endif

/*
 * Class that associated with a Frame represents an area of interest in
 * a frame.
 */
#ifndef SNAP_H
#define SNAP_H
class Frame;

class Snapshot{
private:
	// external references
	Frame *image;
	// class data
	cv::Mat mask;
	
public:
	// Constructor
	Snapshot();
};
#endif
 
