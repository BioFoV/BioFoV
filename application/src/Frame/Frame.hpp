#ifndef FRAME_H
#define FRAME_H

// OpenCV
#ifndef OPENCV_INC
#define OPENCV_INC
#include <opencv2/opencv.hpp>
#endif

#ifndef INC_VIDEO
#define INC_VIDEO
#include <Video/Video.hpp>
#endif

#ifndef INC_PLAYER
#define INC_PLAYER
#include <player.hpp>
#endif

#ifndef INC_STDIO
#define INC_STDIO
#include <stdio.h>
#endif

#ifndef INC_DRAWABLES
#define INC_DRAWABLES
#include <Drawables/drawable.hpp>
#endif

#define IMG_EXT ".image.png"

#include <QObject>

class Video;

class Frame;
typedef QSharedPointer<Frame> FramePtr;

/**
 * @brief Class that represents Frames.
 */
class Frame : public QObject , public Player {
    Q_OBJECT

private:
    /**
     * @brief Video object from which this Frame was extracted.
     */
    Video *vid;

    /**
     * @brief Frame number in the video.
     */
    unsigned int frameNumber;

    /**
     * @brief Filename of the Frame.
     */
    std::string filename;

//    FramePtr thisPtr;

public:
    // Constructors
    Frame();
    Frame(Video *source_vid, cv::Mat shot, std::string path);

    virtual ~Frame();

    // Functions
    void setImage(cv::Mat shot);
    unsigned int getNumber();

    // Capture functions
    bool check_cap();
    bool setFramePos(double);
    double getFramePos();
    bool getFrame(cv::Mat &frame);
    bool getPrevFrame(cv::Mat &frame);
    bool getNextFrame(cv::Mat &frame);
    FramePtr getCurrentFrameRef();
    uint getCurrentFrameNumber();

    bool stepForward();
    bool stepBackwards();

    // Properties
    double getFrameInt();
    double getFPS();
    double getLengthTime();
    double getLengthFrames();

    void mousePressEvent(cv::Point point);
    void mouseReleaseEvent(cv::Point point);
    void mouseMoveEvent(cv::Point point);

    void save(std::string fname);

    TStrDoubleMap getValues();

signals:
    void updateValues();
};
#endif
