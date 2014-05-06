#include "QdialogSplit.hpp"
#include "ui_splitdialog.h"

SplitDialog::SplitDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SplitDialog)
{
    ui->setupUi(this);
}

SplitDialog::~SplitDialog()
{
    delete ui;
}

void SplitDialog::setFPS(unsigned int FPS) {
    fps = FPS;
    ui->maxframes->setValue(FPS * DEFAULT_MAX_TIME);
    ui->minframes->setValue(FPS * DEFAULT_MIN_TIME);
    ui->historyframes->setValue(FPS * DEFAULT_HIST);
}

int SplitDialog::getThreshold(){
    return ui->threshSlider->value();
}

int SplitDialog::getMaxFrames(){
    return ui->maxframes->value();
}

int SplitDialog::getMinFrames(){
    return ui->minframes->value();
}

int SplitDialog::getHistory(){
    return ui->historyframes->value();
}

int SplitDialog::getvarThreshold(){
    return ui->varThreshold->value();
}

bool SplitDialog::getbShadowDetection(){
    return ui->bShadowDetection->checkState();
}

void SplitDialog::on_maxseconds_valueChanged(int arg1)
{
    ui->maxframes->setValue(arg1*fps);
}

void SplitDialog::on_minseconds_valueChanged(int arg1)
{
    ui->minframes->setValue(arg1*fps);
}

void SplitDialog::on_maxframes_valueChanged(int arg1)
{
    ui->maxseconds->setValue(arg1/fps);
}

void SplitDialog::on_minframes_valueChanged(int arg1)
{
    ui->minseconds->setValue(arg1/fps);
}

void SplitDialog::on_historyseconds_valueChanged(int arg1)
{
    ui->historyframes->setValue(arg1*fps);
}

void SplitDialog::on_historyframes_valueChanged(int arg1)
{
    ui->historyseconds->setValue(arg1/fps);
}
