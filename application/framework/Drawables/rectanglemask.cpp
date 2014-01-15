#include "rectanglemask.hpp"

RectangleMask::RectangleMask()
{
}

// Click
void RectangleMask::press(cv::Point pi1){
    p[0] = pi1;
}

bool RectangleMask::release(cv::Point pi2){
    p[1] = pi2;
    return false;
}

// Draw
void RectangleMask::draw(cv::Point pi2, cv::Mat& frame){
    cv::rectangle(frame, p[0], pi2, cv::Scalar( 0, 0, 255));
}

// Apply
double RectangleMask::apply(cv::Mat &frame){

}
