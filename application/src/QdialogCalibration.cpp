#include "QdialogCalibration.hpp"
#include "ui_calibrationdialog.h"

CalibrationDialog::CalibrationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CalibrationDialog)
{
    ui->setupUi(this);
}

CalibrationDialog::~CalibrationDialog()
{
    delete ui;
}

//FIXME: non negative numbers should REALLY be unsigned!
int CalibrationDialog::getNBoards(){
    return ui->nBoards->value();
}

int CalibrationDialog::getFrameStep(){
    return ui->frameStep->value();
}

int CalibrationDialog::getWidth(){
    return ui->width->value();
}

int CalibrationDialog::getHeight(){
    return ui->height->value();
}

int CalibrationDialog::getIterations(){
    return ui->iterations->value();
}
