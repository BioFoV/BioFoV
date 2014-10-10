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
#include <Video/Video.hpp>
#endif

#include <QDateTime>
#include <QFileDialog>

/**
 * @brief The Camera class is responsible for the calibration of the camera and
 * for holding the distortion parameters.
 */
class Camera
{
private:
    /**
     * @brief The points in world coordinates.
     */
    std::vector<std::vector<cv::Point3f> > objectPoints;

    /**
     * @brief The points in image pixels.
     */
    std::vector<std::vector<cv::Point2f> > imagePoints;

    /**
     * @brief Flag to specify how calibration is done.
     */
    int flag;

    /**
     * @brief Maximum number of iterations.
     */
    int maxIter;

    /**
     * @brief The camera matrix itself.
     */
    cv::Mat cameraMatrix;

    /**
     * @brief Matrix for simple distortions (flips).
     */
    cv::Mat posCameraMatrix;

    /**
     * @brief Distortion coeficients.
     */
    cv::Mat distCoeffs;

    /**
     * @brief Estimated error introduced by the reprojection.
     */
    double reprojectionError;

    /**
     * @brief Size of the chessboard pattern (number of inner corners).
     * This variable is a cv::Size, not an int or an array.
     */
    cv::Size boardSize;

    /**
     * @brief Total number of boards detected.
     */
    unsigned int boardTotal;

    /**
     * @brief Video which was or will be used to calibrate de camera.
     * More Videos can be referenced to this camera, but none should re-call
     * the calibration methods.
     */
    Video* vid;

    /**
     * @brief Is calibrated.
     */
    bool calibrated;

    void initCamera();

public:
    Camera();
    Camera(Video* iVid);
    Camera(Video* iVid, int boardW, int boardH);

    int addSeveralChessboardPoints(const std::vector<std::string>& filelist);
    bool addChessboardPoints(const cv::Mat image);
    void addPoints(const std::vector<cv::Point2f> &imageCorners,
        const std::vector<cv::Point3f> &objectCorners);
    double calibrate(int nBoards, int frameStep, int iterations);
    bool isCalibrated();
    cv::Mat undistort(const cv::Mat &image);
    void set_calib_flags(int flags);
    bool write_file();
    bool read_file();
    void flip_horizontal();
    void flip_vertical();
};

#endif // CAMERA_HPP
