#ifndef CALIBRATIONDIALOG_HPP
#define CALIBRATIONDIALOG_HPP

#include <QDialog>

namespace Ui {
class CalibrationDialog;
}

class CalibrationDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit CalibrationDialog(QWidget *parent = 0);
    ~CalibrationDialog();
    
    int getNBoards();
    int getFrameStep();
    int getWidth();
    int getHeight();
    int getIterations();

private:
    Ui::CalibrationDialog *ui;
};

#endif // CALIBRATIONDIALOG_HPP
