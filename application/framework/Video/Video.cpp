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
    lengthFrames = cap.get(CV_CAP_PROP_FRAME_COUNT);
    readAll();
    cap.release();
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
double Video::readAll(){
    cv::Mat *image = new cv::Mat;
    Frame* frame;
    double framesRead = 0;

    while (cap.read(*image)){
        framesRead ++;
        frame = new Frame(this, image);
        frames.push_back(frame);
        image = new cv::Mat;
    }
    return framesRead;
}

bool Video::check_cap(){
    if(!frames.empty()){
		return true;
	}
	std::cerr << "Couldn't open " << filename << std::endl;
	return false;
}

double Video::getFramePos(){
    return position;
}

bool Video::setFramePos(double frameNum){
    if (frameNum > getLengthFrames()){
        return false;
    } else{
        position = frameNum;
        return true;
    }
}

cv::Mat* Video::getFrame(){
	if(!check_cap()){
        return NULL;
	}
    position++;
    try{
        return frames.at(position)->getImage();
    } catch (std::out_of_range){
        return NULL;
    }
}

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

double Video::getLengthTime(){
    return getLengthFrames()/getFPS();
}

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
