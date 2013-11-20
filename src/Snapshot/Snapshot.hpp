/*
 * Class that associated with a Frame represents an area of interest in
 * a frame.
 */
#ifndef SNAP_H
#define SNAP_H
class Frame;

class Snapshot{
private:
	// external references
	Frame image;
	// class data
	cv::Mat mask;
	
public:
	// Constructor
	Snapshot();
};
#endif
 
