#include "camera.hpp"

Camera::Camera() : flag(0), mustInitUndistort(true), maxIter(0)
{
    vid = NULL;
}

Camera::Camera(Video* iVid, int boardW, int boardH)
{
    vid = iVid;
    boardSize = cv::Size( boardW, boardH );
    boardTotal = boardSize.width * boardSize.height;
}

// Open chessboard images and extract corner points
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
        if (imageCorners.size() == boardSize.area()) {
            // Add image and scene points from one view
            addPoints(imageCorners, objectCorners);
            successes++;
        }
    }
    return successes;
}

// Given an image extract corner points
std::vector<cv::Point2f> Camera::addChessboardPoints(
    const cv::Mat image) {

    cv::Mat gray_image;
    // the points on the chessboard
    std::vector<cv::Point2f> imageCorners;
    std::vector<cv::Point3f> objectCorners;

    // Get the chessboard corners
    bool found = cv::findChessboardCorners(
        image, boardSize, imageCorners);

    if (!found){
        return imageCorners;
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

    cvtColor(image, gray_image, CV_BGR2GRAY);
    // Get subpixel accuracy on the corners
    cv::cornerSubPix(gray_image, imageCorners,
        cv::Size(5,5),
        cv::Size(-1,-1),
        cv::TermCriteria(cv::TermCriteria::MAX_ITER +
        cv::TermCriteria::EPS,
        30, // max number of iterations
        0.1)); // min accuracy
    //If we have a good board, add it to our data
    if (imageCorners.size() == boardSize.area()) {
        // Add image and scene points from one view
        addPoints(imageCorners, objectCorners);
    }

    return imageCorners;
}

// Add scene points and corresponding image points
void Camera::addPoints(const std::vector<cv::Point2f> &imageCorners,
    const std::vector<cv::Point3f> &objectCorners) {

    // 2D image points from one view
    imagePoints.push_back(imageCorners);
    // corresponding 3D scene points
    objectPoints.push_back(objectCorners);
}

// Calibrate the camera
// returns the re-projection error
double Camera::calibrate(int nBoards, int frameStep, int iterations) {
    std::vector<cv::Point2f> corners;
    int successes = 0;
    int frame = 0;

    cv::Mat image;

    // Loop while successful captures equals total snapshots
    // Successful captures implies when all the enclosed corners
    //are detected from a snapshot
    while(successes < nBoards){
        //Get next image
        if (! vid->getFrame(image)){
            nBoards = successes;
            break;
        }

        //Skip frames if needed
        if((frame++ % frameStep) == 0){
            corners = addChessboardPoints(image);

            // If we got a good board, add it to our data
            if( corners.size() == boardTotal){
                successes++;
            }
        }
    }

    if (successes == 0){
        return -1;
    }

    set_calib_flags(CV_CALIB_FIX_PRINCIPAL_POINT |
                    CV_CALIB_FIX_K3);

    // undistorter must be reinitialized
    mustInitUndistort= true;
    maxIter = iterations;

    //Output rotations and translations
    std::vector<cv::Mat> rvecs, tvecs;

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

    return reprojectionError;
}

// remove distortion in an image (after calibration)
cv::Mat Camera::remap(const cv::Mat &image) {

    cv::Mat undistorted;

    if (mustInitUndistort) { // called once per calibration
        cv::initUndistortRectifyMap(
            cameraMatrix, // computed camera matrix
            distCoeffs,   // computed distortion matrix
            cv::Mat(),    // optional rectification (none)
            cv::Mat(),    // camera matrix to generate undistorted
            image.size(), // size of undistorted
            CV_32FC1,     // type of output map
            map1, map2);  // the x and y mapping functions
        mustInitUndistort=false;
    }

    // Apply mapping functions
    cv::remap(image, undistorted, map1, map2,
        cv::INTER_LINEAR); // interpolation type

    return undistorted;
}

// Set flags for calibration public method
void Camera::set_calib_flags(int flags){
    flag = flags;
}

// Writes relevant calibration data to output file
bool Camera::write_file(std::string filename){
    cv::FileStorage fs(filename, cv::FileStorage::WRITE);
    if (!fs.isOpened()){
        return false;
    }
    time_t rawtime; time(&rawtime);
    fs << "number of frames used" << (int) imagePoints.size();
    fs << "number of maximum iterations" << maxIter;
    fs << "reprojection error" << reprojectionError;
    fs << "calibrationDate" << asctime(localtime(&rawtime));
    fs << "camera Matrix" << cameraMatrix;
    fs << "distance Coefficients" << distCoeffs;
    fs.release();
    return true;
}
