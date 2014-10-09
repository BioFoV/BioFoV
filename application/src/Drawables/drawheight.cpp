#include "drawheight.hpp"

DrawHeight::DrawHeight() {
    npoints = -1;
    calculated = false;
}

DrawHeight::~DrawHeight() {

}

void DrawHeight::press(cv::Point){

}

void DrawHeight::release(cv::Point pi2){
    if (isDone())
        return;
    npoints ++;
    points[npoints] = pi2;
    if (isDone()) {
        auxpoints[0].x = (points[0].x + points[1].x)/2;
        auxpoints[0].y = points[0].y;
        auxpoints[1].x = auxpoints[0].x;
        auxpoints[1].y = points[1].y;
        values.push_back(TStrDoublePair("Height", abs(points[1].y - points[0].y)));
    }
}

void DrawHeight::draw(cv::Mat& frame){
    int largest = int(frame.rows<frame.cols?frame.rows:frame.cols);
    int rad = CIRCLE_RATIO * largest;
    int thick = LINE_RATIO * largest;

    if(!isVisible())
        return;

    switch (npoints) {
    case 1: // 2nd point
        cv::line(frame, points[0], auxpoints[0], cv::Scalar( 255, 0, 0), thick, CV_AA);
        cv::line(frame, auxpoints[0], auxpoints[1], cv::Scalar( 0, 255, 0), thick, CV_AA);
        cv::line(frame, auxpoints[1], points[1], cv::Scalar( 255, 0, 0), thick, CV_AA);
        cv::circle(frame, points[1], rad, cv::Scalar( 0, 0, 255), -1, CV_AA, 0);
    case 0: // 1st point
        cv::circle(frame, points[0], rad, cv::Scalar( 0, 0, 255), -1, CV_AA, 0);
    default:
        break;
    }
}

void DrawHeight::move(cv::Point /*point - unused*/){

}

bool DrawHeight::isDone(){
    return (npoints >= 1);
}

std::string DrawHeight::getDescription(){
    return std::string("Height");
}

std::string DrawHeight::getIcon() {
    return ":/icons/height";
}
