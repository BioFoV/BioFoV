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

void QdialogSettings::on_cacheButton_clicked()
{
    QFileDialog getDirDialog(this);
    getDirDialog.setDirectory(QDir::homePath());
    getDirDialog.setFileMode(QFileDialog::Directory);
    getDirDialog.setOption(QFileDialog::ShowDirsOnly);
    getDirDialog.setAcceptMode(QFileDialog::AcceptOpen);

    QStringList dirNames;

    if(getDirDialog.exec()) {
        dirNames = getDirDialog.selectedFiles();

        foreach (QString dirName, dirNames) {
            ui->cacheDir->setText(dirName);
        }
    }
}

void QdialogSettings::on_haarButton_clicked()
{
    QFileDialog getDirDialog(this);
    getDirDialog.setDirectory(QDir::homePath());
    getDirDialog.setFileMode(QFileDialog::Directory);
    getDirDialog.setOption(QFileDialog::ShowDirsOnly);
    getDirDialog.setAcceptMode(QFileDialog::AcceptOpen);

    QStringList dirNames;

    if(getDirDialog.exec()) {
        dirNames = getDirDialog.selectedFiles();

        foreach (QString dirName, dirNames) {
            ui->haarDir->setText(dirName);
        }
    }
}

QString QdialogSettings::getHaarDir(){
    return ui->haarDir->text();
}

QString QdialogSettings::getCacheDir(){
    return ui->cacheDir->text();
}
