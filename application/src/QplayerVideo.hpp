#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include <QWidget>
#include <QImage>
#include <QPainter>
#include <QTimer>
#include <QMouseEvent>
#include <QDebug>
#include <QtPrintSupport>

// OpenCV
#ifndef OPENCV_INC
#define OPENCV_INC
#include <opencv2/opencv.hpp>
#endif

#ifndef INC_EVENT
#define INC_EVENT
#include "Event/Event.hpp"
#endif

#ifndef INC_VIDEO
#define INC_VIDEO
#include "Video/Video.hpp"
#endif

#include "Drawables/drawable.hpp"

#define PLAYER_VID 0
#define PLAYER_EV  1
#define PLAYER_FRAME 2

namespace Ui {
class VideoPlayer;
}

class VideoPlayer : public QWidget
{
    Q_OBJECT

public:
    explicit VideoPlayer(QWidget *parent = 0);
    ~VideoPlayer();

public slots:
    void play();
    void pause();
    void playOrPause();
    bool stepBack();
    bool stepForward();
    void goTo(double nthFrame);
    void loadVid(Player* nextVid, int playerT, QTreeWidgetItem *item);
    void unload();
    void unload(Player* toUnload);
    int getPlayerType();
    void setPlayMode(int mode);
    void setClickable(Drawable* draw);

    /// \brief Print the current frame with any of the system configured
    ///printers.
    void print();

    void showStillImage(const cv::Mat& image);

    Player* getCurrentPlayer();
    Frame* getCurrentFrameRef();
    QTreeWidgetItem* getCurrentItem();
private:
    Ui::VideoPlayer *ui;
    Player* currentPlayer;
    QImage _qimage;
    cv::Mat _tmp;
    cv::Mat frame;
    bool isplaying; // playing or not
    double frameInt; // interval between frames
    double FPS; // frames per second
    QTimer timer;
    float speed;
    int playerType;

    bool isClickable;
    Drawable *drawer;

    QTreeWidgetItem* Qitem;

private slots:
    void showImage(const cv::Mat& image);
    void paintEvent(QPaintEvent* /*event*/);
    void on_posSlider_sliderPressed();
    void on_posSlider_sliderReleased();
    void on_posSlider_sliderMoved(int position);
//    void on_posSlider_valueChanged(int value);
    void on_speedSlider_sliderMoved(int position);

    void setControlsEnabled(bool status);

    cv::Point qtPt_To_cvPt(QPoint in);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
};

#endif // VIDEOPLAYER_H
