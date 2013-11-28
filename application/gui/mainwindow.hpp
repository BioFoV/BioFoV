#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QListWidget>

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
    void on_videoList_itemActivated(QListWidgetItem *item);
    void openAbout();

    void on_playButton_clicked();

private:
	Ui::MainWindow *ui;
	
};

#endif // MAINWINDOW_H
