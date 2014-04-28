#include "drawwidth.hpp"

DrawWidth::DrawWidth() {
    npoints = -1;
    calculated = false;
}

DrawWidth::~DrawWidth() {

}

void DrawWidth::press(cv::Point){

}

void DrawWidth::release(cv::Point pi2){
    if (isDone())
        return;
    npoints ++;
    points[npoints] = pi2;
    if (isDone()) {
        auxpoints[0].x = points[0].x;
        auxpoints[0].y = (points[0].y + points[1].y)/2;
        auxpoints[1].x = points[1].x;
        auxpoints[1].y = auxpoints[0].y;
        values.push_back(TStrDoublePair("Width", abs(points[1].x - points[0].x)));
    }
}

void DrawWidth::draw(cv::Mat& frame){
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

void DrawWidth::move(cv::Point /*point - unused*/){

}

bool DrawWidth::isDone(){
    return (npoints >= 1);
}

std::string DrawWidth::getDescription(){
    return std::string("Width");
}
