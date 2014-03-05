#include "drawheight.hpp"

DrawHeight::DrawHeight() {
    npoints = -1;
    calculated = false;
}

DrawHeight::~DrawHeight() {

}

void DrawHeight::press(cv::Point){

}

void DrawHeight::release(cv::Point pi2){
    if (isDone())
        return;
    npoints ++;
    points[npoints] = pi2;

    if (isDone() && !isCalculated()){
        calcUndistort();
        values.push_back(TStrDoublePair("Referential",referential));
        values.push_back(TStrDoublePair("Height",height));
        values.push_back(TStrDoublePair("Ratio",ratio));
    }
}

void DrawHeight::draw(cv::Mat& frame){
    int largest = int(frame.rows<frame.cols?frame.rows:frame.cols);
    int rad = CIRCLE_RATIO * largest;
    int thick = LINE_RATIO * largest;

    if(!isVisible())
        return;

    switch (npoints) {
    case 4: // height point
        cv::circle(frame, points[4], rad, cv::Scalar( 0, 255, 255), -1, CV_AA, 0);
    case 3: // last rectangle point
        cv::line(frame, points[3], points[1], cv::Scalar( 0, 255, 0), thick, CV_AA);
        cv::circle(frame, points[3], rad, cv::Scalar( 0, 0, 255), -1, CV_AA, 0);
        cv::line(frame, points[3], points[2], cv::Scalar( 0, 255, 0), thick, CV_AA);
    case 2: // 3rd point
        cv::circle(frame, points[2], rad, cv::Scalar( 0, 0, 255), -1, CV_AA, 0);
        cv::line(frame, points[2], points[0], cv::Scalar( 0, 255, 0), thick, CV_AA);
    case 1: // 2nd point
        cv::circle(frame, points[1], rad, cv::Scalar( 0, 0, 255), -1, CV_AA, 0);
        cv::line(frame, points[1], points[0], cv::Scalar( 255, 0, 0), thick, CV_AA);
    case 0: // 1st point
        cv::circle(frame, points[0], rad, cv::Scalar( 0, 0, 255), -1, CV_AA, 0);
    default:
        break;
    }

    if (isDone()){
        undistort(frame);
    }
}

void DrawHeight::move(cv::Point /*point - unused*/){

}

bool DrawHeight::isCalculated(){
    return calculated;
}

void DrawHeight::calcUndistort(){
    // average the position of the points to get a good undistortion without the
    //image getting out of the frame.
    double c1 = (points[0].x + points[2].x)/2;
    double c2 = (points[1].x + points[3].x)/2;
    double r1 = (points[0].y + points[1].y)/2;
    double r2 = (points[2].y + points[3].y)/2;
    cv::Point2f ref[4];
    ref[0] = cv::Point2f(c1, r1);
    ref[1] = cv::Point2f(c2, r1);
    ref[2] = cv::Point2f(c1, r2);
    ref[3] = cv::Point2f(c2, r2);

    persptransf = cv::getPerspectiveTransform(points, ref);

    std::vector<cv::Point2f> a;
    std::vector<cv::Point2f> b;
    for (int i=0; i<=4; i++){
        a.push_back(points[i]);
        b.push_back(points[i]);
    }

    cv::perspectiveTransform(a, b, persptransf);

    c1 = (b.at(0).x + b.at(2).x)/2;
    c2 = (b.at(1).x + b.at(3).x)/2;
    r1 = (b.at(0).y + b.at(1).y)/2;
    r2 = (b.at(2).y + b.at(3).y)/2;

    referential = std::abs(double(r2)-double(r1));
    height = std::abs(b.at(4).y-r2);
    ratio = height/referential;

    calculated = true;
}

void DrawHeight::undistort(cv::Mat& frame){
    cv::Mat ftmp = frame.clone();
    cv::warpPerspective(ftmp, // input image
                        frame, // output image
                        persptransf, // transformation
                        cv::Size(frame.cols, frame.rows)); // size of the output
                                                           //image
}

bool DrawHeight::isDone(){
    return (npoints >= 4);
}

std::string DrawHeight::getDescription(){
    return std::string("Height");
}
