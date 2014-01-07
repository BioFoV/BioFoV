#include "rectanglemask.hpp"

RectangleMask::RectangleMask()
{
}

// Click
void RectangleMask::press(cv::Point pi1){
    p1 = pi1;
}

void RectangleMask::release(cv::Point pi2){
    p2 = pi2;
}

// Draw
void RectangleMask::draw(cv::Point pi2, cv::Mat& frame){
    cv::rectangle(frame, p1, pi2, cv::Scalar( 0, 0, 255));
}

// Apply
void RectangleMask::apply(){

}
