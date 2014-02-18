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
    // FIXME: deletion is not done due to merging.
//    for(std::deque<Frame*>::iterator ftmp = frames.begin();
//        ftmp != frames.end(); ftmp++){
//        delete *ftmp;
//    }
}

/*******************************************************************************
 * Modifiers
 ******************************************************************************/
Event& Event::operator +=(const Event& ev1){
    unsigned int i;
    for (i=0; i<ev1.frames.size(); i++){
        frames.push_back(ev1.frames.at(i));
    }
    for (i=0; i<ev1.individuals.size(); i++){
        individuals.push_back(ev1.individuals.at(i));
    }
    for (i=0; i<ev1.snapshots.size(); i++){
        snapshots.push_back(ev1.snapshots.at(i));
    }
    position = 0;

    return *this;
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

void Event::remLastFrame(){
    frames.pop_back();
}

void Event::remLastSnapshot(){
    snapshots.pop_back();
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

bool Event::getFrameObject(Frame **outFrame){
    try {
        *outFrame = frames.at(position);
    }
    catch (const std::out_of_range& oor) {
        return false;
    }
    position += 1;
    return true;
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
    } else if (playMode == PLAY_MASK){
        Snapshot* tmpSnap;
        try {
            tmpSnap = snapshots.at(position);
        }
        catch (const std::out_of_range& oor) {
            return false;
        }

        frame = tmpSnap->getMask();
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
    }
    if (frame.empty())
        return false;
    else{
        position += 1;
        return true;
    }
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
