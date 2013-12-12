#ifndef SPLITDIALOG_HPP
#define SPLITDIALOG_HPP

#include <QDialog>

namespace Ui {
class SplitDialog;
}

class SplitDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit SplitDialog(QWidget *parent = 0);
    ~SplitDialog();

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
