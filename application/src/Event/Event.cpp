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
//    vid->removeEvent(this);
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
void Event::addFrame(FramePtr inFrame){
    frames.push_back(inFrame);
}

void Event::addSnapshot(SnapshotPtr inSnap){
    snapshots.push_back(inSnap);
}

void Event::remLastFrame(){
    frames.pop_back();
}

void Event::remLastSnapshot(){
    snapshots.pop_back();
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
            tmpFrame = frames.at(position).data();
        }
        catch (const std::out_of_range& oor) {
            return false;
        }
        frame = tmpFrame->getImage();
    } else if (playMode == PLAY_MASK){
        SnapshotPtr tmpSnap;
        try {
            tmpSnap = snapshots.at(position);
        }
        catch (const std::out_of_range& oor) {
            return false;
        }
        frame = tmpSnap->getMask();
    } else if (playMode == PLAY_MASKED_FRAMES){
        SnapshotPtr tmpSnap;
        try {
            tmpSnap = snapshots.at(position);
        }
        catch (const std::out_of_range& oor) {
            return false;
        }
        frame = tmpSnap->getMasked();
    }
    if (frame.empty())
        return false;
    else{
        return true;
    }
}

bool Event::getPrevFrame(cv::Mat &frame){
    if (position > 0) {
        position --;
        return getFrame(frame);
    } else {
        return false;
    }
}

bool Event::getNextFrame(cv::Mat &frame){
    if (position < getLengthFrames()-1){
        position ++;
        return getFrame(frame);
    } else {
        return false;
    }
}

bool Event::stepForward(){
    position ++;
    if (position > getLengthFrames()-1)
        return false;
    return true;
}

bool Event::stepBackwards(){
    position --;
    if (position < 0)
        return false;
    return true;
}

FramePtr Event::getCurrentFrameRef(){
    if (position > getLengthFrames()-1)
        return QSharedPointer<Frame>(NULL);
    return frames.at(position);
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

uint Event::getCurrentFrameNumber(){
    return frames.at(position)->getCurrentFrameNumber();
}

/*******************************************************************************
 * Playback modifier
 ******************************************************************************/
void Event::setPlaybackMode(int mode){
    playMode = mode;
}

bool Event::saveAsVideo(std::string filename, std::string encoder){
    int fourcc = 0;

    if(encoder == "XVID")
        fourcc = CV_FOURCC('X','V','I','D');
    else if(encoder == "HFYU")
        fourcc = CV_FOURCC('H','F','Y','U');

    double fps = vid->getFPS();
    cv::Size frameSize = vid->getSize();
    bool isColor = !(playMode == PLAY_MASK);

    cv::VideoWriter vidW(filename, fourcc, fps, frameSize, isColor);

    if (!vidW.isOpened()){
        return false;
    }

    int tmpPos = getFramePos();
    setFramePos(0);

    cv::Mat buffer;
    while (getNextFrame(buffer)){
        vidW.write(buffer);
    }

    vidW.release();

    setFramePos(tmpPos);
    return true;
}

void Event::save(std::string fname){
    saveAsVideo(fname+".avi", "HFYU");
}

Video* Event::getVideo(){
    return vid;
}
