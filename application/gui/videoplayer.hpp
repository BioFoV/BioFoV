#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include <QLabel>

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

class VideoPlayer : public QLabel
{
    Q_OBJECT

public:
    VideoPlayer(QWidget *parent = 0);
    ~VideoPlayer();

public slots:
    void play();
    void pause();
    void playOrPause();
    void step();
    void goTo(int nthFrame);
    void loadVid(Video* nextVid);

private:
    Ui::VideoPlayer *vp;
    Video* currentVid;
};

#endif // VIDEOPLAYER_H
