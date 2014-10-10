#include "Frame.hpp"

/*******************************************************************************
 * Constructors
 ******************************************************************************/
/**
 * @brief Simple constructor.
 */
Frame::Frame(){
	vid = NULL;
//    thisPtr = FramePtr(this);
}

/**
 * @brief Constructor with reference to the Video source from which the Frame was taken.
 * @param source_vid Video from which the Frame was extracted.
 * @param shot
 * @param path Folder for holding the png files.
 */
Frame::Frame(Video *source_vid, cv::Mat shot, std::string path){
    // use image address as filename to ensure there are no clashes
    const void * address = static_cast<const void*>(this);
    std::stringstream ss;
    ss << address;
    filename = path + ss.str() + IMG_EXT;

    vid = source_vid;
    frameNumber = vid->getFramePos();

    cv::imwrite( filename, shot );

    activeDrawable = NULL;

//    thisPtr = FramePtr(this);
}

/*******************************************************************************
 * Destructor
 ******************************************************************************/
/**
 * @brief Simple destructor.
 */
Frame::~Frame(){
    remove(filename.c_str());
}

/*******************************************************************************
 * Functions
 ******************************************************************************/
/**
 * @brief Sets the image of the Frame.
 * Use this if you didn't specify it in the constructor.
 * @param shot Image of the Frame.
 */
void Frame::setImage(cv::Mat shot){
    imwrite( filename, shot);
}

/**
 * @brief Frame::getNumber
 * @return
 */
unsigned int Frame::getNumber(){
    return frameNumber;
}


bool Frame::check_cap(){
    return true;
}

bool Frame::setFramePos(double /*frameNum - unused*/){
    return true;
}

double Frame::getFramePos(){
    return 0;
}

bool Frame::getFrame(cv::Mat &frame) {
    frame = cv::imread(filename);;
    applyDrawables(frame);
    return true;
}

bool Frame::getPrevFrame(cv::Mat &frame){
    getFrame(frame);
    return false;
}

bool Frame::getNextFrame(cv::Mat &frame){
    getFrame(frame);
    return false;
}

FramePtr Frame::getCurrentFrameRef(){
    //FIXME this is NOT how it should be done!
    qDebug("If you read this then something is wrong");
    FramePtr thisPtr = FramePtr(this);
    return thisPtr;
}

bool Frame::stepForward(){
    return false;
}

bool Frame::stepBackwards(){
    return false;
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

uint Frame::getCurrentFrameNumber(){
    return frameNumber;
}

void Frame::mousePressEvent(cv::Point point){
    if (activeDrawable != NULL)
        activeDrawable->press(point);
}

void Frame::mouseReleaseEvent(cv::Point point){
    if (activeDrawable != NULL){
        activeDrawable->release(point);
        if (activeDrawable->isDone()){
            activeDrawable = NULL;
            updateValues();
        }
    }
}

void Frame::mouseMoveEvent(cv::Point point){
    if (activeDrawable != NULL)
        activeDrawable->move(point);
}

void Frame::save(std::string fname){
    cv::Mat buff;
    getFrame(buff);
    cv::imwrite( fname + ".png", buff);
}

/**
 * @brief Frame::getValues
 * @return
 */
TStrDoubleMap Frame::getValues(){
    TStrDoubleMap ret;
    TStrDoubleMap temp;
    for (std::deque<Drawable*>::iterator iter = drawers.begin();
         iter != drawers.end();
         iter ++) {
        if((*iter)->isDone()){
            temp = (*iter)->getValues();
            for (TStrDoubleMap::iterator iter2 = temp.begin();
                 iter2 != temp.end();
                 iter2 ++){
                ret.push_back(*iter2);
            }
        }
    }
    return ret;
}
