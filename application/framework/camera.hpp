#ifndef CAMERA_HPP
#define CAMERA_HPP

// OpenCV
#ifndef OPENCV_INC
#define OPENCV_INC
#include <opencv2/opencv.hpp>
#endif

#ifndef INC_VECTOR
#define INC_VECTOR
#include <vector>
#endif

#ifndef INC_VIDEO
#define INC_VIDEO
#include "Video/Video.hpp"
#endif

class Camera
{
private:
    // input points:
    //the points in world coordinates
    std::vector<std::vector<cv::Point3f> > objectPoints;
    //the point positions in pixels
    std::vector<std::vector<cv::Point2f> > imagePoints;
    // flag to specify how calibration is done
    int flag;
    // used in image undistortion
    cv::Mat map1,map2;
    int maxIter;
    cv::Mat cameraMatrix;
    cv::Mat distCoeffs;
    double reprojectionError;
    cv::Size boardSize;
    int boardTotal;
    Video* vid;

public:

    bool mustInitUndistort;

    // Constructor
    Camera();
    Camera(Video* iVid, int boardW, int boardH);

    // Functions
    int addSeveralChessboardPoints(const std::vector<std::string>& filelist);

    std::vector<cv::Point2f> addChessboardPoints(const cv::Mat image);

    void addPoints(const std::vector<cv::Point2f> &imageCorners,
        const std::vector<cv::Point3f> &objectCorners);

    double calibrate(int nBoards, int frameStep, int iterations);

    cv::Mat remap(const cv::Mat &image);

    void set_calib_flags(int flags);

    bool write_file(std::string filename);
};

#endif // CAMERA_HPP
