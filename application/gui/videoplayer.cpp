#include "videoplayer.hpp"

/*******************************************************************************
 * Constructors
 ******************************************************************************/
VideoPlayer::VideoPlayer(QWidget *parent) :
    QWidget(parent)
{
}

/*******************************************************************************
 * Destructor
 ******************************************************************************/
VideoPlayer::~VideoPlayer(){

}

/*******************************************************************************
 * Actions
 ******************************************************************************/
void VideoPlayer::play(){

}

void VideoPlayer::pause(){

}

void VideoPlayer::playOrPause(){

}

void VideoPlayer::step(){
    cv::Mat _tmp2;
    // Check if there is a next frame
    if(currentVid->get_frame(_tmp2)) {
        showImage(_tmp2);
    } else {
        qDebug("could not get frame");
    }
}

void VideoPlayer::goTo(int nthFrame){

}

void VideoPlayer::loadVid(Video* nextVid){
    currentVid = nextVid;
    step();
    qDebug("loaded video to player");
}

void VideoPlayer::unload(){
    delete currentVid;
    qDebug("unloaded video to player");
}

void VideoPlayer::showImage(const cv::Mat& image){
    // Convert the image to the RGB888 format
    switch (image.type()) {
    case CV_8UC1:
        cvtColor(image, _tmp, CV_GRAY2RGB);
        break;
    case CV_8UC3:
        cvtColor(image, _tmp, CV_BGR2RGB);
        break;
    }

    // QImage needs the data to be stored continuously in memory
    assert(_tmp.isContinuous());
    // Assign OpenCV's image buffer to the QImage. Note that the bytesPerLine parameter
    // is 3*width because each pixel has three bytes.
    _qimage = QImage(_tmp.data, _tmp.cols, _tmp.rows, _tmp.cols*3, QImage::Format_RGB888);
    //setFixedSize(image.cols, image.rows);

    repaint();
}

void VideoPlayer::paintEvent(QPaintEvent* /*event*/) {
    // Display the image
    QPainter painter(this);
    _qimage = _qimage.scaled(this->size().width(),this->size().height(),Qt::KeepAspectRatio);
    painter.drawImage(QPoint(0,0), _qimage);
    painter.end();
}
