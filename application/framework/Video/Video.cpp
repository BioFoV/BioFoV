#include "Video.hpp"

/*******************************************************************************
 * Constructors
 ******************************************************************************/
Video::Video(){
	bg = NULL;
	return;
}

Video::Video(cv::VideoCapture capture){
	bg = NULL;
	cap = capture;
}

Video::Video(std::string name){
	bg = NULL;
	filename = name;
	cap = cv::VideoCapture(name);
}

/*******************************************************************************
 * Destructors
 ******************************************************************************/
Video::~Video(){
	if (bg != NULL){
		delete bg;
	}
}

/*
 * Set and Get
 **/
void Video::setFileName(std::string name){
    filename = name;
}

std::string Video::getFileName(){
    return filename;
}

void Video::setCapture(cv::VideoCapture capture){
    cap = capture;
}

cv::VideoCapture Video::getCapture(){
    return cap;
}

/*******************************************************************************
 * Capture functions
 ******************************************************************************/
bool Video::check_cap(){
	if(cap.isOpened()){
		return true;
	}
	std::cerr << "Couldn't open " << filename << std::endl;
	return false;
}

bool Video::get_frame(cv::Mat &frame){
	if(!check_cap()){
		return false;
	}
	if(cap.read(frame)){
		return true;
	}
	else{
		std::cerr << "Couldn't read frame" << std::endl;
		return false;
	}
}

/*******************************************************************************
 * Background Subtraction functions
 ******************************************************************************/
void Video::bgSubInit(int hist, int varThresh, bool bShadowDet){
	bg = new BackgroundSubtractor(hist,varThresh,bShadowDet);
}

void Video::bgSubDelete(){
	delete bg;
}
