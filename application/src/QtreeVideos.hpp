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
    void showMessage(QString);
    void loadVid(Player*, int);
    void setPlaybackEnabled(bool);
    QdialogSettings* getSettings();
    void progressChanged(uint);
    void startProgress(uint, uint);
    void resetProgress();
    void removePlayer(Player*);
    int getPlayMode();
    void setPlaybackMode(int);
    void playOrPause();

    void setSelectedText(QString);
    void setTotalFramesText(QString);
    void setTotalTimeText(QString);

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

    /// \brief Double click an item on the video/event list.
    /// \param item Pointer to the item which was double clicked.
    /// \param column Index of the clicked column (not used).
    void on_item_doubleclicked(QTreeWidgetItem* item, int column);

    /// \brief Changed selection in the video/event list.
    /// Updates the statistics for the selected events.
    void on_item_selection_changed();

    void flip_horizontally();

    void flip_vertically();
private:
    uint nEvent;
};

#endif // QTREEVIDEOS_HPP
