#include "Frame.hpp"

/*******************************************************************************
 * Constructors
 ******************************************************************************/
Frame::Frame(){
	vid = NULL;
}

Frame::Frame(Video *source_vid, std::string path){
    // use image address as filename to ensure there are no clashes
    const void * address = static_cast<const void*>(this);
    std::stringstream ss;
    ss << address;
    filename = path + ss.str() + IMG_EXT;

    vid = source_vid;
    frameNumber = vid->getFramePos();

    cv::Mat shot;
    vid->getFrame(shot);

    cv::imwrite( filename, shot );
}

/*******************************************************************************
 * Destructor
 ******************************************************************************/
Frame::~Frame(){
    remove(filename.c_str());
    for (unsigned int i=0; i<snap.size(); i++){
        snap.pop_back();
    }
}

/*******************************************************************************
 * Functions
 ******************************************************************************/
void Frame::setImage(cv::Mat shot){
    imwrite( filename, shot);
}

void Frame::setSnapshot(Snapshot *insnap){
    snap.push_back(insnap);
}

cv::Mat Frame::getImage(){
    cv::Mat image = cv::imread(filename);
    return image;
}

unsigned int Frame::getNumber(){
    return frameNumber;
}


bool Frame::check_cap(){
    return true;
}

bool Frame::setFramePos(double frameNum){
    return true;
}

double Frame::getFramePos(){
    return 0;
}

bool Frame::getFrame(cv::Mat &frame) {
    frame = getImage();
    return true;
}

bool Frame::getPrevFrame(cv::Mat &frame){
    frame = getImage();
    return true;
}

bool Frame::getNextFrame(cv::Mat &frame){
    frame = getImage();
    return true;
}

void* Frame::getCurrentFrameRef(){
    return this;
}

double Frame::getFrameInt(){
    return 0;
}

double Frame::getFPS(){
    return 0;
}

double Frame::getLengthTime(){
    return 0;
}

double Frame::getLengthFrames(){
    return 1;
}

