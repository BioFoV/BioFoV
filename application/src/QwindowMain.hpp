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
#include "Feature/faces.hpp"

namespace Ui {
class MainWindow;
}

/**
 * @brief The MainWindow class.
 * Responsible for the main window, channel all user requests to the rightful
 * functions, and display the appropriate data.
 */
class MainWindow : public QMainWindow
{
	Q_OBJECT
	
public:
    explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

public slots:
    void enableProgress(unsigned int min = 0, unsigned int max = 100);
    void resetProgress();
    void setProgress(uint val);

    // Status bar message handlers
    void showMessage(QString text);
    void showMessage(const char* text);

    QdialogSettings* getSettings();

    int getPlayMode();

    void cancel();

private slots:
    void openAbout();

    void setProgressSize(unsigned int min, unsigned int max, unsigned int val = 0);
    void disableProgress();

    // Event playback mode modifiers
    void on_actionNormal_triggered();
    void on_actionMask_triggered();
    void on_actionMasked_Video_triggered();

    // Flag handlers
    void on_actionNormal_toggled(bool arg1);
    void on_actionMask_toggled(bool arg1);
    void on_actionMasked_Video_toggled(bool arg1);

    void on_actionDetect_Faces_triggered();
    void on_actionExport_Event_triggered();

    void on_actionSave_Current_Player_Image_triggered();
    void on_actionSave_Faces_As_Images_triggered();

private:
    /**
     * @brief UI created by Qt.
     * Points to a class that contains everything that was defined in the
     * mainwindow.ui XML file.
     */
    Ui::MainWindow *ui;

    /**
     * @brief Settings
     */
    QdialogSettings* settings;

    /**
     * @brief Total events found so far.
     */
    int nEvent;

    /**
     * @brief progressBar
     */
    QProgressBar* progressBar;

    /**
     * @brief cancelButton
     */
    QPushButton* cancelButton;

    /**
     * @brief Playback Mode.
     * Can be one of the 3 defined in event.hpp: PLAY_FRAMES, PLAY_MASK or
     * PLAY_MASKED_FRAMES.
     */
    int playMode;

    /**
     * @brief keyPressEvent
     * @param ev
     */
    void keyPressEvent(QKeyEvent *ev);

    /**
     * @brief toCancel
     */
    bool toCancel;

    /**
     * @brief canceled
     */
    void canceled();
};

#endif // MAINWINDOW_H
