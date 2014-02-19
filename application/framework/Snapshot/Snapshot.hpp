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

#ifndef INC_STDIO
#define INC_STDIO
#include <stdio.h>
#endif

#define SNAP_EXT ".snap.png"

class Frame;

///
/// \brief Class that associated with a Frame represents an area of interest in
///a frame.
///
class Snapshot{
private:
    /// \brief External Frame reference.
	Frame *image;

    cv::Rect rect;

	// class data
    std::string filename;
	
public:
    /// \brief Simple constructor.
	Snapshot();

    /// \brief Simple destructor.
    ~Snapshot();

    /// \brief Constructor with a reference to the Frame this Snapshot relates
    ///to.
    /// \param img Pointer to the refered Frame.
	Snapshot(Frame *img);

    /// \brief Constructor with a reference to the Frame this Snapshot relates
    ///to, and the image mask.
    /// \param img Pointer to the refered Frame.
    /// \param inmask Mask that defines where something is.
    Snapshot(Frame *img, cv::Mat inmask);

    Snapshot(Frame *img, cv::Rect inrect);

    // Functions
    cv::Mat getMask();
    cv::Mat getMasked();
};
#endif
