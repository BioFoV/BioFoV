#ifndef VIDEOITEM_HPP
#define VIDEOITEM_HPP

#include <QTreeWidgetItem>

#ifndef INC_VIDEO
#define INC_VIDEO
#include "../framework/Video/Video.hpp"
#endif

class VideoItem : public QTreeWidgetItem
{
public:
    // Constructors
    explicit VideoItem(QTreeWidget *parent = 0);
    VideoItem(QString filename, QTreeWidget *parent = 0);

    // Functions
    Video* getVideo();

private:
    Video *vid;
};

#endif // VIDEOITEM_HPP
