#include "mainwindow.hpp"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(openAbout()));
    nEvent = 0;
    playMode = PLAY_FRAMES;
}


MainWindow::~MainWindow()
{
    delete ui;
}


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
            ui->menuPlayback_Mode->setEnabled(false);
            ui->player->loadVid(last->getVideo(), PLAYER_VID);
            showMessage("Finished loading files");
        }
    } else {
        showMessage("No files selected");
    }
    return;
}

void MainWindow::openAbout()
{
    About about;
    about.exec();
}

void MainWindow::on_actionAuto_Detect_Events_triggered()
{
    VideoItem* videoiter;
    std::deque<Event*> events;
    EventItem* newEvent;

    unsigned int j;
    
    SplitDialog split;
    
    if (ui->videoList->selectedItems().isEmpty()){
        showMessage("Select at least one Video");
        return;
    }

    foreach (QTreeWidgetItem* item, ui->videoList->selectedItems()){
        if (item->parent() != NULL){
            showMessage("Item selected is not a video");
            continue;
        }
        videoiter = (VideoItem*) item;
        showMessage(QString("Analyzing Video %1").arg(item->text(0)));
        split.setFPS(videoiter->getVideo()->getFPS());
        split.setWindowTitle(videoiter->text(0));
        if(!split.exec()){
            showMessage(QString("Auto detection canceled"));
            continue;
        }

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

void MainWindow::on_action_Remove_From_Project_triggered()
{
    if(ui->videoPage->isVisible()){
        foreach(QTreeWidgetItem* item, ui->videoList->selectedItems()){
            if(item->parent() == NULL){
                delete item;
            }
            else {
                showMessage("Item selected is not a Video");
            }
        }
    }
}

void MainWindow::on_actionDeleteEvent_triggered()
{
    if(ui->videoPage->isVisible()){
        if(ui->videoPage->isVisible()){
            foreach(QTreeWidgetItem* item, ui->videoList->selectedItems()){
                if(item->parent() != NULL){
                    delete item;
                }
                else {
                    showMessage("Item selected is not an Event");
                }
            }
        }
    } else {
        showMessage("Please select the Videos tab first");
    }
}


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

void MainWindow::on_videoList_itemDoubleClicked(QTreeWidgetItem *item,
                                                int column)
{
    showMessage(QString("Loaded ") + item->text(0));
    if (item->parent() == NULL){
        VideoItem * vItem = (VideoItem *) item;
        ui->menuPlayback_Mode->setEnabled(false);
        ui->player->loadVid(vItem->getVideo(), PLAYER_VID);
    } else {
        EventItem * vItem = (EventItem *) item;
        Event* ev = vItem->getEvent();
        ev->setPlaybackMode(playMode);
        ui->menuPlayback_Mode->setEnabled(true);
        ui->player->loadVid(ev, PLAYER_EV);
    }
    ui->player->playOrPause();
}


void MainWindow::showMessage(QString text){
    ui->statusBar->showMessage(text);
}

void MainWindow::showMessage(const char *text){
    ui->statusBar->showMessage(QString(text));
}

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


void MainWindow::on_actionNormal_triggered()
{
    if (ui->actionNormal->isChecked()) {
        ui->actionMask->setChecked(false);
        ui->actionMasked_Video->setChecked(false);
    } else {
        ui->actionNormal->setChecked(true);
    }
}


void MainWindow::on_actionMask_triggered()
{
    if (ui->actionMask->isChecked()) {
        ui->actionNormal->setChecked(false);
        ui->actionMasked_Video->setChecked(false);
    } else {
        ui->actionNormal->setChecked(true);
    }
}


void MainWindow::on_actionMasked_Video_triggered()
{
    if (ui->actionMasked_Video->isChecked()) {
        ui->actionNormal->setChecked(false);
        ui->actionMask->setChecked(false);
    } else {
        ui->actionNormal->setChecked(true);
    }
}


void MainWindow::on_actionNormal_toggled(bool arg1)
{
    if (arg1) {
        playMode = PLAY_FRAMES;
        ui->player->setPlayMode(playMode);
    }
}


void MainWindow::on_actionMask_toggled(bool arg1)
{
    if (arg1) {
        playMode = PLAY_MASK;
        ui->player->setPlayMode(playMode);
    }
}


void MainWindow::on_actionMasked_Video_toggled(bool arg1)
{
    if (arg1) {
        playMode = PLAY_MASKED_FRAMES;
        ui->player->setPlayMode(playMode);
    }
}


void MainWindow::on_actionCrop_triggered()
{
    ui->player->pause();
    showMessage("Select the area to crop in the player");
//    ui->player->setClickable();
}


void MainWindow::on_actionExclude_rectangle_triggered()
{
    ui->player->pause();
    showMessage("Select a rectangle to zoneout in the player");
    ui->player->setClickable((Drawable*)new RectangleMask());
}

void MainWindow::on_actionHeight_triggered()
{
    ui->player->pause();
    showMessage("Select 4 points in the player");
    ui->player->setClickable((Drawable*)new DrawHeight());
}

void MainWindow::on_actionMerge_triggered()
{
    unsigned int count = 0;
    EventItem* it0, * it1;
    foreach (QTreeWidgetItem* item, ui->videoList->selectedItems()){
        if(item->parent() == NULL){
            showMessage("Merging Videos is not supported");
            return;
        }
        else{
            switch (count){
                case 0:
                    it0 = (EventItem*) item;
                    break;
                case 1:
                    it1 = (EventItem*) item;
                    break;
                case 2:
                    showMessage("Events can only be merged in pairs");
                    return;
            }
            count++;
        }
    }
    if (count == 0 || count == 1){
        showMessage("Select two events to be merged");
        return;
    }
    showMessage(QString("Merging events %1 and %2").arg(it0->text(0), it1->text(0)));
    *(it0->getEvent()) += *(it1->getEvent());
    showMessage(QString("Merged events %1 and %2 into event %1").arg(it0->text(0), it1->text(0)));

    delete(it1);
}

void MainWindow::on_actionPrint_triggered()
{
    QPrinter printer;
    QPrintDialog *dlg = new QPrintDialog(&printer,0);
    if(dlg->exec() == QDialog::Accepted) {
        QPainter painter(&printer);
        ui->player->print(painter);
        painter.end();
    }

    delete dlg;
}

void MainWindow::on_actionHorizontally_triggered()
{
    VideoItem * vidItem;
    foreach (QTreeWidgetItem* item, ui->videoList->selectedItems()){
        if(item->parent() != NULL){
            showMessage("Flip Videos, not events.");
            continue;
        }
        vidItem = (VideoItem*) item;
        vidItem->getVideo()->flip_horizontally();
        showMessage("Flipped selected Video.");
    }
}

void MainWindow::on_actionVertically_triggered()
{
    VideoItem * vidItem;
    foreach (QTreeWidgetItem* item, ui->videoList->selectedItems()){
        if(item->parent() != NULL){
            showMessage("Flip Videos, not events.");
            continue;
        }
        vidItem = (VideoItem*) item;
        vidItem->getVideo()->flip_vertically();
        showMessage("Flipped selected Video.");
    }
}

void MainWindow::on_actionDetect_Faces_triggered()
{
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
            Face* face = new Face(fileName.toStdString());

            foreach (QTreeWidgetItem* item, ui->videoList->selectedItems()){
                face->addEvent(((EventItem* )item)->getEvent());
            }
            foreach (QTreeWidgetItem* item, ui->videoList->selectedItems()){
                Event* ev = ((EventItem*)item)->getEvent();
                Frame * face_frame;
                for (;;){
                    if(!ev->getFrameObject(&face_frame))
                        break;
                    face->findFaces(face_frame);
                }
                FaceItem * newFaceItem = new FaceItem(QString("face"), face);
                ui->faceList->addTopLevelItem(newFaceItem);
            }
        }
    }
}

void MainWindow::on_actionDeleteFace_triggered()
{
    if(ui->facePage->isVisible()){
        foreach(QTreeWidgetItem* item, ui->faceList->selectedItems()){
            if(item->parent() != NULL){
                delete item;
            }
            else {
                showMessage("Item selected is not a Face");
            }
        }
    }
}

void MainWindow::on_faceList_itemPressed(QTreeWidgetItem *item, int column)
{
    if(item->parent() == NULL){
        return;
    }

    SnapshotItem* snapitem = (SnapshotItem *) item;
    ui->player->showStillImage(snapitem->getSnapshot()->getMasked());
    ui->menuPlayback_Mode->setEnabled(false);
}

void MainWindow::keyPressEvent(QKeyEvent *ev){
    if(ev->key() == Qt::Key_Delete){
        on_actionDeleteEvent_triggered();
        on_actionDeleteFace_triggered();
    }
}
