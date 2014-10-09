#ifndef VIDEOITEM_HPP
#define VIDEOITEM_HPP

#include <QTreeWidgetItem>
#include <QDir>

#ifndef INC_VIDEO
#define INC_VIDEO
#include "Video/Video.hpp"
#endif

#ifndef INC_PLAYERITEM
#define INC_PLAYERITEM
#include <QitemPlayer.hpp>
#endif

#define TAG_VIDEO "Video"

typedef QSharedPointer<Video> VideoPtr;

class VideoItem : public PlayerItem
{
public:
    // Constructors
    explicit VideoItem(QTreeWidget *parent = 0);
    VideoItem(QString filename, QTreeWidget *parent = 0);

    // Functions
    VideoPtr getVideo();

    bool setPlayer(PlayerPtr inPlayer);
    PlayerPtr getPlayer();
private:
    VideoPtr vid;
};

#endif // VIDEOITEM_HPP
