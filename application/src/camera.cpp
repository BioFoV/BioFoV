#include "camera.hpp"

/**
 * @brief Simple Camera constructor.
 */
Camera::Camera() : flag(0), maxIter(0)
{
    calibrated = false;
    vid = NULL;
}

/**
 * @brief Camera constructor relative to a Video.
 * @param iVid Video to which this object relates to.
 */
Camera::Camera(Video* iVid){
    calibrated = false;
    vid = iVid;
}

/**
 * @brief Camera constructor using the board dimentions and Video reference.
 * @param iVid Pointer to the Video object.
 * @param boardW Width of the board (input by the user).
 * @param boardH Height of the board (input by the user).
 */
Camera::Camera(Video* iVid, int boardW, int boardH)
{
    calibrated = false;
    vid = iVid;
    boardSize = cv::Size( boardW, boardH );
    boardTotal = boardSize.width * boardSize.height;
}

/**
 * @brief Open chessboard images and extract corner points.
 * @param filelist
 * @return
 */
int Camera::addSeveralChessboardPoints(
    const std::vector<std::string>& filelist) {

    // the points on the chessboard
    std::vector<cv::Point2f> imageCorners;
    std::vector<cv::Point3f> objectCorners;
    // 3D Scene Points:
    // Initialize the chessboard corners
    // in the chessboard reference frame
    // The corners are at 3D location (X,Y,Z)= (i,j,0)
    for (int i=0; i<boardSize.height; i++) {
        for (int j=0; j<boardSize.width; j++) {
            objectCorners.push_back(cv::Point3f(i, j, 0.0f));
        }
    }

    // 2D Image points:
    cv::Mat image; // to contain chessboard image
    int successes = 0;

    // for all viewpoints
    for (unsigned int i=0; i<filelist.size(); i++) {

        // Open the image
        image = cv::imread(filelist[i],0);

        // Get the chessboard corners
        //bool found = cv::findChessboardCorners(
        cv::findChessboardCorners(
            image, boardSize, imageCorners);

        // Get subpixel accuracy on the corners
        cv::cornerSubPix(image, imageCorners,
            cv::Size(5,5),
            cv::Size(-1,-1),
            cv::TermCriteria(cv::TermCriteria::MAX_ITER +
            cv::TermCriteria::EPS,
            30, // max number of iterations
            0.1)); // min accuracy
        //If we have a good board, add it to our data
        if (imageCorners.size() == (unsigned)boardSize.area()) {
            // Add image and scene points from one view
            addPoints(imageCorners, objectCorners);
            successes++;
        }
    }
    return successes;
}

/**
 * @brief Given an image extract corner points.
 * @param image
 * @return
 */
bool Camera::addChessboardPoints(
    const cv::Mat image) {

    cv::Mat gray_image;
    // the points on the chessboard
    std::vector<cv::Point2f> imageCorners;
    std::vector<cv::Point3f> objectCorners;

    cvtColor(image, gray_image, CV_BGR2GRAY);

    // Get the chessboard corners
    bool found = cv::findChessboardCorners(
        gray_image, boardSize, imageCorners,
        cv::CALIB_CB_ADAPTIVE_THRESH +
        cv::CALIB_CB_NORMALIZE_IMAGE +
        cv::CALIB_CB_FAST_CHECK);

    if (!found){
        return false;
    }

    // 3D Scene Points:
    // Initialize the chessboard corners
    // in the chessboard reference frame
    // The corners are at 3D location (X,Y,Z)= (i,j,0)
    for (int i=0; i<boardSize.height; i++) {
        for (int j=0; j<boardSize.width; j++) {
            objectCorners.push_back(cv::Point3f(i, j, 0.0f));
        }
    }

    // Get subpixel accuracy on the corners
    cv::cornerSubPix(gray_image, imageCorners,
        cv::Size(5,5),
        cv::Size(-1,-1),
        cv::TermCriteria(cv::TermCriteria::MAX_ITER +
        cv::TermCriteria::EPS,
        30, // max number of iterations
        0.1)); // min accuracy
    //If we have a good board, add it to our data
    if (imageCorners.size() == (unsigned)boardSize.area()) {
        // Add image and scene points from one view
        addPoints(imageCorners, objectCorners);
        return true;
    } else {
        return false;
    }
}

/**
 * @brief Add scene points and corresponding image points.
 * @param imageCorners
 * @param objectCorners
 */
void Camera::addPoints(const std::vector<cv::Point2f> &imageCorners,
    const std::vector<cv::Point3f> &objectCorners) {

    // 2D image points from one view
    imagePoints.push_back(imageCorners);
    // corresponding 3D scene points
    objectPoints.push_back(objectCorners);
}

/**
 * @brief Calibrate the camera.
 * @param nBoards
 * @param frameStep
 * @param iterations
 * @return re-projection error.
 */
double Camera::calibrate(int nBoards, int frameStep, int iterations) {
    int successes = 0;
    int frame = 0;

    cv::Mat image;

    // Loop while successful captures equals total snapshots
    // Successful captures implies when all the enclosed corners
    //are detected from a snapshot

    while(successes < nBoards){
        //Get next image
        if (! vid->getNextFrame(image)){
            nBoards = successes;
            break;
        }

        //Skip frames if needed
        if((frame++ % frameStep) == 0){
            // If we got a good board, add it to our data
            if (addChessboardPoints(image))
                successes++;
        }
    }

    if (successes == 0){
        return -1;
    }

    maxIter = iterations;

    //Output rotations and translations
    std::vector<cv::Mat> rvecs, tvecs;

    initCamera();

    // start calibration
    reprojectionError=
        cv::calibrateCamera(objectPoints, // the 3D points
        imagePoints, // the image points
        vid->getSize(), // image size
        cameraMatrix, // output camera matrix
        distCoeffs, // output distortion matrix
        rvecs, tvecs, // Rs, Ts
        flag,
        cv::TermCriteria( cv::TermCriteria::COUNT +
        cv::TermCriteria::EPS, iterations,DBL_EPSILON ) ); // set options

    calibrated = true;
    return reprojectionError;
}

/**
 * @brief Remove distortion in an image (after calibration).
 * @param image Original image.
 * @return Remaped image.
 */
cv::Mat Camera::undistort(const cv::Mat &image) {

    cv::Mat undistorted;

    cv::undistort(image, undistorted, cameraMatrix, distCoeffs,
                  cv::getOptimalNewCameraMatrix(cameraMatrix, distCoeffs,
                                                image.size(), 1));

    return undistorted;
}

/**
 * @brief Set flags for calibration public method.
 * @param flags Flags for the calibration.
 */
void Camera::set_calib_flags(int flags){
    flag = flags;
}

/**
 * @brief Writes relevant calibration data to output file.
 * @return File write succcessful or not.
 */
bool Camera::write_file(){
    QString filename = QFileDialog::getSaveFileName();

    cv::FileStorage fs(filename.toStdString(), cv::FileStorage::WRITE);
    if (!fs.isOpened()){
        return false;
    }
    QDateTime date;
    date.date();
    fs << "calibrationDate" << date.toString("dd-mm-yyyy-hh.mm").toStdString();
    fs << "video resolution" << vid->getSize();
    fs << "number of frames used" << (int) imagePoints.size();
    fs << "number of maximum iterations" << maxIter;
    fs << "reprojection error" << reprojectionError;
    fs << "camera Matrix" << cameraMatrix;
    fs << "transformations" << posCameraMatrix;
    fs << "distance Coefficients" << distCoeffs;
    fs.release();
    return true;
}

/**
 * @brief Imports a camera from a file.
 * @return Success value.
 */
bool Camera::read_file() {
    QString filename = QFileDialog::getOpenFileName();

    cv::FileStorage fs(filename.toStdString(), cv::FileStorage::READ);
    if (!fs.isOpened()){
        return false;
    }

    cv::Size inSize;
    fs["video resolution"] >> inSize;
    fs["reprojection error"] >> reprojectionError;
    fs["camera Matrix"] >> cameraMatrix;
    fs["transformations"] >> posCameraMatrix;
    fs["distance Coefficients"] >> distCoeffs;
    fs.release();

    if (inSize != vid->getSize()){
        return false;
    }

    calibrated = true;
    return true;
}

/**
 * @brief Initialize the camera matrix.
 */
void Camera::initCamera(){
    if(cameraMatrix.empty()) {
        cameraMatrix = cv::Mat::eye(3, 3, CV_64FC1);
        cameraMatrix.at<double>(0,2) = vid->getSize().width/2;
        cameraMatrix.at<double>(1,2) = vid->getSize().height/2;

        distCoeffs = cv::Mat(1, 5, CV_64FC1);
    }
    if(posCameraMatrix.empty()){
        posCameraMatrix = cv::Mat::eye(3, 3, CV_64FC1);
    }
    calibrated = true;
}

/**
 * @brief Flips the calibration horizontally.
 */
void Camera::flip_horizontal(){
    initCamera();
    cameraMatrix.col(0) *= -1.0;
}

/**
 * @brief Flips the calibration vertically.
 */
void Camera::flip_vertical(){
    initCamera();
    cameraMatrix.col(1) *= -1.0;
}

/**
 * @brief Checks if the camera is calibrated.
 * @return Calibrated or not.
 */
bool Camera::isCalibrated(){
    return calibrated;
}
