#include "videoitem.hpp"

/*******************************************************************************
 * Constructors
 ******************************************************************************/
VideoItem::VideoItem(QTreeWidget *parent) :
    QTreeWidgetItem(parent)
{

}

VideoItem::VideoItem(QString filename, QTreeWidget *parent) :
    QTreeWidgetItem(parent)
{
    vid = new Video(filename.toStdString());
    setText(0, filename);
    setText(1, TAG_VIDEO );
}

/*******************************************************************************
 * Functions
 ******************************************************************************/
Video* VideoItem::getVideo(){
    return vid;
}
