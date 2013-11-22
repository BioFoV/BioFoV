// OpenCV
#ifndef OPENCV_INC
#define OPENCV_INC
#include <opencv2/opencv.hpp>
#endif

#ifndef BGSUB_H
#define BGSUB_H
class BackgroundSubtractor {
	private:
		std::vector<std::vector<cv::Point> > contours;
		int history;
		float varThreshold;
		bool bShadowDetection;
		cv::BackgroundSubtractorMOG2 bgsub;
		
	public:
		BackgroundSubtractor();
		
		BackgroundSubtractor(int hist, int varThresh, bool bShadowDet);
		
		cv::Mat Foreground(cv::Mat frame);
		
		cv::Mat Contours(cv::Mat frame);
		
		cv::Mat Background();
};
#endif
