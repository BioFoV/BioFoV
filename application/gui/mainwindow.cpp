#include "mainwindow.hpp"
#include "ui_mainwindow.h"

/*******************************************************************************
 * Constructors
 ******************************************************************************/
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(openAbout()));
    nEvent = 0;
}

/*******************************************************************************
 * Destructors
 ******************************************************************************/
MainWindow::~MainWindow()
{
    delete ui;
}

/*******************************************************************************
 * Actions
 ******************************************************************************/
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
            ui->player->loadVid(last->getVideo());
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

void MainWindow::on_action_Remove_From_Project_triggered()
{
    qDeleteAll(ui->videoList->selectedItems());
}

void MainWindow::on_actionDeleteEvent_triggered()
{
    qDeleteAll(ui->videoList->selectedItems());
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
        ui->player->loadVid(vItem->getVideo());
    } else {
        EventItem * vItem = (EventItem *) item;
        ui->player->loadVid(vItem->getEvent());
    }
    ui->player->playOrPause();
}

/*******************************************************************************
 * Display messages on status bar
 ******************************************************************************/
void MainWindow::showMessage(QString text){
    ui->statusBar->showMessage(text);
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
        showMessage(QString("Select a Video first"));
        return;
    }

    CalibrationDialog calibDiag;
    if(!calibDiag.exec()){
        showMessage(QString("Calibration canceled"));
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
    }
}
