#include "drawheight.hpp"

DrawHeight::DrawHeight() {
    npoints = 0;
}

void DrawHeight::press(cv::Point pi1){

}

bool DrawHeight::release(cv::Point pi2){

    npoints ++;
    if (npoints < 4){
        return true;
    }
    else {
        return false;
    }
}

void DrawHeight::draw(cv::Point pi2, cv::Mat& frame){

}

void DrawHeight::apply(){

}
