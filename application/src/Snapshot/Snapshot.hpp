#ifndef SNAP_H
#define SNAP_H

// OpenCV
#ifndef OPENCV_INC
#define OPENCV_INC
#include <opencv2/opencv.hpp>
#endif

#ifndef INC_FRAME
#define INC_FRAME
#include "../Frame/Frame.hpp"
#endif

#ifndef INC_PLAYER
#define INC_PLAYER
#include "../player.hpp"
#endif

#ifndef INC_STDIO
#define INC_STDIO
#include <stdio.h>
#endif

#define SNAP_EXT ".snap.png"

#include <QSharedPointer>

class Frame;
typedef QSharedPointer<Frame> FramePtr;

class Snapshot;
typedef QSharedPointer<Snapshot> SnapshotPtr;

///
/// \brief Class that associated with a Frame represents an area of interest in
///a frame.
///
class Snapshot : public Player {
private:
	/// \brief External Frame reference.
	FramePtr image;

	cv::Rect rect;

	// class data
	std::string filename;

public:
	Snapshot();
	Snapshot(FramePtr img);
	Snapshot(FramePtr img, cv::Mat inmask, std::string path);
	Snapshot(FramePtr img, cv::Rect inrect);

	virtual ~Snapshot();

	// Functions
	cv::Mat getMask();
	cv::Mat getMasked();

	bool check_cap();

	bool setFramePos(double frameNum);

	double getFramePos();

	bool getFrame(cv::Mat &frame);

	bool getNextFrame(cv::Mat &frame);

	bool getPrevFrame(cv::Mat &frame);

	bool stepForward();
	bool stepBackwards();

	double getFrameInt();

	double getFPS();

	double getLengthTime();

	double getLengthFrames();

	FramePtr getCurrentFrameRef();

	unsigned int getCurrentFrameNumber();

	void mousePressEvent(cv::Point){}
	void mouseReleaseEvent(cv::Point){}
	void mouseMoveEvent(cv::Point){}

	void save(std::string fname);
};
#endif
