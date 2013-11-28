#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QListWidget>

#ifndef INC_ABOUT
#define INC_ABOUT
#include "about.hpp"
#endif

#ifndef INC_VIDEO
#define INC_VIDEO
#include "../framework/Video/Video.hpp"
#endif

#ifndef INC_STRING
#define INC_STRING
#include <string>
#endif

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT
	
public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

private slots:
    void on_actionAdd_Video_File_triggered();
    void openAbout();

    void on_playButton_clicked();

    void on_videoList_itemDoubleClicked(QListWidgetItem *item);

    void on_stepButton_clicked();

private:
	Ui::MainWindow *ui;
    QList<Video*> videos;
};

#endif // MAINWINDOW_H
