#include "Event.hpp"

/*******************************************************************************
 * Constructors
 ******************************************************************************/
Event::Event(Video* iVid){
    position = 0;
    vid = iVid;
}

/*******************************************************************************
 * Destructor
 ******************************************************************************/
Event::~Event(){
//    Frame* ftmp;
    for(std::deque<Frame*>::iterator ftmp = frames.begin();
        ftmp != frames.end(); ftmp++){
        delete *ftmp;
    }
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

std::deque<Event*> Event::splitEvent(double threshold, double maxcount){
    double fTotal = getLengthFrames();
    std::deque<Event*> events;
    Event* newEvent = NULL;
    int j=0;
    int count=0;
    int value;

    while(j < fTotal){
        value = cv::countNonZero(snapshots.at(j)->getMask());

        // Detected change
        if ( value > threshold ){
            if (newEvent == NULL){
                newEvent = new Event(vid);
            }
            newEvent->addFrame(frames.at(j));
            newEvent->addSnapshot(snapshots.at(j));
            count = 0;
        }
        // Did not detect change
        else {
            if (newEvent != NULL){
                count ++;
                if(count > maxcount){
                    events.push_back(newEvent);
                    newEvent = NULL;
                    count = 0;
                }
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

cv::Mat* Event::getFrame(){
    Frame *tmpFrame;
    cv::Mat *frame;
    try {
        tmpFrame = frames.at(position);
    }
    catch (const std::out_of_range& oor) {
        return NULL;
    }

    frame = tmpFrame->getImage();
    if (frame->empty())
        return NULL;
    else{
        position += 1;
        return frame;
    }
    return frame;
}

bool Event::getPrevFrame(cv::Mat &frame){
    position -= 1;
    frame = getFrame();
    return false;
}

/*******************************************************************************
 * Properties
 ******************************************************************************/
double Event::getFrameInt(){
    return 1000.0/getFPS();
}

double Event::getFPS(){
    return vid->getFPS();
}

double Event::getLengthTime(){
    return getLengthFrames()*getFrameInt()/1000;
}

double Event::getLengthFrames(){
    return frames.size();
}
