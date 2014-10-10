#ifndef FACES_HPP
#define FACES_HPP

// OpenCV
#ifndef OPENCV_INC
#define OPENCV_INC
#include <opencv2/opencv.hpp>
#endif

#ifndef INC_FEATURE
#define INC_FEATURE
#include <Feature/Feature.hpp>
#endif

#ifndef INC_EVENT
#define INC_EVENT
#include <Event/Event.hpp>
#endif

#ifndef INC_SNAPSHOT
#define INC_SNAPSHOT
#include <Snapshot/Snapshot.hpp>
#endif

#ifndef INC_FRAME
#define INC_FRAME
#include <Frame/Frame.hpp>
#endif

class Face;

/**
 * @brief FacePtr
 */
typedef QSharedPointer<Face> FacePtr;

/**
 * @brief The Face class
 */
class Face : public Feature {
private:
    /**
     * @brief model
     */
    cv::Ptr<cv::FaceRecognizer> model;

    /**
     * @brief haar_cascade
     */
    cv::CascadeClassifier haar_cascade;

    /**
     * @brief snapshots
     */
    std::deque<SnapshotPtr> snapshots;

public:
    Face(std::string haar_filename);
    ~Face();
    void findFaces(FramePtr newFrame);
    unsigned int faceNumber();
    SnapshotPtr getFaceAt(unsigned int i);
};

#endif // FACES_HPP
