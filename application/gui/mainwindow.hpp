#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QListWidget>

#ifndef INC_ABOUT
#define INC_ABOUT
#include "about.hpp"
#endif

#include <string>

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

private:
	Ui::MainWindow *ui;
    QList<QString> videos;
};

#endif // MAINWINDOW_H
