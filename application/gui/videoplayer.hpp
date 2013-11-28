#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include <QLabel>

namespace Ui {
class VideoPlayer;
}

class VideoPlayer : public QLabel
{
    Q_OBJECT

public:
    VideoPlayer(QWidget *parent = 0);
    ~VideoPlayer();

private slots:
    void play();
    void pause();
    void playOrPause();
    void step();
    void goTo(int nthFrame);

private:
    Ui::VideoPlayer *vp;

};

#endif // VIDEOPLAYER_H
