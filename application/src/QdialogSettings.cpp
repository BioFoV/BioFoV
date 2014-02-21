#include "QdialogSettings.hpp"
#include "ui_qdialogsettings.h"

QdialogSettings::QdialogSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QdialogSettings)
{
    ui->setupUi(this);
}

QdialogSettings::~QdialogSettings()
{
    delete ui;
}
