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
    /// \brief The points in world coordinates.
    std::vector<std::vector<cv::Point3f> > objectPoints;

    /// \brief The points in image pixels.
    std::vector<std::vector<cv::Point2f> > imagePoints;

    /// \brief Flag to specify how calibration is done.
    int flag;

    /// \brief Used in image undistortion.
    cv::Mat map1,map2;

    /// \brief Are the undistortion coeficients initialized?
    bool mustInitUndistort;

    /// \brief Maximum number of iterations.
    int maxIter;

    /// \brief The camera matrix itself.
    cv::Mat cameraMatrix;

    /// \brief Distortion coeficients.
    cv::Mat distCoeffs;

    /// \brief Estimated error introduced by the reprojection.
    double reprojectionError;

    /// \brief Size of the chessboard pattern (number of inner corners).
    /// This variable is a cv::Size, not an int or an array.
    cv::Size boardSize;

    /// \brief Total number of boards detected.
    unsigned int boardTotal;

    /// \brief Video which was or will be used to calibrate de camera.
    /// More Videos can be referenced to this camera, but none should re-call
    ///the calibration methods.
    Video* vid;

public:
    // Constructor
    /// \brief Simple Camera constructor.
    Camera();

    Camera(Video* iVid);

    /// \brief Camera constructor using the board dimentions and Video
    /// reference.
    /// \param iVid Pointer to the Video object.
    /// \param boardW Width of the board (input by the user).
    /// \param boardH Height of the board (input by the user).
    Camera(Video* iVid, int boardW, int boardH);

    // Functions
    /// \brief Open chessboard images and extract corner points.
    /// \param filelist
    /// \return
    int addSeveralChessboardPoints(const std::vector<std::string>& filelist);

    /// \brief Given an image extract corner points.
    /// \param image
    /// \return
    std::vector<cv::Point2f> addChessboardPoints(const cv::Mat image);

    /// \brief Add scene points and corresponding image points.
    /// \param imageCorners
    /// \param objectCorners
    void addPoints(const std::vector<cv::Point2f> &imageCorners,
        const std::vector<cv::Point3f> &objectCorners);

    /// \brief Calibrate the camera.
    /// \param nBoards
    /// \param frameStep
    /// \param iterations
    /// \return re-projection error.
    double calibrate(int nBoards, int frameStep, int iterations);

    /// \brief Remove distortion in an image (after calibration).
    /// \param Original image.
    /// \return Remaped image.
    cv::Mat remap(const cv::Mat &image);

    /// \brief Set flags for calibration public method.
    /// \param Flags for the calibration.
    void set_calib_flags(int flags);

    /// \brief Writes relevant calibration data to output file.
    /// \param Filename.
    /// \return File write succcessful or not.
    bool write_file(std::string filename);

    /// \brief Flips the calibration horizontally.
    void flip_horizontal(cv::Size size);

    /// \brief Flips the calibration vertically.
    void flip_vertical();
};

#endif // CAMERA_HPP
