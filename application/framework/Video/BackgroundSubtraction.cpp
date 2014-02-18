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
void BackgroundSubtractor::NewFrame(cv::Mat img, bool f/*=true*/,
                                    bool b/*=true*/, bool c/*=false*/){
    // copy image to object
    frame = img;
    // calculate foreground
    if(f)
        bgsub(img,fore);
    // calculate background
    if(b)
        bgsub.getBackgroundImage(back);
    // draw contours
    if(c){
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
    }
}

cv::Mat BackgroundSubtractor::Foreground(){
    return fore;
}

cv::Mat BackgroundSubtractor::Background(){
    return back;
}

cv::Mat BackgroundSubtractor::Contours(){
    return cont;
}
