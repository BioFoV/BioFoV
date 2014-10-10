#include "QitemVideo.hpp"

/*******************************************************************************
 * Constructors
 ******************************************************************************/
/**
 * @brief VideoItem::VideoItem
 * @param parent
 */
VideoItem::VideoItem(QTreeWidget *parent) :
    PlayerItem(parent)
{

}

/**
 * @brief VideoItem::VideoItem
 * @param filename
 * @param parent
 */
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
/**
 * @brief VideoItem::getVideo
 * @return
 */
VideoPtr VideoItem::getVideo(){
    return vid;
}

/**
 * @brief VideoItem::setPlayer
 * @param inPlayer
 * @return
 */
bool VideoItem::setPlayer(PlayerPtr inPlayer){
    vid = qSharedPointerDynamicCast<Video>(inPlayer);
    if (vid.isNull())
        return false;
    return true;
}

/**
 * @brief VideoItem::getPlayer
 * @return
 */
PlayerPtr VideoItem::getPlayer(){
    return qSharedPointerDynamicCast<Player>(vid);
}
