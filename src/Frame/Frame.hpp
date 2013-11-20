#ifndef FRAME_H
#define FRAME_H
class Video;

/*
 * Class that represents Frames
 */
class Frame{
private:
	// external references
	Video vid;
	// class data
	cv::Mat image;
	
public:
	// Constructor
	Frame();
};
#endif
 
