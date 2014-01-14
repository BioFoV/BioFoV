#include "drawheight.hpp"

DrawHeight::DrawHeight() {
    npoints = -1;
}

void DrawHeight::press(cv::Point pi1){

}

bool DrawHeight::release(cv::Point pi2){
    npoints ++;
    points[npoints] = pi2;

    if (npoints < 3){
        return true;
    }
    else {
        return false;
    }
}

void DrawHeight::draw(cv::Point pi2, cv::Mat& frame){
    int largest = int(frame.rows<frame.cols?frame.rows:frame.cols);
    int rad = CIRCLE_RATIO * largest;
    int thick = LINE_RATIO * largest;

    switch (npoints) {
    case 3: // last point
        cv::line(frame, points[3], points[0], cv::Scalar( 0, 255, 0), thick, CV_AA);
        cv::circle(frame, points[3], rad, cv::Scalar( 0, 0, 255), -1, CV_AA, 0);
        cv::line(frame, points[3], points[2], cv::Scalar( 0, 255, 0), thick, CV_AA);
    case 2: // 3rd point
        cv::circle(frame, points[2], rad, cv::Scalar( 0, 0, 255), -1, CV_AA, 0);
        cv::line(frame, points[2], points[1], cv::Scalar( 0, 255, 0), thick, CV_AA);
    case 1: // 2nd point
        cv::circle(frame, points[1], rad, cv::Scalar( 0, 0, 255), -1, CV_AA, 0);
        cv::line(frame, points[1], points[0], cv::Scalar( 255, 0, 0), thick, CV_AA);
    case 0: // 1st point
        cv::circle(frame, points[0], rad, cv::Scalar( 0, 0, 255), -1, CV_AA, 0);
    default:
        break;
    }
}

///
/// \brief applies the transformation with the data previously inputed.
/// \param frame on which to apply the transformation.
///
void DrawHeight::apply(cv::Mat& frame){
    // average the position of the points to get a good undistortion without the
    //image getting out of the frame.
    int c1 = (points[0].x + points[2].x)/2;
    int c2 = (points[1].x + points[3].x)/2;
    int r1 = (points[0].y + points[1].y)/2;
    int r2 = (points[2].y + points[3].y)/2;
    cv::Point2f ref[4];
    ref[0] = cv::Point2f(c1, r1);
    ref[1] = cv::Point2f(c2, r1);
    ref[2] = cv::Point2f(c1, r2);
    ref[3] = cv::Point2f(c2, r2);

    cv::Mat persptransf = cv::getPerspectiveTransform(points,
                                                      ref);

    cv::Mat ftmp = frame.clone();
    cv::warpPerspective(ftmp, // input image
                        frame, // output image
                        persptransf, // transformation
                        cv::Size(frame.cols, frame.rows)); // size of the output
                                                           //image
}
