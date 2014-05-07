#include "Video.hpp"

/*******************************************************************************
 * Constructors
 ******************************************************************************/
Video::Video(){
	bg = NULL;
    activeDrawable = NULL;
}

Video::Video(cv::VideoCapture capture){
	bg = NULL;
	cap = capture;
    activeDrawable = NULL;
}

Video::Video(std::string name){
	bg = NULL;
	filename = name;
	cap = cv::VideoCapture(name);
    fps = cap.get(CV_CAP_PROP_FPS);
    resolution.width = cap.get(CV_CAP_PROP_FRAME_WIDTH);
    resolution.height = cap.get(CV_CAP_PROP_FRAME_HEIGHT);
    cam = NULL;
    activeDrawable = NULL;
}

/*******************************************************************************
 * Destructors
 ******************************************************************************/
Video::~Video(){
    if (bg != NULL){
        delete bg;
    }
}

/*
 * Set and Get
 **/
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
bool Video::check_cap(){
	if(cap.isOpened()){
		return true;
    }
	return false;
}

double Video::getFramePos(){
    return cap.get(CV_CAP_PROP_POS_FRAMES);
}

bool Video::setFramePos(double frameNum){
    return cap.set(CV_CAP_PROP_POS_FRAMES, frameNum);
}

bool Video::getFrame(cv::Mat &frame){
	if(!check_cap()){
		return false;
    }
    setFramePos(getFramePos()-1);
	if(cap.read(frame)){
        if(isCalibrated()){
            frame = cam->undistort(frame);
        }
        applyDrawables(frame);
        return true;
	}
    else{
        return false;
	}
}

bool Video::getPrevFrame(cv::Mat &frame){
    double tempPos = getFramePos();
    if (tempPos > 0){
        setFramePos(tempPos-1);
        return getFrame(frame);
    } else {
        return false;
    }
}

bool Video::getNextFrame(cv::Mat &frame){
    if(!check_cap()){
        return false;
    }
    if(cap.read(frame)){
        if(isCalibrated()){
            frame = cam->undistort(frame);
        }
        applyDrawables(frame);
        return true;
    }
    else{
        return false;
    }
}

FramePtr Video::getCurrentFrameRef(){
    cv::Mat shot;
    if (getFrame(shot))
        return FramePtr(new Frame(this, shot, getCacheDir()));
    return FramePtr(NULL);
}

std::string Video::getCacheDir(){
    return getSettings()->getCacheDir().append("/").toStdString();
}

bool Video::stepForward(){
    return setFramePos(getFramePos()+1);
}

bool Video::stepBackwards(){
    return setFramePos(getFramePos()-1);
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

double Video::getLengthTime(){
    return getLengthFrames()/getFPS();
}

double Video::getLengthFrames(){
    return cap.get(CV_CAP_PROP_FRAME_COUNT);
}

cv::Size Video::getSize(){
    return resolution;
}

bool Video::isCalibrated(){
    if (cam != NULL){
        return cam->isCalibrated();
    }
    return false;
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

EventPtr Video::convertToEvent(std::string path){
    cv::Mat shot;
    FramePtr frame;
    EventPtr event;

    unsigned int j=0;
    int framecount=0;

    double tmpPos = getFramePos();
    setFramePos(0);

    emit startProgress(0, (uint) getLengthFrames());

    while(getNextFrame(shot)){
        emit progressChanged(j);

        if (event.isNull()){
            event = EventPtr(new Event(this));
        }
        // create new frame
        frame = FramePtr(new Frame(this, shot, path));
        // add frame to event
        event->addFrame(frame);
        framecount ++;
        j++;
    }

    setFramePos(tmpPos);

    return event;
}

std::deque<EventPtr> Video::autoDetectEvents(double threshold,
                                           double maxcount,
                                           double mincount,
                                           int history,
                                           int varThreshold,
                                           bool bShadowDetection,
                                           std::string path){
    cv::Mat shot;
    FramePtr frame;
    SnapshotPtr snap;
    EventPtr event;
    std::deque<EventPtr> events;

    unsigned int j=0;
    int emptycount=0;
    int framecount=0;
    int value;
    int absoluteThreshold = threshold/100*resolution.width*resolution.height;
    int i;


    // Initialization of background subtraction
    bgSubInit(history, varThreshold, bShadowDetection);

    setFramePos(0);

    emit startProgress(0, (uint) getLengthFrames());

    while(getNextFrame(shot)){
        QCoreApplication::processEvents();
        if (toCancel){
            events.clear();
            canceled();
            std::cout << toCancel << std::endl;
            return events;
        }
        bg->NewFrame(shot);
        bg->Denoise();
        emit progressChanged(j);
        value = cv::countNonZero(bg->Foreground());

        // Detected change
        if ( value > absoluteThreshold ){
            if (event.isNull()){
                event = EventPtr(new Event(this));
            }
            // create new frame
            frame = FramePtr(new Frame(this, shot, path));
            snap = SnapshotPtr(new Snapshot(frame, bg->Foreground(), path));
            // add frame to event
            event->addFrame(frame);
            event->addSnapshot(snap);
            framecount ++;
            emptycount = 0;
        }
        // Did not detect change
        else if (!event.isNull()){
            emptycount ++;
            // create new frame
            frame = FramePtr(new Frame(this, shot, path));
            snap = SnapshotPtr(new Snapshot(frame, bg->Foreground(), path));
            // add frame to event
            event->addFrame(frame);
            event->addSnapshot(snap);
            framecount ++;
            if(emptycount > maxcount){
                if (framecount - emptycount > mincount){
                    // remove extra frames with no movement
                    for (i = 0; i < maxcount; i++){
                        event->remLastFrame();
                        event->remLastSnapshot();
                    }
                    events.push_back(event);
                }
                event.clear();
                emptycount = 0;
                framecount = 0;
            }
        }
        j++;
    }
    // Check if Video ended in the middle of an Event.
    if (!event.isNull()){
        if (framecount > mincount){
            events.push_back(event);
        } else {
            event.clear();
        }
    }
    return events;
}

void Video::calibrate(int nBoards, int frameStep, int boardW,
                      int boardH, int iterations) {

    // Rewind to the beginning
    setFramePos(0);

//    if (cam != NULL){
//        delete cam;
//    }
    cam = new Camera(this, boardW, boardH);
    cam->calibrate(nBoards, frameStep, iterations);

    // Rewind again
    setFramePos(0);
}

void Video::deleteCalibration() {
    delete cam;
    cam = NULL;
}

void Video::flip_horizontally(){
    if (cam == NULL){
        cam = new Camera(this);
    }
    cam->flip_horizontal();
}

void Video::flip_vertically(){
    if (cam == NULL){
        cam = new Camera(this);
    }
    cam->flip_vertical();
}

Camera* Video::getCamera(){
    return cam;
}

void Video::importCamera(){
    cam = new Camera(this);

    cam->read_file();
}

void Video::mousePressEvent(cv::Point point){
    if (activeDrawable != NULL)
        activeDrawable->press(point);
}

void Video::mouseReleaseEvent(cv::Point point){
    if (activeDrawable != NULL){
        activeDrawable->release(point);
        if (activeDrawable->isDone()){
            activeDrawable = NULL;
            updateValues();
        }
    }
}

void Video::mouseMoveEvent(cv::Point point){
    if (activeDrawable != NULL)
        activeDrawable->move(point);
}

uint Video::getCurrentFrameNumber(){
    return getFramePos();
}

void Video::save(std::string /*fname*/){
    //FIXME - not implemented
}

void Video::cancel() {
    toCancel = true;
}

void Video::canceled() {
    toCancel = false;
}
