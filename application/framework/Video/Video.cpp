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
    fps = cap.get(CV_CAP_PROP_FPS);
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

double Video::getFramePos(){
    return cap.get(CV_CAP_PROP_POS_FRAMES);
}

bool Video::setFramePos(double frameNum){
    return cap.set(CV_CAP_PROP_POS_FRAMES, frameNum);
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

bool Video::getPrevFrame(cv::Mat &frame){
    double tempPos = getFramePos();
    if (tempPos > 1){
        setFramePos(tempPos-2);
        return get_frame(frame);
    } else {
        return false;
    }

}

/*******************************************************************************
 * Properties
 ******************************************************************************/
/* Returns the interval between frames (in miliseconds)
 */
double Video::getFrameInt(){
    return 1000.0/fps;
}

/* Returns the number of frames per second
 */
double Video::getFPS(){
    return fps;
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
