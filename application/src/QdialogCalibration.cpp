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

unsigned int CalibrationDialog::getFlags(){
    return CV_CALIB_FIX_PRINCIPAL_POINT * ui->fixPrincipalPoint->isChecked() |
           CV_CALIB_FIX_ASPECT_RATIO * ui->fixAspectRatio->isChecked() |
           CV_CALIB_ZERO_TANGENT_DIST * ui->zeroTangentDist->isChecked() |
           CV_CALIB_RATIONAL_MODEL * ui->rationalModel->isChecked() |
           CV_CALIB_FIX_K1 * ui->k1->isChecked() |
           CV_CALIB_FIX_K2 * ui->k2->isChecked() |
           CV_CALIB_FIX_K3 * ui->k3->isChecked() |
           CV_CALIB_FIX_K4 * ui->k4->isChecked() |
           CV_CALIB_FIX_K5 * ui->k5->isChecked() |
           CV_CALIB_FIX_K6 * ui->k6->isChecked();
}
