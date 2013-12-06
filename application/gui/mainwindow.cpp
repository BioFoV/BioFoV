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
        if (fileNames.isEmpty()) {return;} // No file name provided
        foreach (QString fileName, fileNames) {
            last = new VideoItem(fileName);
            last->setText(0,fileName);
            last->setText(1,TAG_VIDEO);
            ui->videoList->addTopLevelItem(last);
        }
        if(last != NULL) {
            ui->player->loadVid(last->getVideo());
        }
    } else {
        qDebug("Failed to open FileDialog window");
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
    qDebug("Going through all videos");
    for (int i = 0; i < ui->videoList->topLevelItemCount(); i++){
        videoiter = (VideoItem*) ui->videoList->topLevelItem(i);
        qDebug("Video %d",i);

        events = videoiter->getVideo()->autoDetectEvents();
        for (unsigned int j = 0; j < events.size(); j++){
            qDebug(" Event %d",j);
            newEvent = new EventItem();
            newEvent->setEvent(events.at(j));
            newEvent->setText(0,QString("E%1").arg(nEvent));
            newEvent->setText(1, TAG_EVENT);
            nEvent ++;
            videoiter->addChild(newEvent);
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
    std::list<Event*> events;

    foreach(QTreeWidgetItem* item, ui->videoList->selectedItems()){
        eventIt = (EventItem *) item;
        events = eventIt->getEvent()->splitEvent(200,3);
        foreach(Event* event, events){
            newEventIt = new EventItem;
            newEventIt->setEvent(event);
            newEventIt->setText(0, QString("E%1").arg(nEvent));
            newEventIt->setText(1, TAG_EVENT );
            nEvent ++;
            eventIt->parent()->addChild(newEventIt);
        }
        ui->videoList->removeItemWidget(item,0);
    }
}

void MainWindow::on_videoList_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    VideoItem * vItem = (VideoItem *) item;
    ui->player->loadVid(vItem->getVideo());
}
