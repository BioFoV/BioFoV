#include "Event.hpp"

/*******************************************************************************
 * Constructors
 ******************************************************************************/
Event::Event(){
    position = 0;
    fps = 0;
}

/*******************************************************************************
 * Functions
 ******************************************************************************/
void Event::addFrame(Frame* inframe){
    frames.push_back(inframe);
}

void Event::setFPS(double infps){
    fps = infps;
}

/*******************************************************************************
 * Capture functions
 ******************************************************************************/
bool Event::check_cap(){
    return !frames.empty();
}

//TODO: error conditions
bool Event::setFramePos(double frameNum){
    position = frameNum;
    return true;
}

double Event::getFramePos(){
    return position;
}

bool Event::getFrame(cv::Mat &frame){
    Frame *tmpFrame;
    try {
        tmpFrame = frames.at(position);
    }
    catch (const std::out_of_range& oor) {
        return false;
    }

    frame = tmpFrame->getImage();
    if (frame.empty())
        return false;
    else{
        position += 1;
        return true;
    }
    return false;
}

bool Event::getPrevFrame(cv::Mat &frame){
    position -= 1;
    getFrame(frame);
    return false;
}

/*******************************************************************************
 * Properties
 ******************************************************************************/
double Event::getFrameInt(){
    return 1000.0/fps;
}

double Event::getFPS(){
    return fps;
}

double Event::getLengthTime(){
    return getLengthFrames()*getFrameInt()/1000;
}

double Event::getLengthFrames(){
    return frames.size();
}
