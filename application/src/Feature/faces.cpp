#include "faces.hpp"

Face::Face(std::string haar_filename){
    model = cv::createLBPHFaceRecognizer();
    haar_cascade.load(haar_filename);
}

Face::~Face(){

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
        Snapshot* newSnap = new Snapshot(newFrame, face_i);
        snapshots.push_back(newSnap);
    }
}

unsigned int Face::faceNumber(){
    return snapshots.size();
}

Snapshot* Face::getFaceAt(unsigned int i){
    return snapshots.at(i);
}
