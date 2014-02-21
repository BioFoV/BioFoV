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
    ui->maxframes->setValue(FPS * DEFAULT_MAX_TIME);
    ui->minframes->setValue(FPS * DEFAULT_MIN_TIME);
    ui->history->setValue(FPS * DEFAULT_HIST);
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
    return ui->history->value();
}

int SplitDialog::getvarThreshold(){
    return ui->varThreshold->value();
}

bool SplitDialog::getbShadowDetection(){
    return ui->bShadowDetection->checkState();
}
