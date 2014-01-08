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

///
/// \brief The Camera class is responsible for the calibration of the camera and
/// for holding the distortion parameters.
///
class Camera
{
private:
    // input points:
    ///
    /// \brief the points in world coordinates.
    ///
    std::vector<std::vector<cv::Point3f> > objectPoints;
    ///
    /// \brief the points in image pixels.
    ///
    std::vector<std::vector<cv::Point2f> > imagePoints;
    ///
    /// \brief flag to specify how calibration is done.
    ///
    int flag;
    ///
    /// \brief used in image undistortion.
    ///
    cv::Mat map1,map2;
    ///
    /// \brief maximum number of iterations.
    ///
    int maxIter;
    ///
    /// \brief the camera matrix itself.
    ///
    cv::Mat cameraMatrix;
    ///
    /// \brief distortion coeficients.
    ///
    cv::Mat distCoeffs;
    ///
    /// \brief estimated error introduced by the reprojection.
    ///
    double reprojectionError;
    ///
    /// \brief size of the chessboard pattern (number of inner corners).
    /// This variable is a cv::Size, not an int or an array.
    ///
    cv::Size boardSize;
    ///
    /// \brief total number of boards detected.
    ///
    unsigned int boardTotal;
    ///
    /// \brief Video which was or will be used to calibrate de camera.
    /// More Videos can be referenced to this camera, but none should re-call
    ///the calibration methods.
    ///
    Video* vid;

public:
    ///
    /// \brief are the undistortion coeficients initialized?
    ///
    bool mustInitUndistort;

    // Constructor
    ///
    /// \brief Simple Camera constructor.
    ///
    Camera();
    ///
    /// \brief Camera constructorr using the board dimentions and Video
    /// reference.
    /// \param iVid Pointer to the Video object.
    /// \param boardW Width of the board (input by the user).
    /// \param boardH Height of the board (input by the user).
    ///
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
