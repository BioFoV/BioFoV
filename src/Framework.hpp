/*
 * This framework should comprehend all the libs needed for the program
 * to function.
 */

// OpenCV
#ifndef OPENCV_INC
#define OPENCV_INC
#include <opencv2/opencv.hpp>
#endif

// IOStream
#ifndef IOSTREAM_INC
#define IOSTREAM_INC
#include <iostream>
#endif

class Video;
class Frame;
class Snapshot;
class Event;
class Individual;
class Feature;

/*
 * Class that holds the VideoCapture handler and that provides frames
 */
#ifndef VIDEO_H
#define VIDEO_H
class Video {
private:
	cv::VideoCapture cap;
	
	std::list<Frame> frames;
	
public:
	// Constructor
	Video(){
		
	}
	void GetNextFrame(){
	}
};
#endif

/*
 * Class that represents Frames
 */
#ifndef FRAME_H
#define FRAME_H
class Frame{
private:
	// external references
	Video vid;
	// class data
	cv::Mat image;
	
public:
	// Constructor
	Frame(){
	}
};
#endif

/*
 * Class that associated with a Frame represents an area of interest in
 * a frame.
 */
#ifndef SNAP_H
#define SNAP_H
class Snapshot{
private:
	// external references
	Frame image;
	// class data
	cv::Mat mask;
	
public:
	// Constructor
	Snapshot(){
	}
};
#endif

/*
 * Class that represents a contiguous set of frames with something
 * interesting on them.
 */
#ifndef EVENT_H
#define EVENT_H
class Event{
private:
	// external references
	Video vid;
	std::list<Frame> frames;
	std::list<Individual> individuals;
	
public:
	// Constructor
	Event(){
	}
};
#endif

/*
 * Class that represents an individual, and has associated with it the
 * various Events and Snapshots where this same individual shows up.
 * An Individual also has several Features that can be used for later
 * matching.
 */
#ifndef INDIV_H
#define INDIV_H
class Individual{
private:
	// external references
	std::list<Event> events;
	std::list<Snapshot> snapshots;
	
public:
	// Constructor
	Individual(){
	}
};
#endif

/*
 * Class that holds the data of a certain individual.
 * This container can be used for holding deterministic features or
 * sets of samples.
 */
#ifndef FEAT_H
#define FEAT_H
class Feature{
private:
	// external references
	Individual ind;
	// class data
	std::string description;
	
public:
	// Constructor
	Feature(){
	}
};
#endif

