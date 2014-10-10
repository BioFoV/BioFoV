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
#include "Drawables/drawangle.hpp"
#include "Drawables/rectanglemask.hpp"
#include "Drawables/drawreproj.hpp"
#include "QdialogCalibration.hpp"
#include "QplayerVideo.hpp"

/**
 * @brief The QtreeVideos class
 */
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

    void cancel();

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
    void on_add_video_file();
    void on_video_to_event();
    void on_auto_detect_events();
    void on_remove_from_project();
    void on_delete_event();
    void on_item_doubleclicked(QTreeWidgetItem* item, int column);
    void on_item_selection_changed();
    void on_merge();

    void flip_horizontally();
    void flip_vertically();
    void on_calibrate();
    void on_discard_calibration();
    void on_export_camera();
    void on_import_camera();

    FrameItem* getFrame();

    void on_reproject();

    /// \brief
    void on_height();
    void on_width();
    void on_length();
    void on_angle();
    void on_exclude_rectangle();

    void updateValues();

    void itemChanged(QTreeWidgetItem *item, int);

private:
    /**
     * @brief nEvent
     */
    uint nEvent;
};

#endif // QTREEVIDEOS_HPP
