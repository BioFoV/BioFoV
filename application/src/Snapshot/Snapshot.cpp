#include "Snapshot.hpp"

/*******************************************************************************
 * Constructors
 ******************************************************************************/
/**
 * @brief Simple constructor.
 */
Snapshot::Snapshot(){
	
}

/**
 * @brief Constructor with a reference to the Frame this Snapshot relates to.
 * @param img Pointer to the refered Frame.
 */
Snapshot::Snapshot(FramePtr img){
    image = img;
}

/**
 * @brief Constructor with a reference to the Frame this Snapshot relates to,
 * and the image mask.
 * @param img Pointer to the refered Frame.
 * @param inmask Mask that defines where something is.
 * @param path Path where to save the snapshot.
 */
Snapshot::Snapshot(FramePtr img, cv::Mat inmask, std::string path){
    const void * address = static_cast<const void*>(this);
    std::stringstream ss;
    ss << address;
    filename = path + ss.str() + SNAP_EXT;

    image = img;
    cv::imwrite( filename, inmask );
}

Snapshot::Snapshot(FramePtr img, cv::Rect inrect){
    image = img;
    rect = inrect;
}

/*******************************************************************************
 * Destructor
 ******************************************************************************/
/**
 * @brief Simple destructor.
 */
Snapshot::~Snapshot(){
    remove(filename.c_str());
}

/*******************************************************************************
 * Functions
 ******************************************************************************/
/**
 * @brief Snapshot::getMask
 * @return
 */
cv::Mat Snapshot::getMask(){
    cv::Mat mask;
    cv::Mat a;
    if (!filename.empty()){
        getFrame(mask);
        return mask;
    } else { //FIXME: Missing application of rectangle mask.
        image->getFrame(mask);
        a = cv::Mat(mask.rows, mask.cols, CV_8U);
        a.setTo(0);
        cv::rectangle(a, rect, 255, CV_FILLED);
        return a;
    }
}

/**
 * @brief Snapshot::getMasked
 * @return
 */
cv::Mat Snapshot::getMasked(){
    cv::Mat mask;
    if (!filename.empty()){
        getFrame(mask);
        cv::Mat out, f;
        image->getFrame(f);
        f.copyTo(out, mask);

        return out;
    } else {
        image->getFrame(mask);
        return (mask)(rect);
    }
}

bool Snapshot::check_cap(){
    return true;
}

bool Snapshot::setFramePos(double){
    return true;
}

double Snapshot::getFramePos(){
    return 0;
}

bool Snapshot::getFrame(cv::Mat &frame){
    frame = cv::imread(filename, 0);
    return true;
}

bool Snapshot::getNextFrame(cv::Mat &frame){
    getFrame(frame);
    return true;
}

bool Snapshot::getPrevFrame(cv::Mat &frame){
    getFrame(frame);
    return true;
}

bool Snapshot::stepForward(){
    return false;
}

bool Snapshot::stepBackwards(){
    return false;
}

double Snapshot::getFrameInt(){
    return 0;
}

double Snapshot::getFPS(){
    return 0;
}

double Snapshot::getLengthTime(){
    return 0;
}

double Snapshot::getLengthFrames(){
    return 0;
}

FramePtr Snapshot::getCurrentFrameRef(){
    return image;
}

unsigned int Snapshot::getCurrentFrameNumber(){
    return image->getCurrentFrameNumber();
}

void Snapshot::save(std::string fname){
    cv::imwrite( fname + ".png", getMasked());
}
