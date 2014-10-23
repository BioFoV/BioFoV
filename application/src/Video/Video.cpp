#include "Video.hpp"

/*******************************************************************************
 * Constructors
 ******************************************************************************/
/**
 * @brief Simple constructor.
 */
Video::Video(){
	bg = NULL;
	activeDrawable = NULL;
}

/**
 * @brief Constructor providing cv VideoCapture.
 * @param capture CV capture object.
 */
Video::Video(cv::VideoCapture capture){
	bg = NULL;
	cap = capture;
	activeDrawable = NULL;
}

/**
 * @brief Video constructor providing a file name.
 * @param name File name.
 */
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
/**
 * @brief Simple destructor.
 */
Video::~Video(){
	if (bg != NULL){
		delete bg;
	}
}

/*******************************************************************************
 * Set and Get
 ******************************************************************************/
/**
 * @brief Changes the filename to the string provided.
 * @param name New filename.
 */
void Video::setFileName(std::string name){
	filename = name;
}

/**
 * @brief Get filename.
 * @return Filename of the Video if there is one, otherwise returns NULL.
 */
std::string Video::getFileName(){
	return filename;
}

/**
 * @brief Changes the CV VideoCapture object to a new one.
 * @param capture New CV VideoCapture object of the Video.
 */
void Video::setCapture(cv::VideoCapture capture){
	cap = capture;
}

/**
 * @brief Get CV VideoCapture object.
 * @return CV VideoCapture object of the Video.
 */
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

/**
 * @brief Video::getSize
 * @return
 */
cv::Size Video::getSize(){
	return resolution;
}

/**
 * @brief Check if video is calibrated.
 * @return true if calibrated, false otherwise.
 */
bool Video::isCalibrated(){
	if (cam != NULL){
		return cam->isCalibrated();
	}
	return false;
}

/*******************************************************************************
 * Background Subtraction functions
 ******************************************************************************/
/**
 * @brief Initializes the CV background subtractor object.
 * @param hist
 * @param varThresh
 * @param bShadowDet
 */
void Video::bgSubInit(int hist, int varThresh, bool bShadowDet){
	bg = new BackgroundSubtractor(hist,varThresh,bShadowDet);
}

/**
 * @brief Purges the CV background subtractor object linked to this Video.
 */
void Video::bgSubDelete(){
	delete bg;
}

/*******************************************************************************
 * Event autoDetection
 ******************************************************************************/
/**
 * @brief Video::convertToEvent
 * @param path
 * @return
 */
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

/**
 * @brief Automatically splits the video into several events provided the
 * given parameters.
 * @param threshold
 * @param maxcount
 * @param mincount
 * @param history
 * @param varThreshold
 * @param bShadowDetection
 * @param path
 * @return
 */
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

/**
 * @brief calibrate Calibrates the camera based on this Video.
 *
 * If this Video has enough chessboard pattern frames on it, and they are
 * described by the arguments given to the function, the function will
 * calibrate the video and after the call, all other player implemented
 * functions that ask for a frame will have an undistorted frame.
 *
 * @param nBoards Maximum number of boards to be detected.
 * After this number, it stops. Use frameStep to skip frames if there are a
 * lot of frames with similar pattern positions.
 * @param frameStep Steps frames to avoid similar ones.
 * @param boardW Number of inner corners of the pattern, on width.
 * @param boardH Number of inner corners of the pattern, on height.
 * @param iterations Number of iterations to be passed to the BackgroundSubtractor object. 1~5 is normally enough.
 * @param flags
 */
void Video::calibrate(int nBoards, int frameStep, int boardW,
					  int boardH, int iterations, unsigned int flags) {

	// Rewind to the beginning
	setFramePos(0);

//	if (cam != NULL){
//		delete cam;
//	}
	cam = new Camera(this, boardW, boardH);
	cam->set_calib_flags(flags);
	cam->calibrate(nBoards, frameStep, iterations);

	// Rewind again
	setFramePos(0);
}

/**
 * @brief Video::deleteCalibration
 */
void Video::deleteCalibration() {
	delete cam;
	cam = NULL;
}

/**
 * @brief Video::flip_horizontally
 */
void Video::flip_horizontally(){
	if (cam == NULL){
		cam = new Camera(this);
	}
	cam->flip_horizontal();
}

/**
 * @brief Video::flip_vertically
 */
void Video::flip_vertically(){
	if (cam == NULL){
		cam = new Camera(this);
	}
	cam->flip_vertical();
}

/**
 * @brief Video::getCamera
 * @return
 */
Camera* Video::getCamera(){
	return cam;
}

/**
 * @brief Video::importCamera
 * @return
 */
bool Video::importCamera(){
	cam = new Camera(this);

	if (!cam->read_file()){
		delete cam;
		return false;
	}
	return true;
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

/**
 * @brief Video::cancel
 */
void Video::cancel() {
	toCancel = true;
}

/**
 * @brief Video::canceled
 */
void Video::canceled() {
	toCancel = false;
}
