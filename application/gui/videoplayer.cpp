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
    ui->posSlider->setValue(currentPlayer->getFramePos());
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
    if(currentPlayer->getPrevFrame(_tmp2)) {
        showImage(_tmp2);
        return true;
    } else {
        qDebug("could not get frame");
        pause();
        return false;
    }
}

bool VideoPlayer::stepForward(){
    cv::Mat _tmp2;
    // Check if there is a next frame
    if(currentPlayer->getFrame(_tmp2)) {
        showImage(_tmp2);
        return true;
    } else {
        qDebug("could not get frame");
        pause();
        return false;
    }
}

void VideoPlayer::goTo(double nthFrame){
    currentPlayer->setFramePos(nthFrame);
    stepForward();
}

/*******************************************************************************
 * Video loading functions
 ******************************************************************************/
void VideoPlayer::loadVid(std::string filename){
    Video * vid = new Video(filename);
    pause();
    unload();
    loadVid(vid, PLAYER_VID);
}

void VideoPlayer::loadVid(Player* nextVid, int playerT){
    pause();
    unload();
    currentPlayer = nextVid;
    playerType = playerT;

    nextVid->setFramePos(0);
    ui->posSlider->setValue(0);
    stepForward();
    FPS = currentPlayer->getFPS();
    frameInt = currentPlayer->getFrameInt();
    qDebug("loaded video to player");
    qDebug("FPS = %f",FPS);
    qDebug("Frame interval = %f",frameInt);
    timer.setInterval(frameInt);
    ui->posSlider->setMaximum(currentPlayer->getLengthFrames());
    qDebug("length %f", currentPlayer->getLengthTime());
    // Using 1/10th of the video as page step
    ui->posSlider->setPageStep(currentPlayer->getLengthFrames()/10);
    speed = 1;
    ui->speedSlider->setValue(speed*10);
}

void VideoPlayer::unload(){
    //delete currentVid;
    qDebug("unloaded video to player");
}

/*******************************************************************************
 * Image show
 ******************************************************************************/
void VideoPlayer::showImage(const cv::Mat& image){
    // Convert the image to the RGB888 format
    switch (image.type()) {
    case CV_8UC1:
        cv::cvtColor(image, _tmp, CV_GRAY2RGB);
        break;
    case CV_8UC3:
        cv::cvtColor(image, _tmp, CV_BGR2RGB);
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
    _qimage = QImage(_tmp.data, _tmp.cols, _tmp.rows, _tmp.cols*3, QImage::Format_RGB888);
    if (!_qimage.isNull()){
        _qimage = _qimage.scaled(ui->player->size().width(),ui->player->size().height(),Qt::KeepAspectRatio);
        painter.drawImage(QPoint(0,0), _qimage);
    }
    painter.end();
}

/*******************************************************************************
 * Slider functions
 ******************************************************************************/
void VideoPlayer::on_posSlider_sliderPressed()
{
    if(isplaying)
        timer.stop();
}

void VideoPlayer::on_posSlider_sliderReleased()
{
    if(isplaying)
        timer.start();
}

void VideoPlayer::on_posSlider_sliderMoved(int position)
{
    goTo(position);
}
/* Function slows down video playback
 *
void VideoPlayer::on_posSlider_valueChanged(int value)
{
    currentVid->setFramePos(value);
}
*/

void VideoPlayer::on_speedSlider_sliderMoved(int position)
{
    speed = position/10.0;
    timer.setInterval(frameInt/speed);
}

/*******************************************************************************
 * Playback button hadlers
 ******************************************************************************/
void VideoPlayer::on_rewindButton_clicked()
{
    stepBack();
}

void VideoPlayer::on_playButton_clicked()
{
    playOrPause();
}

void VideoPlayer::on_stepButton_clicked()
{
    stepForward();
}

/*******************************************************************************
 * Player type
 ******************************************************************************/
int VideoPlayer::getPlayerType(){
    return playerType;
}

void VideoPlayer::setPlayMode(int mode){
    if (playerType == PLAYER_EV)
        ((Event*)currentPlayer)->setPlaybackMode(mode);
}
