#include "Event.hpp"

/*******************************************************************************
 * Constructors
 ******************************************************************************/
Event::Event(Video* iVid){
    position = 0;
    vid = iVid;
    playMode = PLAY_FRAMES;
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

/* Splits an event into several based on background subtraction
 * threshold -> pixelcount for background subtraction difference
 * maxcount -> maximum distance in frames between events for them to be a single
 *one
 * mincount -> minimum size of an event in frames
 */
std::deque<Event*> Event::splitEvent(double threshold, double maxcount,
                                     double mincount){
    double fTotal = getLengthFrames();
    std::deque<Event*> events;
    Event* newEvent = NULL;
    int j=0;
    int emptycount=0;
    int framecount=0;
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
            framecount ++;
            emptycount = 0;
        }
        // Did not detect change
        else {
            if (newEvent != NULL){
                emptycount ++;
                if(emptycount > maxcount){
                    if (framecount > mincount){
                        events.push_back(newEvent);
                    } else {
                        delete newEvent;
                    }
                    newEvent = NULL;
                    emptycount = 0;
                    framecount = 0;
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

bool Event::getFrame(cv::Mat &frame){
    if (playMode == PLAY_FRAMES){
        Frame* tmpFrame;
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
    } else if (playMode == PLAY_MASK){
        Snapshot* tmpSnap;
        try {
            tmpSnap = snapshots.at(position);
        }
        catch (const std::out_of_range& oor) {
            return false;
        }

        frame = tmpSnap->getMask();
        if (frame.empty())
            return false;
        else {
            position ++;
            return true;
        }
    } else if (playMode == PLAY_MASKED_FRAMES){
        Snapshot* tmpSnap;
        Frame* tmpFrame;
        try {
            tmpSnap = snapshots.at(position);
            tmpFrame = frames.at(position);
        }
        catch (const std::out_of_range& oor) {
            return false;
        }

        frame = tmpSnap->getMask();
        tmpFrame->getImage().copyTo(frame,tmpSnap->getMask());
        if (frame.empty())
            return false;
        else {
            position ++;
            return true;
        }
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

/*******************************************************************************
 * Playback modifier
 ******************************************************************************/
void Event::setPlaybackMode(int mode){
    playMode = mode;
}
