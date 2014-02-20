#include "Frame.hpp"

/*******************************************************************************
 * Constructors
 ******************************************************************************/
Frame::Frame(){
	vid = NULL;
}

Frame::Frame(Video *source_vid){
	vid = source_vid;
}

Frame::Frame(Video *source_vid, cv::Mat shot, unsigned int index){
    // use image address as filename to ensure there are no clashes
    const void * address = static_cast<const void*>(this);
    std::stringstream ss;
    ss << address;
    filename = ss.str() + IMG_EXT;

    vid = source_vid;
    frameNumber = index;

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
