#include "faces.hpp"

/**
 * @brief Face::Face
 * @param haar_filename
 */
Face::Face(std::string haar_filename){
	model = cv::createLBPHFaceRecognizer();
	haar_cascade.load(haar_filename);
}

/**
 * @brief Face::~Face
 */
Face::~Face(){

}

/**
 * @brief Face::findFaces
 * @param newFrame
 */
void Face::findFaces(FramePtr newFrame){
	cv::Mat gray;
	SnapshotPtr newSnap;

	cv::Mat img;
	newFrame->getFrame(img);

	cv::cvtColor(img, gray, CV_BGR2GRAY);
	std::vector< cv::Rect_<int> > faces;
	haar_cascade.detectMultiScale(img, faces);
	for(unsigned int i = 0; i < faces.size(); i++) {
		cv::Rect face_i = faces[i];
		newSnap = SnapshotPtr(new Snapshot(newFrame, face_i));
		snapshots.push_back(newSnap);
	}
}

/**
 * @brief Face::faceNumber
 * @return
 */
unsigned int Face::faceNumber(){
	return snapshots.size();
}

/**
 * @brief Face::getFaceAt
 * @param i
 * @return
 */
SnapshotPtr Face::getFaceAt(unsigned int i){
	return snapshots.at(i);
}
