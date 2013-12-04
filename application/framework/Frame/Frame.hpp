#ifndef FRAME_H
#define FRAME_H

// OpenCV
#ifndef OPENCV_INC
#define OPENCV_INC
#include <opencv2/opencv.hpp>
#endif

#ifndef INC_VIDEO
#define INC_VIDEO
#include "../Video/Video.hpp"
#endif

#ifndef INC_SNAPSHOT
#define INC_SNAPSHOT
#include "../Snapshot/Snapshot.hpp"
#endif

class Video;
class Snapshot;

/*
 * Class that represents Frames
 */
class Frame{
private:
	// external references
	Video *vid;
	// class data
	cv::Mat image;
    Snapshot * snap;
	
public:
	// Constructors
	Frame();
    Frame(Video *source_vid);
    Frame(Video *source_vid, cv::Mat shot);
    void setImage(cv::Mat shot);
    void setSnapshot(Snapshot *insnap);
};
#endif
