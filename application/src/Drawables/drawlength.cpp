#include "drawlength.hpp"

DrawLength::DrawLength()
{
    npoints = -1;
}

DrawLength::~DrawLength(){

}

void DrawLength::press(cv::Point){

}

void DrawLength::release(cv::Point pi2){
    if (isDone())
        return;
    npoints ++;
    points[npoints] = pi2;

    if (isDone()){
        result = cv::norm(points[1]-points[0]);
        values.push_back(TStrDoublePair("Length",result));
    }
}

void DrawLength::draw(cv::Mat& frame){
    int largest = int(frame.rows<frame.cols?frame.rows:frame.cols);
    int rad = CIRCLE_RATIO * largest;
    int thick = LINE_RATIO * largest;

    switch (npoints) {
    case 1: // 2nd point
        cv::circle(frame, points[1], rad, cv::Scalar( 0, 0, 255), -1, CV_AA, 0);
        cv::line(frame, points[1], points[0], cv::Scalar( 255, 0, 0), thick, CV_AA);
    case 0: // 1st point
        cv::circle(frame, points[0], rad, cv::Scalar( 0, 0, 255), -1, CV_AA, 0);
    default:
        break;
    }

}

void DrawLength::move(cv::Point){

}

bool DrawLength::isDone(){
    return (npoints >= 1);
}

std::string DrawLength::getDescription(){
    return std::string("Length");
}
