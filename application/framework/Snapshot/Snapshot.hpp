#ifndef SNAP_H
#define SNAP_H

// OpenCV
#ifndef OPENCV_INC
#define OPENCV_INC
#include <opencv2/opencv.hpp>
#endif

#ifndef INC_FRAME
#define INC_FRAME
#include "../Frame/Frame.hpp"
#endif

/*
 * Class that associated with a Frame represents an area of interest in
 * a frame.
 */
class Frame;

class Snapshot{
private:
	// external references
	Frame *image;
	// class data
	cv::Mat mask;
	
public:
	// Constructors
	Snapshot();
	Snapshot(Frame *img);
    Snapshot(Frame *img, cv::Mat inmask);
};
#endif
