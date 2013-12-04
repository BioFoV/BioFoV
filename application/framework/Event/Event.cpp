#include "Event.hpp"

/*******************************************************************************
 * Constructors
 ******************************************************************************/
Event::Event(){
	
}

/*******************************************************************************
 * Functions
 ******************************************************************************/
void Event::addFrame(Frame* inframe){
    frames.push_back(inframe);
}

/*******************************************************************************
 * Capture functions
 ******************************************************************************/
bool Event::check_cap(){
    return false;
}

bool Event::setFramePos(double frameNum){
    return false;
}

double Event::getFramePos(){
    return 0;
}

bool Event::get_frame(cv::Mat &frame){
    return false;
}

bool Event::getPrevFrame(cv::Mat &frame){
    return false;
}

/*******************************************************************************
 * Properties
 ******************************************************************************/
double Event::getFrameInt(){
    return 0;
}

double Event::getFPS(){
    return 0;
}

double Event::getLengthTime(){
    return 0;
}

double Event::getLengthFrames(){
    return 0;
}
