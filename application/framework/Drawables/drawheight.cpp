#include "drawheight.hpp"

DrawHeight::DrawHeight() {
    npoints = -1;
}

void DrawHeight::press(cv::Point pi1){

}

bool DrawHeight::release(cv::Point pi2){
    npoints ++;
    points[npoints] = pi2;

    if (npoints < 3){
        return true;
    }
    else {
        return false;
    }
}

void DrawHeight::draw(cv::Point pi2, cv::Mat& frame){
    int largest = int(frame.rows>frame.cols?frame.rows:frame.cols);
    int rad = CIRCLE_RATIO * largest;
    int thick = LINE_RATIO * largest;

    switch (npoints) {
    case 3:
        cv::circle(frame, points[3], rad, cv::Scalar( 0, 0, 255), -1, CV_AA, 0);
        cv::line(frame, points[3], points[2], cv::Scalar( 0, 255, 0), thick, CV_AA);
    case 2:
        cv::circle(frame, points[2], rad, cv::Scalar( 0, 0, 255), -1, CV_AA, 0);
    case 1:
        cv::circle(frame, points[1], rad, cv::Scalar( 0, 0, 255), -1, CV_AA, 0);
        cv::line(frame, points[1], points[0], cv::Scalar( 255, 0, 0), thick, CV_AA);
    case 0:
        cv::circle(frame, points[0], rad, cv::Scalar( 0, 0, 255), -1, CV_AA, 0);
    default:
        break;
    }
}

void DrawHeight::apply(){

}
