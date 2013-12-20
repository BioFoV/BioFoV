#include "mainwindow.hpp"
#include "ui_mainwindow.h"

///
/// \brief MainWindow constructor.
/// \param parent Parent of the new MainWindow.
///
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(openAbout()));
    nEvent = 0;
    playMode = PLAY_FRAMES;
}

///
/// \brief MainWindow destructor.
///
MainWindow::~MainWindow()
{
    delete ui;
}

///
/// \brief Add video file.
/// Add a video file dialog and import wizard.
///
void MainWindow::on_actionAdd_Video_File_triggered()
{
    VideoItem * last = NULL;
    QFileDialog getFileDialog(this);
    getFileDialog.setDirectory(QDir::homePath());
    getFileDialog.setFileMode(QFileDialog::ExistingFiles);
    getFileDialog.setAcceptMode(QFileDialog::AcceptOpen);

    QStringList fileNames;
    if(getFileDialog.exec())
    {
        fileNames = getFileDialog.selectedFiles();
        if (fileNames.isEmpty()) {
            showMessage("No files loaded");
            return;
        } // No file name provided
        foreach (QString fileName, fileNames) {
            last = new VideoItem(fileName);
            ui->videoList->addTopLevelItem(last);
            showMessage(QString("Loaded ") + fileName);
        }
        if(last != NULL) {
            ui->player->loadVid(last->getVideo(), PLAYER_VID);
            showMessage("Finished loading files");
        }
    } else {
        showMessage("No files selected");
    }
    return;
}

///
/// \brief Opens the about window.
/// This was a test for the exec function and opening new windows/dialogs, but
///in the end it stayed.
///
void MainWindow::openAbout()
{
    About about;
    about.exec();
}

///
/// \brief Auto detect events in video.
/// For each video in the video list split them into events accordingly with the
///given parameters in the split window that is used.
///
void MainWindow::on_actionAuto_Detect_Events_triggered()
{
    VideoItem* videoiter;
    std::deque<Event*> events;
    EventItem* newEvent;

    int i;
    unsigned int j;
    
    SplitDialog split;
    if(!split.exec()){
        showMessage(QString("Auto detection canceled"));
        return;
    }
    
    for (i = 0; i < ui->videoList->topLevelItemCount(); i++){
        videoiter = (VideoItem*) ui->videoList->topLevelItem(i);
        showMessage(QString("Analyzing Video %1").arg(i));

        events = videoiter->getVideo()->autoDetectEvents(split.getThreshold(),
                                                         split.getMaxFrames(),
                                                         split.getMinFrames(),
                                                         split.getHistory(),
                                                         split.getvarThreshold(),
                                                         split.getbShadowDetection());
        for (j = 0; j < events.size(); j++) {
            showMessage(QString("Found Event %1").arg(nEvent));
            newEvent = new EventItem(QString("E%1").arg(nEvent));;
            newEvent->setEvent(events.at(j));
            nEvent ++;
            videoiter->addChild(newEvent);
        }
        if (j != 0){
            videoiter->setExpanded(true);
        }
    }
}

///
/// \brief Remove video file from project.
///
void MainWindow::on_action_Remove_From_Project_triggered()
{
    qDeleteAll(ui->videoList->selectedItems());
}

///
/// \brief Delete all selected Events.
///
void MainWindow::on_actionDeleteEvent_triggered()
{
    qDeleteAll(ui->videoList->selectedItems());
}

///
/// \brief Automatically split an event.
/// This was sort of deprecated by the Auto Detect option, but it could still be
///applied to Events.
///
void MainWindow::on_actionAuto_Split_triggered()
{
    EventItem* eventIt;
    EventItem* newEventIt;
    std::deque<Event*> events;

    foreach(QTreeWidgetItem* item, ui->videoList->selectedItems()){
        eventIt = (EventItem *) item;
        events = eventIt->getEvent()->splitEvent(200, 3, 5);
        foreach(Event* event, events){
            showMessage(QString("Found Event %1").arg(nEvent));
            newEventIt = new EventItem(QString("E%1").arg(nEvent));
            newEventIt->setEvent(event);
            nEvent ++;
            eventIt->parent()->addChild(newEventIt);
        }
        ui->videoList->removeItemWidget(item,0);
    }
}

///
/// \brief Double click an item on the video/event list.
/// \param item Pointer to the item which was double clicked.
/// \param column Index of the clicked column (not used).
///
void MainWindow::on_videoList_itemDoubleClicked(QTreeWidgetItem *item,
                                                int column)
{
    showMessage(QString("Loaded ") + item->text(0));
    if (item->parent() == NULL){
        VideoItem * vItem = (VideoItem *) item;
        ui->player->loadVid(vItem->getVideo(), PLAYER_VID);
    } else {
        EventItem * vItem = (EventItem *) item;
        Event* ev = vItem->getEvent();
        ev->setPlaybackMode(playMode);
        ui->player->loadVid(ev, PLAYER_EV);
    }
    ui->player->playOrPause();
}

/*******************************************************************************
 * Display messages on status bar
 ******************************************************************************/
///
/// \brief Shows a message in the status bar.
/// \param text message as a QString.
///
void MainWindow::showMessage(QString text){
    ui->statusBar->showMessage(text);
}

///
/// \brief Shows a message in the status bar.
/// \param text message as a normal C++ char *.
///
void MainWindow::showMessage(const char *text){
    ui->statusBar->showMessage(QString(text));
}

///
/// \brief Changed selection in the video/event list.
/// Updates the statistics for the selected events.
///
void MainWindow::on_videoList_itemSelectionChanged()
{
    EventItem* eventIt;
    int selected = 0;
    double frames = 0;
    double time = 0;
    foreach (QTreeWidgetItem* item, ui->videoList->selectedItems()){
        eventIt = (EventItem *) item;
        frames += eventIt->getEvent()->getLengthFrames();
        time += eventIt->getEvent()->getLengthTime();
        selected ++;
    }
    ui->labelSelected->setText(QString("%1").arg(selected));
    ui->labelTotalFrames->setText(QString("%1").arg(frames));
    ui->labelTotalTime->setText(QString("%1 s").arg(time));
}

///
/// \brief Calibrate the video.
/// Call for the calibration function for each video selected.
///
void MainWindow::on_actionCalibrate_triggered()
{
    if (ui->videoList->selectedItems().size() == 0){
        showMessage("Select a Video first");
        return;
    }

    CalibrationDialog calibDiag;
    if(!calibDiag.exec()){
        showMessage("Calibration canceled");
        return;
    }

    VideoItem* videoIt;
    foreach (QTreeWidgetItem* item, ui->videoList->selectedItems()){
        if (item->parent() != NULL){
            continue;
        }
        videoIt = (VideoItem*) item;
        videoIt->getVideo()->calibrate(calibDiag.getNBoards(),
                                       calibDiag.getFrameStep(),
                                       calibDiag.getWidth(),
                                       calibDiag.getHeight(),
                                       calibDiag.getIterations());
        if(videoIt->getVideo()->isCalibrated()){
            showMessage("Video Calibrated");
            ui->player->playOrPause();
        } else {
            showMessage("Failed Calibration");
        }
    }
}

///
/// \brief RGB video playback triggered.
/// Disables all the other playback options if enabled. If disabled,
///re-enable, since at least one playback option should be enabled.
///
void MainWindow::on_actionNormal_triggered()
{
    if (ui->actionNormal->isChecked()) {
        ui->actionMask->setChecked(false);
        ui->actionMasked_Video->setChecked(false);
    } else {
        ui->actionNormal->setChecked(true);
    }
}

///
/// \brief Mask playback triggered.
/// Disables all the other playback options if enabled. If disabled,
///return to normal playback mode.
///
void MainWindow::on_actionMask_triggered()
{
    if (ui->actionMask->isChecked()) {
        ui->actionNormal->setChecked(false);
        ui->actionMasked_Video->setChecked(false);
    } else {
        ui->actionNormal->setChecked(true);
    }
}

///
/// \brief Masked video playback triggered.
/// Disables all the other playback options if enabled. If disabled,
///return to normal playback mode.
///
void MainWindow::on_actionMasked_Video_triggered()
{
    if (ui->actionMasked_Video->isChecked()) {
        ui->actionNormal->setChecked(false);
        ui->actionMask->setChecked(false);
    } else {
        ui->actionNormal->setChecked(true);
    }
}

///
/// \brief Event playback as RGB video toggled.
/// \param arg1 Event playback as RGB video?
///
void MainWindow::on_actionNormal_toggled(bool arg1)
{
    if (arg1) {
        playMode = PLAY_FRAMES;
        ui->player->setPlayMode(playMode);
    }
}

///
/// \brief Event playback of the mask toggled.
/// \param arg1 Event playback as mask only?
///
void MainWindow::on_actionMask_toggled(bool arg1)
{
    if (arg1) {
        playMode = PLAY_MASK;
        ui->player->setPlayMode(playMode);
    }
}

///
/// \brief Event playback of the masked RGB video toggled.
/// \param arg1 Event playback as masked video?
///
void MainWindow::on_actionMasked_Video_toggled(bool arg1)
{
    if (arg1) {
        playMode = PLAY_MASKED_FRAMES;
        ui->player->setPlayMode(playMode);
    }
}

///
/// \brief Crop action.
/// Start cropping the video
///
void MainWindow::on_actionCrop_triggered()
{
    ui->player->pause();
    showMessage("Select the area to crop in the player");
}

///
/// \brief Exclude action.
/// Start excluding a rectangular section of the video
///
void MainWindow::on_actionExclude_rectangle_triggered()
{
    ui->player->pause();
    showMessage("Select a rectangle to zoneout in the player");
}
