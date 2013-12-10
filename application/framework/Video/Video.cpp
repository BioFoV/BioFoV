#include "Video.hpp"

/*******************************************************************************
 * Constructors
 ******************************************************************************/
Video::Video(){
	bg = NULL;
	return;
}

Video::Video(cv::VideoCapture capture){
	bg = NULL;
    filename = "";
	cap = capture;
    dumpCap();
}

Video::Video(std::string name){
	bg = NULL;
	filename = name;
	cap = cv::VideoCapture(name);
    dumpCap();
}

/*******************************************************************************
 * Destructors
 ******************************************************************************/
Video::~Video(){
    if (bg != NULL){
        delete bg;
    }
    frames.clear();
    events.clear();
}

/*******************************************************************************
 * Set and Get
 ******************************************************************************/
void Video::setFileName(std::string name){
    filename = name;
}

std::string Video::getFileName(){
    return filename;
}

void Video::setCapture(cv::VideoCapture capture){
    cap = capture;
}

cv::VideoCapture Video::getCapture(){
    return cap;
}

/*******************************************************************************
 * Capture functions
 ******************************************************************************/
/* From a cv::VideoCapture stored in cap, dumps all the necessary info to the
 *structure.
 */
void Video::dumpCap(){
    fps = cap.get(CV_CAP_PROP_FPS);
    resolution[0] = cap.get(CV_CAP_PROP_FRAME_WIDTH);
    resolution[1] = cap.get(CV_CAP_PROP_FRAME_HEIGHT);
    lengthFrames = cap.get(CV_CAP_PROP_FRAME_COUNT);
    readAll();
    cap.release();
}

/* Reads all the frames from the video and dumps them to Frame objects, queued
 *in the deque "frames". This ignores the current position.
 */
double Video::readAll(){
    cv::Mat *image = new cv::Mat;
    Frame* frame;
    double framesRead = 0;
    QList<QFuture<void> > future;

    while (cap.read(*image)){
        framesRead ++;
        frame = new Frame(this);
        frames.push_back(frame);
        future.append(QtConcurrent::run(frame, &Frame::setImage, image->clone()));
        image = new cv::Mat;
    }
    foreach (QFuture<void> fut, future){
        fut.waitForFinished();
    }

    // delete the last created but unread image
    delete image;

    // return the number of frames read
    return framesRead;
}

/* Checks if there are any frames that can be read.
 */
bool Video::check_cap(){
    if(!frames.empty()){
        return true;
    }
    std::cerr << "Couldn't open " << filename << std::endl;
    return false;
}

/* Gets the current position inside the video
 */
double Video::getFramePos(){
    return position;
}

/* Sets the current position inside the video
 */
bool Video::setFramePos(double frameNum){
    if (frameNum > getLengthFrames()){
        return false;
    } else{
        position = frameNum;
        return true;
    }
}

/* Gets the frame at the current position and takes one step forward
 */
cv::Mat* Video::getFrame(){
    cv::Mat* image;

    if(!check_cap()){
        return NULL;
    }
    try{
        image = frames.at(position)->getImage();
        position++;
        return image;
    } catch (std::out_of_range){
        return NULL;
    }
}

/* Rewinds one position and returns the frame
 */
cv::Mat* Video::getPrevFrame(){
    double tempPos = getFramePos();
    if (tempPos > 1){
        setFramePos(tempPos-2);
        return getFrame();
    } else {
        return NULL;
    }
}

/*******************************************************************************
 * Properties
 ******************************************************************************/
/* Returns the interval between frames (in miliseconds)
 */
double Video::getFrameInt(){
    return 1000.0/fps;
}

/* Returns the number of frames per second
 */
double Video::getFPS(){
    return fps;
}

/* Returns the length of the video in seconds
 */
double Video::getLengthTime(){
    return getLengthFrames()/getFPS();
}

/* Returns the length of the video in frames
 */
double Video::getLengthFrames(){
    return lengthFrames;
}

/*******************************************************************************
 * Background Subtraction functions
 ******************************************************************************/
void Video::bgSubInit(int hist, int varThresh, bool bShadowDet){
	bg = new BackgroundSubtractor(hist,varThresh,bShadowDet);
}

void Video::bgSubDelete(){
	delete bg;
}

/*******************************************************************************
 * Event autoDetection
 ******************************************************************************/
std::deque<Event*> Video::autoDetectEvents(){
    Frame* frame;
    Snapshot *snap;
    Event *event = new Event(this); // new empty event

    // Initialization of background subtraction
    bgSubInit(1000, 50, false);

    setFramePos(0);

    unsigned int iter;

    for (iter = 0; iter < frames.size(); iter ++){
        frame = frames.at(iter);
        bg->NewFrame(frame->getImage());

        // create new snapshot
        snap = new Snapshot(frame, bg->Foreground());
        frame->setSnapshot(snap);
        event->addFrame(frame);
        event->addSnapshot(snap);
    }

    std::deque<Event*> splited = event->splitEvent(200,3, 5);
    for (iter = 0; iter < splited.size(); iter++){
        events.push_back(splited.at(iter));
    }

    return events;
}
