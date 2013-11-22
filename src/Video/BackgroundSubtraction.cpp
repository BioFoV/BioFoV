#include "BackgroundSubtraction.hpp"

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

cv::Mat BackgroundSubtractor::Foreground(cv::Mat frame){
	cv::Mat fore;
	
	bgsub(frame,fore);
	return fore;
}
	
cv::Mat BackgroundSubtractor::Contours(cv::Mat frame){
	cv::Mat fore = Foreground(frame);
	
	cv::erode(fore,fore,cv::Mat());
	cv::dilate(fore,fore,cv::Mat());
	cv::findContours(fore,contours,
		CV_RETR_EXTERNAL,
		CV_CHAIN_APPROX_NONE);
	cv::drawContours(frame,
		contours,
		-1,
		cv::Scalar(0,0,255),
		1);
	
	return frame;
}

cv::Mat BackgroundSubtractor::Background(){
	cv::Mat back;
	bgsub.getBackgroundImage(back);
	return back;
}

