#include "mainwindow.hpp"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(openAbout()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionAdd_Video_File_triggered()
{
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
            ui->videoList->addItem(fileName);
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

/*
 * Play button handler
 */
void MainWindow::on_playButton_clicked()
{
    ui->player->playOrPause();
}

void MainWindow::on_videoList_itemDoubleClicked(QListWidgetItem *item)
{
    std::string filename = item->text().toStdString();
    Video * vid = new Video(filename);
    ui->player->loadVid(vid);
    qDebug("loaded video %s to player",filename.c_str());
}
