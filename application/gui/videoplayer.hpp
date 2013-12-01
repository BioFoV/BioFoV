#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include <QWidget>
#include <QImage>
#include <QPainter>
#include <QTimer>

#ifndef INC_EVENT
#define INC_EVENT
#include "../framework/Event/Event.hpp"
#endif

#ifndef INC_VIDEO
#define INC_VIDEO
#include "../framework/Video/Video.hpp"
#endif

namespace Ui {
class VideoPlayer;
}

class VideoPlayer : public QWidget
{
    Q_OBJECT

public:
    VideoPlayer(QWidget *parent = 0);
    ~VideoPlayer();

public slots:
    void play();
    void pause();
    void playOrPause();
    bool stepBack();
    bool stepForward();
    void goTo(int nthFrame);
    void loadVid(Video* nextVid);
    void unload();

private:
    Ui::VideoPlayer *vp;
    Video* currentVid;
    QImage _qimage;
    cv::Mat _tmp;
    bool isplaying; // playing or not
    double frameInt; // interval between frames
    double FPS; // frames per second
    QTimer timer;

private slots:
    void showImage(const cv::Mat& image);
    void paintEvent(QPaintEvent* /*event*/);
};

#endif // VIDEOPLAYER_H
