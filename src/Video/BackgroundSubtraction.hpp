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
	
public:
	// Constructors
	BackgroundSubtractor();
	BackgroundSubtractor(int hist, int varThresh, bool bShadowDet);
	
	// Get foreground, background and contours functions
	cv::Mat Foreground(cv::Mat frame);
	cv::Mat Background();
	cv::Mat Contours(cv::Mat frame);
};
#endif
