#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QListWidget>
#include <QListWidgetItem>
#include <QtPrintSupport/QPrintDialog>
#include <QtPrintSupport/QPrinter>
#include <QProgressBar>

#ifndef INC_ABOUT
#define INC_ABOUT
#include "QdialogAbout.hpp"
#endif

#ifndef INC_VIDEOITEM
#define INC_VIDEOITEM
#include "QitemVideo.hpp"
#endif

#ifndef INC_EVENTITEM
#define INC_EVENTITEM
#include "QitemEvent.hpp"
#endif

#ifndef INC_FACEITEM
#define INC_FACEITEM
#include "QitemFace.hpp"
#endif

#ifndef INC_SPLITDIALOG
#define INC_SPLITDIALOG
#include "QdialogSplit.hpp"
#endif

#ifndef INC_CALIBRATIONDIALOG
#define INC_CALIBRATIONDIALOG
#include "QdialogCalibration.hpp"
#endif

#ifndef INC_DIALOGSETTINGS
#define INC_DIALOGSETTINGS
#include "QdialogSettings.hpp"
#endif

#ifndef INC_STRING
#define INC_STRING
#include <string>
#endif

#include "Drawables/rectanglemask.hpp"
#include "Drawables/drawheight.hpp"
#include "Feature/faces.hpp"

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

    /// \brief MainWindow constructor.
    /// \param parent Parent of the new MainWindow.
	explicit MainWindow(QWidget *parent = 0);

    /// \brief MainWindow destructor.
	~MainWindow();

public slots:

    /// \brief Enable the progress bar.
    /// \param min Minimum value of progressBar.
    /// \param max Maximum value of progressBar.
    void enableProgress(unsigned int min = 0, unsigned int max = 100);

    /// \brief Disables and empties the progress bar.
    void resetProgress();

    /// \brief Sets progress bar value.
    /// \param val New value for progressBar.
    void setProgress(uint val);

    // Status bar message handlers
    /// \brief Shows a message in the status bar.
    /// \param text message as a QString.
    void showMessage(QString text);

    /// \brief Shows a message in the status bar.
    /// \param text message as a normal C++ char pointer.
    void showMessage(const char* text);

    void loadVid(Player* player, int type);

    QdialogSettings* getSettings();

    int getPlayMode();

private slots:

    /// \brief Opens the about window.
    /// This was a test for the exec function and opening new windows/dialogs, but
    ///in the end it stayed.
    void openAbout();

    /// \brief Automatically split an event.
    /// This was sort of deprecated by the Auto Detect option, but it could still be
    ///applied to Events.
    void on_actionAuto_Split_triggered();

    /// \brief Changes the limits of progressBar.
    /// \param min Minimum value of progressBar.
    /// \param max Maximum value of progressBar.
    /// \param val Current value to set progressBar to.
    void setProgressSize(unsigned int min, unsigned int max, unsigned int val = 0);

    /// \brief Disables the progress bar.
    void disableProgress();

    // Event playback mode modifiers
    /// \brief RGB video playback triggered.
    /// Disables all the other playback options if enabled. If disabled,
    ///re-enable, since at least one playback option should be enabled.
    void on_actionNormal_triggered();

    /// \brief Mask playback triggered.
    /// Disables all the other playback options if enabled. If disabled,
    ///return to normal playback mode.
    void on_actionMask_triggered();

    /// \brief Masked video playback triggered.
    /// Disables all the other playback options if enabled. If disabled,
    ///return to normal playback mode.
    void on_actionMasked_Video_triggered();

    // Flag handlers
    /// \brief Event playback as RGB video toggled.
    /// \param arg1 Event playback as RGB video?
    void on_actionNormal_toggled(bool arg1);

    /// \brief Event playback of the mask toggled.
    /// \param arg1 Event playback as mask only?
    void on_actionMask_toggled(bool arg1);

    /// \brief Event playback of the masked RGB video toggled.
    /// \param arg1 Event playback as masked video?
    void on_actionMasked_Video_toggled(bool arg1);

    // Filter video
    /// \brief Crop action.
    /// Start cropping the video.
    void on_actionCrop_triggered();

    /// \brief Exclude action.
    /// Start excluding a rectangular section of the video.
    void on_actionExclude_rectangle_triggered();

    /// \brief Calculates the height of something.
    void on_actionHeight_triggered();

    /// \brief Merge two events into one.
    ///The second selected event is merged after the first one.
    void on_actionMerge_triggered();

    /// \brief Print the current frame with any of the system configured
    ///printers.
    void on_actionPrint_triggered();

    void on_actionDetect_Faces_triggered();

//    void on_faceList_itemPressed(QTreeWidgetItem *item, int column);

private:
    /// \brief UI created by Qt.
    ///Points to a class that contains everything that was defined in the
    ///mainwindow.ui XML file.
    Ui::MainWindow *ui;

    /// \brief Settings
    QdialogSettings* settings;

    /// \brief Total events found so far.
    int nEvent;

    QProgressBar* progressBar;

    /// \brief Playback Mode.
    /// Can be one of the 3 defined in event.hpp: PLAY_FRAMES, PLAY_MASK or
    ///PLAY_MASKED_FRAMES.
    int playMode;
    void keyPressEvent(QKeyEvent *ev);
};

#endif // MAINWINDOW_H
