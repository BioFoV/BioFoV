#ifndef QTREEFACES_HPP
#define QTREEFACES_HPP

// OpenCV
#ifndef OPENCV_INC
#define OPENCV_INC
#include <opencv2/opencv.hpp>
#endif

#include "QitemFace.hpp"

#ifndef INC_SNAPSHOT
#define INC_SNAPSHOT
#include "Snapshot/Snapshot.hpp"
#endif

#include <QTreeWidget>

/**
 * @brief The QtreeFaces class
 */
class QtreeFaces : public QTreeWidget
{
    Q_OBJECT
public:
    explicit QtreeFaces(QWidget *parent = 0);
    void on_enter_pressed();
signals:
    void showStillImage(const cv::Mat& image);
    void showMessage(QString message);
public slots:
    void on_item_delete();
    void on_item_pressed(QTreeWidgetItem *item, int);
    void newFaceGroup();
    void updateCounts();

    void on_item_changed(QTreeWidgetItem *, int);
};

#endif // QTREEFACES_HPP
