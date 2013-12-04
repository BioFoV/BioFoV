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
    explicit VideoPlayer(QWidget *parent = 0);
    ~VideoPlayer();

public slots:
    void play();
    void pause();
    void playOrPause();
    bool stepBack();
    bool stepForward();
    void goTo(double nthFrame);
    void loadVid(std::string filename);
    void loadVid(Video* nextVid);
    void unload();

private:
    Ui::VideoPlayer *ui;
    Video* currentVid;
    QImage _qimage;
    cv::Mat _tmp;
    bool isplaying; // playing or not
    double frameInt; // interval between frames
    double FPS; // frames per second
    QTimer timer;
    float speed;

private slots:
    void showImage(const cv::Mat& image);
    void paintEvent(QPaintEvent* /*event*/);
    void on_posSlider_sliderPressed();
    void on_posSlider_sliderReleased();
    void on_posSlider_sliderMoved(int position);
//    void on_posSlider_valueChanged(int value);
    void on_speedSlider_sliderMoved(int position);
};

#endif // VIDEOPLAYER_H
