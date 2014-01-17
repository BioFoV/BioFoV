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

#ifndef INC_STDIO
#define INC_STDIO
#include <stdio.h>
#endif

#define IMG_EXT ".image.png"

class Video;
class Snapshot;

///
/// \brief Class that represents Frames.
///
class Frame{
private:
	// external references
	Video *vid;
	// class data
    std::string filename;

    std::deque<Snapshot *> snap;
	
public:
	// Constructors
    /// \brief Simple constructor.
	Frame();
    /// \brief Constructor with reference to the Video source from which the
    ///Frame was taken.
    Frame(Video *source_vid);
    /// \brief Constructor with reference to the Video source from which the
    ///Frame was taken and the image itself.
    Frame(Video *source_vid, cv::Mat shot);

    // Destructor
    /// \brief Simple destructor.
    ~Frame();

    // Functions
    void setImage(cv::Mat shot);
    void setSnapshot(Snapshot *insnap);
    cv::Mat getImage();
};
#endif
