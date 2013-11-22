#include "Video.hpp"

/*******************************************************************************
 * Constructors
 ******************************************************************************/
Video::Video(){
	return;
}

Video::Video(cv::VideoCapture capture){
	cap = capture;
	check_cap();
}

Video::Video(std::string filename){
	cap = cv::VideoCapture(filename);
	check_cap();
}

/********************************************************************************
 * Capture functions
 *******************************************************************************/
bool Video::check_cap(){
	if(cap.isOpened()){
		return true;
	}
	std::cerr << "Couldn't open " << filename << std::endl;
	return false;
}

bool Video::get_frame(cv::Mat &frame){
	if(cap.read(frame)){
		return true;
	}
	else{
		std::cerr << "Couldn't read frame" << std::endl;
		return false;
	}
}
