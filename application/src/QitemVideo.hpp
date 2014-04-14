#ifndef VIDEOITEM_HPP
#define VIDEOITEM_HPP

#include <QTreeWidgetItem>
#include <QDir>

#ifndef INC_VIDEO
#define INC_VIDEO
#include "Video/Video.hpp"
#endif

#define TAG_VIDEO "Video"

typedef QSharedPointer<Video> VideoPtr;

class VideoItem : public QTreeWidgetItem
{
public:
    // Constructors
    explicit VideoItem(QTreeWidget *parent = 0);
    VideoItem(QString filename, QTreeWidget *parent = 0);

    // Functions
    VideoPtr getVideo();

private:
    VideoPtr vid;
};

#endif // VIDEOITEM_HPP
