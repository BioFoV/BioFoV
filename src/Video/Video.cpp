#include "Video.hpp"

/*******************************************************************************
 * Constructors
 ******************************************************************************/
Video::Video(){
	return;
}

Video::Video(cv::VideoCapture* capture){
	cap = capture;
}
