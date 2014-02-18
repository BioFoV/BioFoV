#include "faces.hpp"

Face::Face(std::string haar_filename){
    model = cv::createLBPHFaceRecognizer();
    haar_cascade.load(haar_filename);
}

void Face::addEvent(Event * newEvent){
    events.push_back(newEvent);
}

void Face::findFaces(Frame *newFrame){
    cv::Mat gray;
    cv::Mat img = newFrame->getImage();
    cv::cvtColor(img, gray, CV_BGR2GRAY);
    std::vector< cv::Rect_<int> > faces;
    haar_cascade.detectMultiScale(img, faces);
    for(unsigned int i = 0; i < faces.size(); i++) {
        cv::Rect face_i = faces[i];
        // Crop the face from the image. So simple with OpenCV C++:
        cv::Mat face = gray(face_i);
        cv::imshow("haar output", face);
        cv::waitKey(10);
        Snapshot* newSnap = new Snapshot(newFrame, face);
        snapshots.push_back(newSnap);
    }
}
