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
    switch (npoints) {
    case 3:
        cv::circle(frame, points[3], 3, cv::Scalar( 0, 0, 255), -1, 8, 0);
        cv::line(frame, points[3], points[2], cv::Scalar( 0, 255, 0));
    case 2:
        cv::circle(frame, points[2], 3, cv::Scalar( 0, 0, 255), -1, 8, 0);
    case 1:
        cv::circle(frame, points[1], 3, cv::Scalar( 0, 0, 255), -1, 8, 0);
        cv::line(frame, points[1], points[0], cv::Scalar( 0, 255, 0));
    case 0:
        cv::circle(frame, points[0], 3, cv::Scalar( 0, 0, 255), -1, 8, 0);
    default:
        break;
    }
}

void DrawHeight::apply(){

}
