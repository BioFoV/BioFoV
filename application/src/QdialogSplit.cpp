#include "QdialogSplit.hpp"
#include "ui_splitdialog.h"

/**
 * @brief SplitDialog::SplitDialog
 * @param parent
 */
SplitDialog::SplitDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::SplitDialog)
{
	ui->setupUi(this);
}

/**
 * @brief SplitDialog::~SplitDialog
 */
SplitDialog::~SplitDialog()
{
	delete ui;
}

/**
 * @brief SplitDialog::setFPS
 * @param FPS
 */
void SplitDialog::setFPS(unsigned int FPS) {
	fps = FPS;
	ui->maxframes->setValue(FPS * DEFAULT_MAX_TIME);
	ui->minframes->setValue(FPS * DEFAULT_MIN_TIME);
	ui->historyframes->setValue(FPS * DEFAULT_HIST);
}

/**
 * @brief SplitDialog::getThreshold
 * @return
 */
int SplitDialog::getThreshold(){
	return ui->threshSlider->value();
}

/**
 * @brief SplitDialog::getMaxFrames
 * @return
 */
int SplitDialog::getMaxFrames(){
	return ui->maxframes->value();
}

/**
 * @brief SplitDialog::getMinFrames
 * @return
 */
int SplitDialog::getMinFrames(){
	return ui->minframes->value();
}

/**
 * @brief SplitDialog::getHistory
 * @return
 */
int SplitDialog::getHistory(){
	return ui->historyframes->value();
}

/**
 * @brief SplitDialog::getvarThreshold
 * @return
 */
int SplitDialog::getvarThreshold(){
	return ui->varThreshold->value();
}

/**
 * @brief SplitDialog::getbShadowDetection
 * @return
 */
bool SplitDialog::getbShadowDetection(){
	return ui->bShadowDetection->checkState();
}

/**
 * @brief SplitDialog::on_maxseconds_valueChanged
 * @param arg1
 */
void SplitDialog::on_maxseconds_valueChanged(int arg1)
{
	ui->maxframes->setValue(arg1*fps);
}

/**
 * @brief SplitDialog::on_minseconds_valueChanged
 * @param arg1
 */
void SplitDialog::on_minseconds_valueChanged(int arg1)
{
	ui->minframes->setValue(arg1*fps);
}

/**
 * @brief SplitDialog::on_maxframes_valueChanged
 * @param arg1
 */
void SplitDialog::on_maxframes_valueChanged(int arg1)
{
	ui->maxseconds->setValue(arg1/fps);
}

/**
 * @brief SplitDialog::on_minframes_valueChanged
 * @param arg1
 */
void SplitDialog::on_minframes_valueChanged(int arg1)
{
	ui->minseconds->setValue(arg1/fps);
}

/**
 * @brief SplitDialog::on_historyseconds_valueChanged
 * @param arg1
 */
void SplitDialog::on_historyseconds_valueChanged(int arg1)
{
	ui->historyframes->setValue(arg1*fps);
}

/**
 * @brief SplitDialog::on_historyframes_valueChanged
 * @param arg1
 */
void SplitDialog::on_historyframes_valueChanged(int arg1)
{
	ui->historyseconds->setValue(arg1/fps);
}
