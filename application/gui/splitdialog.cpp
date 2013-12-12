#include "splitdialog.hpp"
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

int SplitDialog::getThreshold(){
    return ui->threshSlider->value();
}

int SplitDialog::getMaxFrames(){
    return ui->maxframes->value();
}

int SplitDialog::getMinFrames(){
    return ui->minframes->value();
}
