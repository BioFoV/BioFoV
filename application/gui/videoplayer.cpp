#include "videoplayer.hpp"
#include "ui_videoplayer.h"

/*******************************************************************************
 * Constructors
 ******************************************************************************/
VideoPlayer::VideoPlayer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VideoPlayer)
{
    ui->setupUi(this);
    connect(&timer, SIGNAL(timeout()), this, SLOT(play()));
}

/*******************************************************************************
 * Destructor
 ******************************************************************************/
VideoPlayer::~VideoPlayer(){
    delete ui;
}

/*******************************************************************************
 * Actions
 ******************************************************************************/
void VideoPlayer::play(){
    if(!stepForward()){
        timer.stop();
    }
}

void VideoPlayer::pause(){
    isplaying = false;
    timer.stop();
}

void VideoPlayer::playOrPause(){
    if(!isplaying){
        isplaying = true;
        //future = QtConcurrent::run(this,&VideoPlayer::play);
        timer.start();
    } else {
        isplaying = false;
        timer.stop();
    }
}

bool VideoPlayer::stepBack(){
    cv::Mat _tmp2;
    if(currentVid->getPrevFrame(_tmp2)) {
        showImage(_tmp2);
        return true;
    } else {
        qDebug("could not get frame");
        return false;
    }
}

bool VideoPlayer::stepForward(){
    cv::Mat _tmp2;
    // Check if there is a next frame
    if(currentVid->get_frame(_tmp2)) {
        showImage(_tmp2);
        return true;
    } else {
        qDebug("could not get frame");
        return false;
    }
}

void VideoPlayer::goTo(int nthFrame){

}

void VideoPlayer::loadVid(Video* nextVid){
    currentVid = nextVid;
    stepForward();
    FPS = currentVid->getFPS();
    frameInt = currentVid->getFrameInt();
    qDebug("loaded video to player");
    qDebug("FPS = %f",FPS);
    qDebug("Frame interval = %f",frameInt);
    timer.setInterval(frameInt);

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
