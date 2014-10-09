#include "QitemVideo.hpp"

/*******************************************************************************
 * Constructors
 ******************************************************************************/
VideoItem::VideoItem(QTreeWidget *parent) :
    PlayerItem(parent)
{

}

VideoItem::VideoItem(QString filename, QTreeWidget *parent) :
    PlayerItem(parent)
{
    vid = VideoPtr(new Video(filename.toStdString()));
    setText(0, filename.split(QDir::separator()).last());
    setText(1, TAG_VIDEO );
}

/*******************************************************************************
 * Functions
 ******************************************************************************/
VideoPtr VideoItem::getVideo(){
    return vid;
}

bool VideoItem::setPlayer(PlayerPtr inPlayer){
    vid = qSharedPointerDynamicCast<Video>(inPlayer);
    if (vid.isNull())
        return false;
    return true;
}

PlayerPtr VideoItem::getPlayer(){
    return qSharedPointerDynamicCast<Player>(vid);
}
