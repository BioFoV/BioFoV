#include "QplayerVideo.hpp"
#include "ui_videoplayer.h"

/*******************************************************************************
 * Constructors
 ******************************************************************************/
/**
 * @brief VideoPlayer::VideoPlayer
 * @param parent
 */
VideoPlayer::VideoPlayer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VideoPlayer)
{
    ui->setupUi(this);
    connect(&timer, SIGNAL(timeout()), this, SLOT(play()));

    setControlsEnabled(false);
    connect(ui->playButton, SIGNAL(clicked()),
            this, SLOT(playOrPause()));
    connect(ui->rewindButton, SIGNAL(clicked()),
            this, SLOT(rewindOrPause()));
    currentPlayer.clear();
}

/*******************************************************************************
 * Destructor
 ******************************************************************************/
/**
 * @brief VideoPlayer::~VideoPlayer
 */
VideoPlayer::~VideoPlayer(){
    delete ui;
}

/*******************************************************************************
 * Actions
 ******************************************************************************/
/**
 * @brief VideoPlayer::play
 */
void VideoPlayer::play(){
    if (dir){
        if(!stepForward()){
            timer.stop();
        }
    }
    else {
        if(!stepBack()){
            timer.stop();
        }
    }
}

/**
 * @brief VideoPlayer::pause
 */
void VideoPlayer::pause(){
    isplaying = false;
    timer.stop();
}

/**
 * @brief VideoPlayer::playOrPause
 */
void VideoPlayer::playOrPause(){
    if (!isloaded())
        return;
    if(!isplaying || dir != true){
        isplaying = true;
        dir = true;
        timer.start();
    } else {
        isplaying = false;
        timer.stop();
    }
}

/**
 * @brief VideoPlayer::rewindOrPause
 */
void VideoPlayer::rewindOrPause() {
    if (!isloaded())
        return;
    if(!isplaying || dir != false){
        isplaying = true;
        dir = false;
        timer.start();
    } else {
        isplaying = false;
        timer.stop();
    }
}

/**
 * @brief VideoPlayer::refresh
 * @return
 */
bool VideoPlayer::refresh(){
    if (!isloaded())
        return false;
    if(currentPlayer->getFrame(frame)) {
        showImage(frame);
        return true;
    } else {
        qDebug("could not get frame");
        pause();
        return false;
    }
}

/**
 * @brief VideoPlayer::stepBack
 * @return
 */
bool VideoPlayer::stepBack(){
    if (!isloaded())
        return false;
    if(currentPlayer->getPrevFrame(frame)) {
        showImage(frame);
        updateFrameNumber();
        updateSliderPos();
        return true;
    } else {
        qDebug("could not get frame");
        pause();
        return false;
    }
}

/**
 * @brief VideoPlayer::stepForward
 * @return
 */
bool VideoPlayer::stepForward(){
    if (!isloaded())
        return false;
    // Check if there is a next frame
    if(currentPlayer->getNextFrame(frame)) {
        showImage(frame);
        updateFrameNumber();
        updateSliderPos();
        return true;
    } else {
        qDebug("could not get frame");
        pause();
        return false;
    }
}

/**
 * @brief VideoPlayer::goTo
 * @param nthFrame
 */
void VideoPlayer::goTo(double nthFrame){
    PlayerPtr tmpPlayer = getCurrentPlayer();
    if (tmpPlayer.isNull()){
        return;
    }
    tmpPlayer->setFramePos(nthFrame);
    stepForward();
}

/*******************************************************************************
 * Video loading functions
 ******************************************************************************/
/**
 * @brief VideoPlayer::loadVid
 * @param nextVid
 * @param playerT
 * @param item
 */
void VideoPlayer::loadVid(PlayerPtr nextVid, int playerT, QTreeWidgetItem* item){
    pause();
    unload();
    currentPlayer = nextVid;
    playerType = playerT;

    Qitem = item;

    ui->posSlider->setValue(nextVid->getFramePos());
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
    setControlsEnabled(true);
    refresh();
}

/**
 * @brief VideoPlayer::unload
 */
void VideoPlayer::unload(){
    currentPlayer.clear();
    Qitem = NULL;
    qDebug("unloaded video to player");
}

/**
 * @brief VideoPlayer::unload
 * @param toUnload
 */
void VideoPlayer::unload(PlayerPtr toUnload){
    if(getCurrentPlayer() == toUnload){
        pause();
        unload();
    }
}

/**
 * @brief VideoPlayer::isloaded
 * @return
 */
bool VideoPlayer::isloaded(){
    return !(currentPlayer == NULL);
}

/*******************************************************************************
 * Image show
 ******************************************************************************/
/**
 * @brief VideoPlayer::showImage
 * @param image
 */
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

/**
 * @brief VideoPlayer::paintEvent
 */
void VideoPlayer::paintEvent(QPaintEvent* /*event*/) {
    // Display the image
    QPainter painter(this);
    _qimage = QImage(_tmp.data, _tmp.cols, _tmp.rows, _tmp.cols*3, QImage::Format_RGB888);
    int x0 = 0;
    int y0 = 0;

    if (!_qimage.isNull()){
        _qimage = _qimage.scaled(ui->player->size().width(),ui->player->size().height(),Qt::KeepAspectRatio);

        x0 = x_origin();
        y0 = y_origin();
        painter.drawImage(QPoint(x0,y0), _qimage);
    }
    painter.end();
}

/**
 * @brief VideoPlayer::x_origin
 * @return
 */
int VideoPlayer::x_origin(){
    if(_qimage.width() < ui->player->size().width()){
        return (ui->player->width() - _qimage.width())/2;
    }
    return 0;
}

/**
 * @brief VideoPlayer::y_origin
 * @return
 */
int VideoPlayer::y_origin(){
    if (_qimage.height() < ui->player->size().height()){
        return (ui->player->height() - _qimage.height())/2;
    }
    return 0;
}

/*******************************************************************************
 * Slider functions
 ******************************************************************************/
/**
 * @brief VideoPlayer::on_posSlider_sliderPressed
 */
void VideoPlayer::on_posSlider_sliderPressed()
{
    if(isplaying)
        timer.stop();
}

/**
 * @brief VideoPlayer::on_posSlider_sliderReleased
 */
void VideoPlayer::on_posSlider_sliderReleased()
{
    if(isplaying)
        timer.start();
}

/**
 * @brief VideoPlayer::on_posSlider_sliderMoved
 * @param position
 */
void VideoPlayer::on_posSlider_sliderMoved(int position)
{
    goTo(position);
}

/**
 * @brief VideoPlayer::on_speedSlider_sliderMoved
 * @param position
 */
void VideoPlayer::on_speedSlider_sliderMoved(int position)
{
    speed = position/10.0;
    timer.setInterval(frameInt/speed);
}

/**
 * @brief VideoPlayer::updateFrameNumber
 */
void VideoPlayer::updateFrameNumber()
{
    ui->frameIndex->setText(QString("%1").arg(currentPlayer->getCurrentFrameNumber()));
}

/**
 * @brief VideoPlayer::updateSliderPos
 */
void VideoPlayer::updateSliderPos()
{
    ui->posSlider->setValue(currentPlayer->getFramePos()-1);
}

/*******************************************************************************
 * Player type
 ******************************************************************************/
/**
 * @brief VideoPlayer::getPlayerType
 * @return
 */
int VideoPlayer::getPlayerType(){
    return playerType;
}

/**
 * @brief VideoPlayer::setPlayMode
 * @param mode
 */
void VideoPlayer::setPlayMode(int mode){
    if (playerType == PLAYER_EV){
        EventPtr tmpEvent = qSharedPointerCast<Event> (currentPlayer);
        tmpEvent->setPlaybackMode(mode);
    }
}

/*******************************************************************************
 * Mouse tracking
 ******************************************************************************/
/**
 * @brief VideoPlayer::qtPt_To_cvPt
 * @param in
 * @return
 */
cv::Point VideoPlayer::qtPt_To_cvPt(QPoint in){
    double x_cv = frame.cols;
    double y_cv = frame.rows;

    double x_qt = _qimage.width();
    double y_qt = _qimage.height();

    double x_now = in.x();
    double y_now = in.y();

    return cv::Point(x_now*x_cv/x_qt,
                     y_now*y_cv/y_qt);
}

/**
 * @brief VideoPlayer::mousePressEvent
 * @param event
 */
void VideoPlayer::mousePressEvent(QMouseEvent *event){
    QPoint ptTmp = event->pos() - QPoint(x_origin(),y_origin());
    PlayerPtr tmpPlayer = getCurrentPlayer();
    if (tmpPlayer.isNull()){
        return;
    }
    tmpPlayer->mousePressEvent(qtPt_To_cvPt(ptTmp));
    tmpPlayer->getFrame(frame);
    showImage(frame);
}

/**
 * @brief VideoPlayer::mouseReleaseEvent
 * @param event
 */
void VideoPlayer::mouseReleaseEvent(QMouseEvent *event){
    QPoint ptTmp = event->pos() - QPoint(x_origin(),y_origin());
    PlayerPtr tmpPlayer = getCurrentPlayer();
    if (tmpPlayer.isNull()){
        return;
    }
    tmpPlayer->mouseReleaseEvent(qtPt_To_cvPt(ptTmp));
    tmpPlayer->getFrame(frame);
    showImage(frame);
}

/**
 * @brief VideoPlayer::mouseMoveEvent
 * @param event
 */
void VideoPlayer::mouseMoveEvent(QMouseEvent *event){
    QPoint ptTmp = event->pos() - QPoint(x_origin(),y_origin());
    PlayerPtr tmpPlayer = getCurrentPlayer();
    if (tmpPlayer.isNull()){
        return;
    }
    tmpPlayer->mouseMoveEvent(qtPt_To_cvPt(ptTmp));
    tmpPlayer->getFrame(frame);
    showImage(frame);
}

/**
 * @brief VideoPlayer::print
 */
void VideoPlayer::print(){
    QPrinter printer;
    QPrintDialog *dlg = new QPrintDialog(&printer,0);
    if(dlg->exec() == QDialog::Accepted) {
        QPainter printerPainter(&printer);
        QImage _qimage(_tmp.data, _tmp.cols, _tmp.rows,
                       _tmp.cols*3, QImage::Format_RGB888);
        _qimage = _qimage.scaled(QSize(printer.width(),printer.height()),Qt::KeepAspectRatio);
        printerPainter.drawImage(QPoint(0,0), _qimage);
        printerPainter.end();
    }
    delete dlg;
}

/**
 * @brief VideoPlayer::showStillImage
 * @param image
 */
void VideoPlayer::showStillImage(const cv::Mat& image){
    setControlsEnabled(false);
    showImage(image);
}

/**
 * @brief VideoPlayer::setControlsEnabled
 * @param status
 */
void VideoPlayer::setControlsEnabled(bool status){
    ui->controls->setEnabled(status);
    ui->posSlider->setEnabled(status);
    ui->speedSlider->setEnabled(status);
}

/**
 * @brief VideoPlayer::getCurrentPlayer
 * @return
 */
PlayerPtr VideoPlayer::getCurrentPlayer(){
    return currentPlayer;
}

/**
 * @brief VideoPlayer::getCurrentItem
 * @return
 */
QTreeWidgetItem* VideoPlayer::getCurrentItem(){
    return Qitem;
}

/**
 * @brief VideoPlayer::getCurrentFrameRef
 * @return
 */
FramePtr VideoPlayer::getCurrentFrameRef(){
    return getCurrentPlayer()->getCurrentFrameRef();
}

/**
 * @brief VideoPlayer::on_stepbackButton_clicked
 */
void VideoPlayer::on_stepbackButton_clicked()
{
    pause();
    stepBack();
}

/**
 * @brief VideoPlayer::on_stepforwardButton_clicked
 */
void VideoPlayer::on_stepforwardButton_clicked()
{
    pause();
    stepForward();
}
