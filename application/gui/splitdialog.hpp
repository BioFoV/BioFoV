#ifndef SPLITDIALOG_HPP
#define SPLITDIALOG_HPP

#include <QDialog>

// the following are in seconds
#define DEFAULT_MAX_TIME 5
#define DEFAULT_MIN_TIME 2
#define DEFAULT_HIST     20

namespace Ui {
class SplitDialog;
}

class SplitDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit SplitDialog(QWidget *parent = 0);
    ~SplitDialog();

    // Set
    void setFPS(unsigned int FPS);

    // Get
    int getThreshold();
    int getMaxFrames();
    int getMinFrames();
    int getHistory();
    int getvarThreshold();
    bool getbShadowDetection();

private:
    Ui::SplitDialog *ui;
};

#endif // SPLITDIALOG_HPP
