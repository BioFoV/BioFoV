#ifndef BGSUB_H
#define BGSUB_H

// OpenCV
#ifndef OPENCV_INC
#define OPENCV_INC
#include <opencv2/opencv.hpp>
#endif

#ifndef INC_VECTOR
#define INC_VECTOR
#include <vector>
#endif

///
/// \brief Class that holds the VideoCapture handler and that provides frames.
///
class BackgroundSubtractor {
private:
    /**
     * @brief contours
     */
	std::vector<std::vector<cv::Point> > contours;

    /**
     * @brief history
     */
	int history;

    /**
     * @brief varThreshold
     */
	float varThreshold;

    /**
     * @brief bShadowDetection
     */
	bool bShadowDetection;

    /**
     * @brief bgsub
     */
	cv::BackgroundSubtractorMOG2 bgsub;
	
	// images of the different stages
    /**
     * @brief Original frame.
     */
    cv::Mat frame;

    /**
     * @brief Foreground mask.
     */
    cv::Mat fore;

    /**
     * @brief Background image.
     */
    cv::Mat back;

    /**
     * @brief Contours after erosion and dilation.
     */
    cv::Mat cont;
	
public:
    BackgroundSubtractor();
	BackgroundSubtractor(int hist, int varThresh, bool bShadowDet);
	
	// Get foreground, background and contours functions
    void NewFrame(cv::Mat img);
    void Denoise();
	cv::Mat Foreground();
	cv::Mat Background();
	cv::Mat Contours();
};
#endif
