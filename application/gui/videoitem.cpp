#include "videoitem.hpp"

VideoItem::VideoItem(QListWidget *parent) :
    QListWidgetItem(parent)
{

}

VideoItem::VideoItem(QString filename, QListWidget *parent) :
    QListWidgetItem(filename, parent)
{
    vid = new Video(filename.toStdString());
}

Video* VideoItem::getVideo(){
    return vid;
}
