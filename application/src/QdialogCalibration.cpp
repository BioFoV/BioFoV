#include "QdialogCalibration.hpp"
#include "ui_calibrationdialog.h"

/**
 * @brief CalibrationDialog::CalibrationDialog
 * @param parent
 */
CalibrationDialog::CalibrationDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::CalibrationDialog)
{
	ui->setupUi(this);
}

/**
 * @brief CalibrationDialog::~CalibrationDialog
 */
CalibrationDialog::~CalibrationDialog()
{
	delete ui;
}

//FIXME: non negative numbers should REALLY be unsigned!
/**
 * @brief CalibrationDialog::getNBoards
 * @return
 */
int CalibrationDialog::getNBoards(){
	return ui->nBoards->value();
}

/**
 * @brief CalibrationDialog::getFrameStep
 * @return
 */
int CalibrationDialog::getFrameStep(){
	return ui->frameStep->value();
}

/**
 * @brief CalibrationDialog::getWidth
 * @return
 */
int CalibrationDialog::getWidth(){
	return ui->width->value();
}

/**
 * @brief CalibrationDialog::getHeight
 * @return
 */
int CalibrationDialog::getHeight(){
	return ui->height->value();
}

/**
 * @brief CalibrationDialog::getIterations
 * @return
 */
int CalibrationDialog::getIterations(){
	return ui->iterations->value();
}

/**
 * @brief CalibrationDialog::getFlags
 * @return
 */
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
