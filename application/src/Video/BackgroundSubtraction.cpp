#include "BackgroundSubtraction.hpp"

/*******************************************************************************
 * Constructors
 ******************************************************************************/
BackgroundSubtractor::BackgroundSubtractor(){
    history = 200;
    varThreshold = 32;
    bShadowDetection = true;
    bgsub = cv::BackgroundSubtractorMOG2(history,  varThreshold,
        bShadowDetection );
}

BackgroundSubtractor::BackgroundSubtractor(int hist, int varThresh,
        bool bShadowDet){
    history = hist;
    varThreshold = varThresh;
    bShadowDetection = bShadowDet;
    bgsub = cv::BackgroundSubtractorMOG2(history,
        varThreshold,
        bShadowDetection );
}

/*******************************************************************************
 * Get foreground, background and contours functions
 ******************************************************************************/
void BackgroundSubtractor::NewFrame(cv::Mat img){
    // copy image to object
    frame = img;
    // calculate foreground
    bgsub(img,fore);
}

void BackgroundSubtractor::Denoise(){
    cv::erode(fore,fore,cv::Mat());
    cv::dilate(fore,fore,cv::Mat());
}

cv::Mat BackgroundSubtractor::Foreground(){
    return fore;
}

cv::Mat BackgroundSubtractor::Background(){
    bgsub.getBackgroundImage(back);
    return back;
}

cv::Mat BackgroundSubtractor::Contours(){
    cont = frame.clone();
    cv::Mat aux = fore.clone();

    cv::erode(aux,aux,cv::Mat());
    cv::dilate(aux,aux,cv::Mat());
    cv::findContours(aux,contours,
        CV_RETR_EXTERNAL,
        CV_CHAIN_APPROX_NONE);
    cv::drawContours(cont,
        contours,
        -1,
        cv::Scalar(0,0,255),
        1);
    return cont;
}
