#include "drawangle.hpp"

/**
 * @brief Simple constructor.
 */
DrawAngle::DrawAngle() {
	npoints = -1;
	calculated = false;
}

/**
 * @brief Simple destructor
 */
DrawAngle::~DrawAngle() {

}

void DrawAngle::press(cv::Point){

}

void DrawAngle::release(cv::Point pi2){
	if (isDone())
		return;
	npoints ++;
	points[npoints] = pi2;

	if (isDone()){
		double p01, p12, p02;

		p01 = std::sqrt(std::pow(points[0].x - points[1].x,2) \
				+ std::pow(points[0].y - points[1].y,2));
		p12 = std::sqrt(std::pow(points[1].x - points[2].x,2) \
				+ std::pow(points[1].y - points[2].y,2));
		p02 = std::sqrt(std::pow(points[0].x - points[2].x,2) \
				+ std::pow(points[0].y - points[2].y,2));

		angle = std::acos((std::pow(p01,2) + std::pow(p12,2) - std::pow(p02,2)) \
						  /(2*p01*p12));

		values.push_back(TStrDoublePair("angle",angle));
	}
}

void DrawAngle::draw(cv::Mat& frame){
	int largest = int(frame.rows<frame.cols?frame.rows:frame.cols);
	int rad = CIRCLE_RATIO * largest;
	int thick = LINE_RATIO * largest;

	if(!isVisible())
		return;

	switch (npoints) {
	case 2: // 3rd point
		cv::line(frame, points[2], points[1], cv::Scalar( 0, 255, 0), thick, CV_AA);
		cv::circle(frame, points[2], rad, cv::Scalar( 0, 0, 255), -1, CV_AA, 0);
	case 1: // 2nd point
		cv::line(frame, points[1], points[0], cv::Scalar( 255, 0, 0), thick, CV_AA);
		cv::circle(frame, points[1], rad, cv::Scalar( 0, 0, 255), -1, CV_AA, 0);
	case 0: // 1st point
		cv::circle(frame, points[0], rad, cv::Scalar( 0, 0, 255), -1, CV_AA, 0);
	default:
		break;
	}
}

void DrawAngle::move(cv::Point /*point - unused*/){

}

bool DrawAngle::isDone(){
	return (npoints >= 2);
}

std::string DrawAngle::getDescription(){
	return std::string("Angle");
}

std::string DrawAngle::getIcon() {
	return "";
}
