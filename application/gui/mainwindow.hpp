#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QListWidget>
#include <QListWidgetItem>

#ifndef INC_ABOUT
#define INC_ABOUT
#include "about.hpp"
#endif

#ifndef INC_VIDEOITEM
#define INC_VIDEOITEM
#include "videoitem.hpp"
#endif

#ifndef INC_EVENTITEM
#define INC_EVENTITEM
#include "eventitem.hpp"
#endif

#ifndef INC_SPLITDIALOG
#define INC_SPLITDIALOG
#include "splitdialog.hpp"
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

    void on_actionAuto_Detect_Events_triggered();
    void on_action_Remove_From_Project_triggered();
    void on_actionDeleteEvent_triggered();
    void on_actionAuto_Split_triggered();
    void on_videoList_itemDoubleClicked(QTreeWidgetItem *item, int column);
    void showMessage(QString text);

    void on_videoList_itemSelectionChanged();

private:
    Ui::MainWindow *ui;
    int nEvent;
};

#endif // MAINWINDOW_H
