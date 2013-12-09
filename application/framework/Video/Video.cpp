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
    resolution[0] = cap.get(CV_CAP_PROP_FRAME_WIDTH);
    resolution[1] = cap.get(CV_CAP_PROP_FRAME_HEIGHT);
//    cap.release();
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
	std::cerr << "Couldn't open " << filename << std::endl;
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
		return true;
	}
	else{
		std::cerr << "Couldn't read frame" << std::endl;
		return false;
	}
}

bool Video::getPrevFrame(cv::Mat &frame){
    double tempPos = getFramePos();
    if (tempPos > 1){
        setFramePos(tempPos-2);
        return getFrame(frame);
    } else {
        return false;
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

double Video::getLengthTime(){
    return getLengthFrames()/getFPS();
}

double Video::getLengthFrames(){
    return cap.get(CV_CAP_PROP_FRAME_COUNT);
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
    cv::Mat shot;
    Frame *frame;
    Snapshot *snap;
    Event *event = new Event(this); // new empty event
    unsigned int iter;

    // Initialization of background subtraction
    bgSubInit(1000, 50, false);

    setFramePos(0);

    while(getFrame(shot)){
        bg->NewFrame(shot);

        // create new frame
        frame = new Frame(this, shot);
        snap = new Snapshot(frame, bg->Foreground());
        frame->setSnapshot(snap);
        frames.push_back(frame);
        event->addFrame(frame);
        event->addSnapshot(snap);
    }

    std::deque<Event*> splited = event->splitEvent(200,3, 5);
    for (iter = 0; iter < splited.size(); iter++){
        events.push_back(splited.at(iter));
    }

    return events;
}
