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
}

/*******************************************************************************
 * Functions
 ******************************************************************************/
Video* VideoItem::getVideo(){
    return vid;
}
