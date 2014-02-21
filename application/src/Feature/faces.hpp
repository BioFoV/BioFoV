#ifndef FACES_HPP
#define FACES_HPP

// OpenCV
#ifndef OPENCV_INC
#define OPENCV_INC
#include <opencv2/opencv.hpp>
#endif

#ifndef INC_FEATURE
#define INC_FEATURE
#include "Feature.hpp"
#endif

#ifndef INC_EVENT
#define INC_EVENT
#include "../Event/Event.hpp"
#endif

#ifndef INC_SNAPSHOT
#define INC_SNAPSHOT
#include "../Snapshot/Snapshot.hpp"
#endif

#ifndef INC_FRAME
#define INC_FRAME
#include "../Frame/Frame.hpp"
#endif

class Face : public Feature {
private:
    cv::Ptr<cv::FaceRecognizer> model;
    cv::CascadeClassifier haar_cascade;
    std::deque<Event *> events;
    std::deque<Snapshot *> snapshots;
public:
    Face(std::string haar_filename);
    void findFaces(Frame * newFrame);
    void addEvent(Event * newEvent);
    unsigned int faceNumber();
    Snapshot * getFaceAt(unsigned int i);
};

#endif // FACES_HPP
