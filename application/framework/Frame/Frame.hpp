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
    /// \brief Video object from which this Frame was extracted.
	Video *vid;
    /// \brief Filename of the Frame.
    std::string filename;
    /// \brief Deque of Snapshot that relate to this Frame.
    std::deque<Snapshot *> snap;
	
public:
	// Constructors
    /// \brief Simple constructor.
	Frame();
    /// \brief Constructor with reference to the Video source from which the
    ///Frame was taken.
    /// \param source_vid Video from which the Frame was extracted.
    Frame(Video *source_vid);
    /// \brief Constructor with reference to the Video source from which the
    ///Frame was taken and the image itself.
    /// \param source_vid Video from which the Frame was extracted.
    /// \param shot The image itself.
    Frame(Video *source_vid, cv::Mat shot);

    // Destructor
    /// \brief Simple destructor.
    ~Frame();

    // Functions
    /// \brief Sets the image of the Frame.
    ///Use this if you didn't specify it in the constructor.
    /// \param shot Image of the Frame.
    void setImage(cv::Mat shot);
    /// \brief Adds a Snapshot to the Frame.
    /// \param insnap Snapshot to be added to the deque of this Frame.
    void setSnapshot(Snapshot *insnap);
    cv::Mat getImage();
};
#endif
