#ifndef QTREEVIDEOS_HPP
#define QTREEVIDEOS_HPP

#include <QTreeWidget>

#ifndef INC_VIDEOITEM
#define INC_VIDEOITEM
#include "QitemVideo.hpp"
#endif

#include "QplayerVideo.hpp"

class QtreeVideos : public QTreeWidget
{
    Q_OBJECT
public:
    explicit QtreeVideos(QWidget *parent = 0);
    
signals:
    void showMessage(QString message);
    void loadVid(Player* player, int type);
    void setPlaybackEnabled(bool value);

public slots:
    /// \brief Add video file.
    /// Add a video file dialog and import wizard.
    void on_add_video_file();
};

#endif // QTREEVIDEOS_HPP
