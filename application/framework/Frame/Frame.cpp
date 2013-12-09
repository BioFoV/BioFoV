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
    // use image address as filename to ensure there are no clashes
    const void * address = static_cast<const void*>(this);
    std::stringstream ss;
    ss << address;
    filename = ss.str() + IMG_EXT;

    vid = source_vid;
    cv::imwrite( filename, shot );
    snap = NULL;
}

/*******************************************************************************
 * Destructor
 ******************************************************************************/
Frame::~Frame(){
    remove(filename.c_str());
    delete snap;
}

/*******************************************************************************
 * Functions
 ******************************************************************************/
void Frame::setImage(cv::Mat shot){
    imwrite( filename, shot);
}

void Frame::setSnapshot(Snapshot *insnap){
    snap = insnap;
}

cv::Mat* Frame::getImage(){
    cv::Mat image = cv::imread(filename);
    return &image;
}
