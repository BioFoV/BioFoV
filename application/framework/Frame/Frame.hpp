#ifndef FRAME_H
#define FRAME_H

// OpenCV
#ifndef OPENCV_INC
#define OPENCV_INC
#include <opencv2/opencv.hpp>
#endif

#ifndef INC_VIDEO
#define INC_VIDEO
#include "../Video/Video.hpp"
#endif

class Video;

/*
 * Class that represents Frames
 */
class Frame{
private:
	// external references
	Video *vid;
	// class data
	cv::Mat image;
	
public:
	// Constructors
	Frame();
	Frame(Video *source_vid);
};
#endif
