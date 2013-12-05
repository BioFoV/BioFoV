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
            ui->videoList->addItem(last);
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

void MainWindow::on_videoList_itemDoubleClicked(QListWidgetItem *item)
{
    VideoItem * vItem = (VideoItem *) item;
    ui->player->loadVid(vItem->getVideo());
}

void MainWindow::on_actionAuto_Detect_Events_triggered()
{
    VideoItem* videoiter;
    std::deque<Event*> events;
    EventItem* newEvent;
    qDebug("Going through all videos");
    for (int i = 0; i < ui->videoList->count(); i++){
        videoiter = (VideoItem*) ui->videoList->item(i);
        qDebug("Video %d",i);

        events = videoiter->getVideo()->autoDetectEvents();
        for (unsigned int j = 0; j < events.size(); j++){
            qDebug(" Event %d",j);
            newEvent = new EventItem();
            newEvent->setEvent(events.at(j));
            ui->eventList->addItem(newEvent);
        }
    }
}

void MainWindow::on_eventList_itemDoubleClicked(QListWidgetItem *item)
{
    EventItem * eItem = (EventItem *) item;
    ui->player->loadVid(eItem->getEvent());
}

void MainWindow::on_action_Remove_From_Project_triggered()
{
    qDeleteAll(ui->videoList->selectedItems());
}
