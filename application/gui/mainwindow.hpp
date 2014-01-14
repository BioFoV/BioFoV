#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QListWidget>
#include <QListWidgetItem>

#ifndef INC_ABOUT
#define INC_ABOUT
#include "about.hpp"
#endif

#ifndef INC_VIDEOITEM
#define INC_VIDEOITEM
#include "videoitem.hpp"
#endif

#ifndef INC_EVENTITEM
#define INC_EVENTITEM
#include "eventitem.hpp"
#endif

#ifndef INC_SPLITDIALOG
#define INC_SPLITDIALOG
#include "splitdialog.hpp"
#endif

#ifndef INC_CALIBRATIONDIALOG
#define INC_CALIBRATIONDIALOG
#include "calibrationdialog.hpp"
#endif

#ifndef INC_STRING
#define INC_STRING
#include <string>
#endif

#include "../framework/Drawables/rectanglemask.hpp"
#include "../framework/Drawables/drawheight.hpp"

namespace Ui {
class MainWindow;
}

///
/// \brief MainWindow class.
/// Responsible for the main window, channel all user requests to the rightful
///functions, and display the appropriate data.
///
class MainWindow : public QMainWindow
{
	Q_OBJECT
	
public:
    ///
    /// \brief MainWindow constructor.
    /// \param parent Parent of the new MainWindow.
    ///
	explicit MainWindow(QWidget *parent = 0);
    ///
    /// \brief MainWindow destructor.
    ///
	~MainWindow();

private slots:
    ///
    /// \brief Add video file.
    /// Add a video file dialog and import wizard.
    ///
    void on_actionAdd_Video_File_triggered();
    ///
    /// \brief Opens the about window.
    /// This was a test for the exec function and opening new windows/dialogs, but
    ///in the end it stayed.
    ///
    void openAbout();

    ///
    /// \brief Auto detect events in video.
    /// For each video in the video list split them into events accordingly with the
    ///given parameters in the split window that is used.
    ///
    void on_actionAuto_Detect_Events_triggered();
    ///
    /// \brief Remove video file from project.
    ///
    void on_action_Remove_From_Project_triggered();
    ///
    /// \brief Delete all selected Events.
    ///
    void on_actionDeleteEvent_triggered();
    ///
    /// \brief Automatically split an event.
    /// This was sort of deprecated by the Auto Detect option, but it could still be
    ///applied to Events.
    ///
    void on_actionAuto_Split_triggered();
    ///
    /// \brief Double click an item on the video/event list.
    /// \param item Pointer to the item which was double clicked.
    /// \param column Index of the clicked column (not used).
    ///
    void on_videoList_itemDoubleClicked(QTreeWidgetItem *item, int column);

    // Status bar message handlers
    ///
    /// \brief Shows a message in the status bar.
    /// \param text message as a QString.
    ///
    void showMessage(QString text);
    ///
    /// \brief Shows a message in the status bar.
    /// \param text message as a normal C++ char *.
    ///
    void showMessage(const char* text);

    ///
    /// \brief Changed selection in the video/event list.
    /// Updates the statistics for the selected events.
    ///
    void on_videoList_itemSelectionChanged();

    ///
    /// \brief Calibrate the video.
    /// Call for the calibration function for each video selected.
    ///
    void on_actionCalibrate_triggered();

    // Event playback mode modifiers
    ///
    /// \brief RGB video playback triggered.
    /// Disables all the other playback options if enabled. If disabled,
    ///re-enable, since at least one playback option should be enabled.
    ///
    void on_actionNormal_triggered();
    ///
    /// \brief Mask playback triggered.
    /// Disables all the other playback options if enabled. If disabled,
    ///return to normal playback mode.
    ///
    void on_actionMask_triggered();
    ///
    /// \brief Masked video playback triggered.
    /// Disables all the other playback options if enabled. If disabled,
    ///return to normal playback mode.
    ///
    void on_actionMasked_Video_triggered();
    // Flag handlers
    ///
    /// \brief Event playback as RGB video toggled.
    /// \param arg1 Event playback as RGB video?
    ///
    void on_actionNormal_toggled(bool arg1);
    ///
    /// \brief Event playback of the mask toggled.
    /// \param arg1 Event playback as mask only?
    ///
    void on_actionMask_toggled(bool arg1);
    ///
    /// \brief Event playback of the masked RGB video toggled.
    /// \param arg1 Event playback as masked video?
    ///
    void on_actionMasked_Video_toggled(bool arg1);

    // Filter video
    ///
    /// \brief Crop action.
    /// Start cropping the video
    ///
    void on_actionCrop_triggered();
    ///
    /// \brief Exclude action.
    /// Start excluding a rectangular section of the video
    ///
    void on_actionExclude_rectangle_triggered();

    void on_actionHeight_triggered();

    void on_actionMerge_triggered();

private:
    Ui::MainWindow *ui; ///< UI created by Qt.
                        ///<Points to a class that contains everything that was
                        ///<defined in the mainwindow.ui XML file.
    int nEvent;   ///< Total events found so far.
    int playMode; ///< Playback Mode.
                  ///<Can be one of the 3 defined in event.hpp: PLAY_FRAMES,
                  ///<PLAY_MASK or PLAY_MASKED_FRAMES.
};

#endif // MAINWINDOW_H
