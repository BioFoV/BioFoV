#include "QwindowMain.hpp"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(openAbout()));
    nEvent = 0;
    playMode = PLAY_FRAMES;

    // Progress bar setup
    //This is here since it can not be done in the mainwindow.ui file
    progressBar = new QProgressBar(NULL);
    progressBar->setMaximumHeight(16);
    progressBar->setMaximumWidth(200);
    progressBar->setTextVisible(false);
    this->statusBar()->addPermanentWidget(progressBar, 0);

    progressBar->setFormat(QString("%v/%m"));
    setProgressSize(0, 100);
    disableProgress();

    // Settings setup
    settings = new QdialogSettings();

    connect(ui->actionSave_Settings_as, SIGNAL(triggered()),
            settings, SLOT(saveSettingsAs()));
    connect(ui->actionSave_Settings, SIGNAL(triggered()),
            settings, SLOT(saveSettings()));
    connect(ui->actionLoad_Settings, SIGNAL(triggered()),
            settings, SLOT(loadSettings()));

    connect(ui->actionSettings, SIGNAL(triggered()),
            settings, SLOT(exec()));
            
    connect(ui->faceList, SIGNAL(showStillImage(cv::Mat)),
            ui->player, SLOT(showStillImage(cv::Mat)));

    connect(ui->faceList, SIGNAL(showMessage(QString)),
            this, SLOT(showMessage(QString)));
    connect(ui->videoList, SIGNAL(showMessage(QString)),
            this, SLOT(showMessage(QString)));

    connect(ui->videoList, SIGNAL(loadVid(Player*, int)),
            this, SLOT(loadVid(Player*,int)));

    connect(ui->actionAdd_Video_File, SIGNAL(triggered()),
            ui->videoList, SLOT(on_add_video_file()));
    connect(ui->actionAuto_Detect_Events, SIGNAL(triggered()),
            ui->videoList, SLOT(on_auto_detect_events()));

    connect(ui->videoList, SIGNAL(getSettings()),
            this, SLOT(getSettings()));

    connect(ui->videoList, SIGNAL(startProgress(uint,uint)),
            this, SLOT(enableProgress(uint,uint)));
    connect(ui->videoList, SIGNAL(progressChanged(uint)),
            this, SLOT(setProgress(uint)));
    connect(ui->videoList, SIGNAL(resetProgress()),
            this, SLOT(resetProgress()));

    connect(ui->actionDeleteFace, SIGNAL(triggered()),
            ui->faceList, SLOT(on_item_delete()));
    connect(ui->actionNew_Face_Group, SIGNAL(triggered()),
            ui->faceList, SLOT(newFaceGroup()));

    connect(ui->videoList, SIGNAL(setPlaybackEnabled(bool)),
            ui->menuPlayback_Mode, SLOT(setEnabled(bool)));

    connect(ui->action_Remove_From_Project, SIGNAL(triggered()),
            ui->videoList, SLOT(on_remove_from_project()));
    connect(ui->actionHorizontally, SIGNAL(triggered()),
            ui->videoList, SLOT(flip_horizontally()));
    connect(ui->actionVertically, SIGNAL(triggered()),
            ui->videoList, SLOT(flip_horizontally()));
    connect(ui->actionCalibrate, SIGNAL(triggered()),
            ui->videoList, SLOT(on_calibrate()));
    connect(ui->actionImport_camera, SIGNAL(triggered()),
            ui->videoList, SLOT(on_import_camera()));
    connect(ui->actionExport_camera, SIGNAL(triggered()),
            ui->videoList, SLOT(on_export_camera()));
    connect(ui->actionMerge, SIGNAL(triggered()),
            ui->videoList, SLOT(on_merge()));

    connect(ui->videoList, SIGNAL(removePlayer(Player*)),
            ui->player, SLOT(unload(Player*)));
    connect(ui->videoList, SIGNAL(getPlayMode()),
            this, SLOT(getPlayMode()));
    connect(ui->videoList, SIGNAL(setPlaybackMode(int)),
            ui->player, SLOT(setPlayMode(int)));
    connect(ui->videoList, SIGNAL(playOrPause()),
            ui->player, SLOT(playOrPause()));

    connect(ui->videoList, SIGNAL(setSelectedText(QString)),
            ui->labelSelected, SLOT(setText(QString)));
    connect(ui->videoList, SIGNAL(setTotalFramesText(QString)),
            ui->labelTotalFrames, SLOT(setText(QString)));
    connect(ui->videoList, SIGNAL(setTotalTimeText(QString)),
            ui->labelTotalTime, SLOT(setText(QString)));
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openAbout()
{
    About about;
    about.exec();
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
            showMessage(tr("Found Event %1").arg(nEvent));
            newEventIt = new EventItem(QString("E%1").arg(nEvent));
            newEventIt->setEvent(event);
            nEvent ++;
            eventIt->parent()->addChild(newEventIt);
        }
        ui->videoList->removeItemWidget(item,0);
    }
}

void MainWindow::showMessage(QString text){
    ui->statusBar->showMessage(text);
}

void MainWindow::showMessage(const char *text){
    ui->statusBar->showMessage(QString(text));
}

void MainWindow::setProgressSize(unsigned int min, unsigned int max,
                                 unsigned int val) {
    progressBar->setMinimum(min);
    progressBar->setMaximum(max);
    setProgress(val);
}

void MainWindow::enableProgress(unsigned int min, unsigned int max){
    progressBar->setEnabled(true);
    setProgressSize(min, max, min);
}

void MainWindow::setProgress(uint val){
    progressBar->setValue(val);
}

void MainWindow::disableProgress(){
    progressBar->setEnabled(false);
}

void MainWindow::resetProgress(){
    setProgressSize(0, 100, 0);
    disableProgress();
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

int MainWindow::getPlayMode(){
    return playMode;
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
    showMessage(tr("Select the area to crop in the player"));
//    ui->player->setClickable();
}


void MainWindow::on_actionExclude_rectangle_triggered()
{
    ui->player->pause();
    showMessage(tr("Select a rectangle to zoneout in the player"));
    ui->player->setClickable((Drawable*)new RectangleMask());
}

void MainWindow::on_actionHeight_triggered()
{
    ui->player->pause();
    showMessage(tr("Select 4 points in the player"));
    ui->player->setClickable((Drawable*)new DrawHeight());
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

void MainWindow::on_actionDetect_Faces_triggered()
{
    QFileDialog getFileDialog(this);
    getFileDialog.setDirectory(QDir(settings->getHaarDir()));
    getFileDialog.setFileMode(QFileDialog::ExistingFiles);
    getFileDialog.setAcceptMode(QFileDialog::AcceptOpen);

    QStringList fileNames;
    if(getFileDialog.exec())
    {
        fileNames = getFileDialog.selectedFiles();
        if (fileNames.isEmpty()) {
            showMessage(tr("No files loaded"));
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
                // rewind event
                ev->setFramePos(0);
                enableProgress(0, ev->getLengthFrames());
                for (;;){
                    if(!ev->getFrameObject(&face_frame))
                        break;
                    setProgress(ev->getFramePos());
                    face->findFaces(face_frame);
                }
                resetProgress();
                if (face->faceNumber() == 0){
                    showMessage(tr("No faces found"));
                    return;
                } else {
                    FaceItem * newFaceItem = new FaceItem(tr("face"), face);
                    ui->faceList->addTopLevelItem(newFaceItem);
                    showMessage(tr("Found %1 faces").arg(face->faceNumber()));
                }
                // rewind event again
                ev->setFramePos(0);
            }
        }
    }
}

void MainWindow::keyPressEvent(QKeyEvent *ev){
    // DELETE
    if(ev->key() == Qt::Key_Delete){
        ui->videoList->on_delete_event();
        ui->actionDeleteFace->trigger();
    }
    // ENTER
    else if ( ev->key() == Qt::Key_Enter || ev->key() == Qt::Key_Return ){

        if(ui->videoList->isVisible()){
            foreach (QTreeWidgetItem* item, ui->videoList->selectedItems()){
                ui->videoList->on_item_doubleclicked(item, 0);
            }
        }
        ui->faceList->on_enter_pressed();
    }
}

void MainWindow::loadVid(Player* player, int type){
    ui->player->loadVid(player, type);
}

QdialogSettings* MainWindow::getSettings(){
    return settings;
}
