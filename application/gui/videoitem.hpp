#ifndef VIDEOITEM_HPP
#define VIDEOITEM_HPP

#include <QListWidgetItem>

#ifndef INC_VIDEO
#define INC_VIDEO
#include "../framework/Video/Video.hpp"
#endif

class VideoItem : public QListWidgetItem
{
public:
    // Constructors
    explicit VideoItem(QListWidget *parent = 0);
    VideoItem(QString filename, QListWidget *parent = 0);

    // Functions
    Video* getVideo();

private:
    Video *vid;
};

#endif // VIDEOITEM_HPP
