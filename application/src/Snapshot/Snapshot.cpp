#include "Snapshot.hpp"

/*******************************************************************************
 * Constructors
 ******************************************************************************/
Snapshot::Snapshot(){
	
}

Snapshot::Snapshot(Frame *img){
	image = img;
}

Snapshot::Snapshot(Frame *img, cv::Mat inmask, std::string path){
    const void * address = static_cast<const void*>(this);
    std::stringstream ss;
    ss << address;
    filename = path + ss.str() + SNAP_EXT;

    image = img;
    cv::imwrite( filename, inmask );
}

Snapshot::Snapshot(Frame *img, cv::Rect inrect){
    image = img;
    rect = inrect;
}

/*******************************************************************************
 * Destructor
 ******************************************************************************/
Snapshot::~Snapshot(){
    remove(filename.c_str());
}

/*******************************************************************************
 * Functions
 ******************************************************************************/
cv::Mat Snapshot::getMask(){
    cv::Mat mask;
    if (!filename.empty()){
        mask = cv::imread(filename, 0);
        return mask;
    } else { //FIXME: Missing application of rectangle mask.
        cv::Mat a = cv::Mat(image->getImage().rows, image->getImage().cols, CV_8U);
        a.setTo(0);
        cv::rectangle(a, rect, 255, CV_FILLED);
        return a;
    }
}

cv::Mat Snapshot::getMasked(){
    if (!filename.empty()){
        cv::Mat mask = cv::imread(filename, 0);
        cv::Mat out;
        image->getImage().copyTo(out, mask);

        return out;
    } else {
        return (image->getImage())(rect);
    }
}

Frame* Snapshot::getFrame(){
    return image;
}
