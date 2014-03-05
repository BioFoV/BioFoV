#include "rectanglemask.hpp"

RectangleMask::RectangleMask()
{
}

RectangleMask::~RectangleMask()
{
}

// Click
void RectangleMask::press(cv::Point pi1){
    p[0] = pi1;
    p[1] = pi1;
}

void RectangleMask::release(cv::Point pi2){

}

// Draw
void RectangleMask::draw(cv::Mat& frame){
    cv::rectangle(frame, p[0], p[1], cv::Scalar( 0, 0, 255));
}

void RectangleMask::move(cv::Point point){
    p[1] = point;
}

bool RectangleMask::isDone(){
    return false; //FIXME This is just a placeholder
}
