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

#ifndef INC_FRAMEITEM
#define INC_FRAMEITEM
#include "QitemFrame.hpp"
#endif

#include "QitemDrawable.hpp"

#ifndef INC_SPLITDIALOG
#define INC_SPLITDIALOG
#include "QdialogSplit.hpp"
#endif

#ifndef INC_DIALOGSETTINGS
#define INC_DIALOGSETTINGS
#include "QdialogSettings.hpp"
#endif

#include "Drawables/drawable.hpp"
#include "Drawables/drawheight.hpp"
#include "Drawables/drawwidth.hpp"
#include "Drawables/drawlength.hpp"
#include "Drawables/rectanglemask.hpp"
#include "Drawables/drawreproj.hpp"
#include "QdialogCalibration.hpp"
#include "QplayerVideo.hpp"

class QtreeVideos : public QTreeWidget
{
    Q_OBJECT
public:
    explicit QtreeVideos(QWidget *parent = 0);
    
signals:
    void showMessage(QString);
    void loadVid(PlayerPtr, int, QTreeWidgetItem*);
    void setPlaybackEnabled(bool);
    QdialogSettings* getSettings();
    void progressChanged(uint);
    void startProgress(uint, uint);
    void resetProgress();
    void removePlayer(PlayerPtr);
    int getPlayMode();
    void setPlaybackMode(int);
    void playOrPause();
    void pause();
    void refreshPlayer();

    void setSelectedText(QString);
    void setTotalFramesText(QString);
    void setTotalTimeText(QString);

    QTreeWidgetItem* getCurrentItem();
    FramePtr getFrameRef();
    PlayerPtr getCurrentPlayer();

public slots:
    /// \brief Add video file.
    /// Add a video file dialog and import wizard.
    void on_add_video_file();

    /// \brief Convert video directly to Event.
    void on_video_to_event();

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
    void on_item_doubleclicked(QTreeWidgetItem* item, int);

    /// \brief Changed selection in the video/event list.
    /// Updates the statistics for the selected events.
    void on_item_selection_changed();

    /// \brief Merge two events into one.
    ///The second selected event is merged after the first one.
    void on_merge();

    void flip_horizontally();

    void flip_vertically();

    /// \brief Calibrate the video.
    /// Call for the calibration function for each video selected.
    void on_calibrate();

    void on_discard_calibration();

    void on_export_camera();

    void on_import_camera();

    FrameItem* getFrame();

    void on_reproject();

    /// \brief Calculates the height of something.
    void on_height();

    void on_width();

    void on_length();

    /// \brief Exclude action.
    /// Start excluding a rectangular section of the video.
    void on_exclude_rectangle();

    void updateValues();

    void itemChanged(QTreeWidgetItem *item, int);

private:
    uint nEvent;
};

#endif // QTREEVIDEOS_HPP
