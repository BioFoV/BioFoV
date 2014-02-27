#ifndef QTREEVIDEOS_HPP
#define QTREEVIDEOS_HPP

#include <QTreeWidget>

#ifndef INC_VIDEOITEM
#define INC_VIDEOITEM
#include "QitemVideo.hpp"
#endif

#ifndef INC_EVENTITEM
#define INC_EVENTITEM
#include "QitemEvent.hpp"
#endif

#ifndef INC_SPLITDIALOG
#define INC_SPLITDIALOG
#include "QdialogSplit.hpp"
#endif

#ifndef INC_DIALOGSETTINGS
#define INC_DIALOGSETTINGS
#include "QdialogSettings.hpp"
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
    QdialogSettings* getSettings();
    void progressChanged(uint);
    void startProgress(uint, uint);
    void resetProgress();
    void removePlayer(Player*);

public slots:
    /// \brief Add video file.
    /// Add a video file dialog and import wizard.
    void on_add_video_file();

    /// \brief Auto detect events in video.
    /// For each video in the video list split them into events accordingly with the
    ///given parameters in the split window that is used.
    void on_auto_detect_events();

    /// \brief Remove video file from project.
    void on_remove_from_project();

    /// \brief Delete all selected Events.
    void on_delete_event();

private:
    uint nEvent;
};

#endif // QTREEVIDEOS_HPP
