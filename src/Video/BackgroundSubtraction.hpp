// OpenCV
#ifndef OPENCV_INC
#define OPENCV_INC
#include <opencv2/opencv.hpp>
#endif

#ifndef BGSUB_H
#define BGSUB_H
/*
 * Class that holds the VideoCapture handler and that provides frames
 */
class BackgroundSubtractor {
private:
	std::vector<std::vector<cv::Point> > contours;
	int history;
	float varThreshold;
	bool bShadowDetection;
	cv::BackgroundSubtractorMOG2 bgsub;
	
	// images of the different stages
	cv::Mat frame;	// original frame
	cv::Mat fore;	// foreground mask
	cv::Mat back;	// background image
	cv::Mat cont;	// contours after erosion and dilation
	
public:
	// Constructors
	BackgroundSubtractor();
	BackgroundSubtractor(int hist, int varThresh, bool bShadowDet);
	
	// Get foreground, background and contours functions
	void NewFrame(cv::Mat img, bool f=true, bool b=true, bool c=false);
	cv::Mat Foreground();
	cv::Mat Background();
	cv::Mat Contours();
};
#endif
