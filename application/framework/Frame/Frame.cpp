#include "Frame.hpp"

/*******************************************************************************
 * Constructors
 ******************************************************************************/
Frame::Frame(){
	vid = NULL;
    snap = NULL;
}

Frame::Frame(Video *source_vid){
	vid = source_vid;
    snap = NULL;
}

Frame::Frame(Video *source_vid, cv::Mat shot){
    vid = source_vid;
    image = shot;
    snap = NULL;
}

/*******************************************************************************
 * Functions
 ******************************************************************************/
void Frame::setImage(cv::Mat shot){
    image = shot;
}

void Frame::setSnapshot(Snapshot *insnap){
    snap = insnap;
}

cv::Mat Frame::getImage(){
    return image;
}
