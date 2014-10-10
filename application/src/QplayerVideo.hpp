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

#include "QitemVideo.hpp"

#ifndef INC_DRAWABLE
#define INC_DRAWABLE
#include "Drawables/drawable.hpp"
#endif

#ifndef INC_PLAYER
#define INC_PLAYER
#include "player.hpp"
#endif

#define PLAYER_VID 0
#define PLAYER_EV  1
#define PLAYER_FRAME 2

namespace Ui {
class VideoPlayer;
}

/**
 * @brief The VideoPlayer class
 */
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
    void rewindOrPause();
    bool refresh();
    bool stepBack();
    bool stepForward();
    void goTo(double nthFrame);
    void loadVid(PlayerPtr nextVid, int playerT, QTreeWidgetItem *item);
    void unload();
    void unload(PlayerPtr toUnload);
    bool isloaded();
    int getPlayerType();
    void setPlayMode(int mode);

    /// \brief Print the current frame with any of the system configured
    ///printers.
    void print();

    void showStillImage(const cv::Mat& image);

    PlayerPtr getCurrentPlayer();
    FramePtr getCurrentFrameRef();
    QTreeWidgetItem* getCurrentItem();
private:
    /**
     * @brief ui
     */
    Ui::VideoPlayer *ui;
    /**
     * @brief currentPlayer
     */
    PlayerPtr currentPlayer;
    /**
     * @brief _qimage
     */
    QImage _qimage;
    /**
     * @brief _tmp
     */
    cv::Mat _tmp;
    /**
     * @brief frame
     */
    cv::Mat frame;
    /**
     * @brief Playing or not
     */
    bool isplaying;
    /**
     * @brief Time interval between frames
     */
    double frameInt;
    /**
     * @brief Frames per second
     */
    double FPS;
    /**
     * @brief timer
     */
    QTimer timer;
    /**
     * @brief speed
     */
    float speed;
    /**
     * @brief playerType
     */
    int playerType;
    /**
     * @brief dir
     */
    bool dir;
    /**
     * @brief drawer
     */
    Drawable *drawer;
    /**
     * @brief Qitem
     */
    QTreeWidgetItem* Qitem;

private slots:
    void showImage(const cv::Mat& image);
    void paintEvent(QPaintEvent* /*event*/);

    int x_origin();
    int y_origin();

    void on_posSlider_sliderPressed();
    void on_posSlider_sliderReleased();
    void on_posSlider_sliderMoved(int position);
    void on_speedSlider_sliderMoved(int position);

    void on_stepbackButton_clicked();
    void on_stepforwardButton_clicked();

    void updateFrameNumber();
    void updateSliderPos();

    void setControlsEnabled(bool status);

    cv::Point qtPt_To_cvPt(QPoint in);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
};

#endif // VIDEOPLAYER_H
