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
void Event::addFrame(Frame* inFrame){
    frames.push_back(inFrame);
}

void Event::addSnapshot(Snapshot* inSnap){
    snapshots.push_back(inSnap);
}

void Event::setFPS(double infps){
    fps = infps;
}

std::list<Event*> Event::splitEvent(double threshold, double maxcount){
    double fTotal = getLengthFrames();
    std::list<Event*> events;
    Event* newEvent;
    int i=0;
    int j=1;
    int count=0;
    int value;

    while(j < fTotal){
        value = cv::countNonZero(snapshots.at(j)->getMask());
        if ( value > threshold ){
            count ++;
            if(count > maxcount){
                newEvent = new Event();
                newEvent->setFPS(getFPS());
                for (int k=i; k<j; k++){
                    newEvent->addFrame(frames.at(k));
                    newEvent->addSnapshot(snapshots.at(k));
                }
                events.push_back(newEvent);
                // next event
                count = 0;
                i = j;
            }
        }
        j++;
    }
    return events;
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
