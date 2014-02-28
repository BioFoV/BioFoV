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
	cap = capture;
}

Video::Video(std::string name){
	bg = NULL;
	filename = name;
	cap = cv::VideoCapture(name);
    fps = cap.get(CV_CAP_PROP_FPS);
    resolution.width = cap.get(CV_CAP_PROP_FRAME_WIDTH);
    resolution.height = cap.get(CV_CAP_PROP_FRAME_HEIGHT);
    cam = NULL;
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
	if(cap.read(frame)){
        setFramePos(getFramePos()-1);
        if(isCalibrated()){
            frame = cam->undistort(frame);
        }
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
        return true;
    }
    else{
        return false;
    }
}

void *Video::getCurrentFrameRef(){
    cv::Mat shot;
    getFrame(shot);
    return new Frame(this, shot, getCacheDir());
}

std::string Video::getCacheDir(){
    return getSettings()->getCacheDir().append("/").toStdString();
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
std::deque<Event*> Video::autoDetectEvents(double threshold,
                                           double maxcount,
                                           double mincount,
                                           int history,
                                           int varThreshold,
                                           bool bShadowDetection,
                                           std::string path){
    cv::Mat shot;
    Frame *frame;
    Snapshot *snap;
    Event *event = NULL;

    unsigned int j=0;
    int emptycount=0;
    int framecount=0;
    int value;

    // Initialization of background subtraction
    bgSubInit(history, varThreshold, bShadowDetection);

    setFramePos(0);

    emit startProgress(0, (uint) getLengthFrames());

    while(getNextFrame(shot)){
        bg->NewFrame(shot);
        emit progressChanged(j);
        value = cv::countNonZero(bg->Foreground());

        // Detected change
        if ( value > threshold/100*resolution.width*resolution.height ){
            if (event == NULL){
                event = new Event(this);
            }
            // create new frame
            frame = new Frame(this, shot, path);
            snap = new Snapshot(frame, bg->Foreground());
            frame->setSnapshot(snap);
            // add frame to event
            event->addFrame(frame);
            event->addSnapshot(snap);
            framecount ++;
            emptycount = 0;
        }
        // Did not detect change
        else if (event != NULL){
            emptycount ++;
            // create new frame
            frame = new Frame(this, shot, path);
            snap = new Snapshot(frame, bg->Foreground());
            frame->setSnapshot(snap);
            // add frame to event
            event->addFrame(frame);
            event->addSnapshot(snap);
            framecount ++;
            if(emptycount > maxcount){
                if (framecount - emptycount > mincount){
                    // remove extra frames with no movement
                    for (int i = 0; i < maxcount; i++){
                        event->remLastFrame();
                        event->remLastSnapshot();
                    }
                    events.push_back(event);
                } else {
                    delete event;
                }
                event = NULL;
                emptycount = 0;
                framecount = 0;
            }
        }
        j++;
    }
    // Check if Video ended in the middle of an Event.
    if (event != NULL){
        if (framecount > mincount){
            events.push_back(event);
        } else {
            delete event;
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
