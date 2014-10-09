#include "QdialogSettings.hpp"
#include "ui_qdialogsettings.h"

QdialogSettings::QdialogSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QdialogSettings)
{
    ui->setupUi(this);
    settingsFile = NULL;

    QDir cacheFolder(QDir::tempPath() + QDir::separator() + "forensics");
    ui->cacheDir->setText(cacheFolder.path());
    if(!cacheFolder.exists()){
        cacheFolder.mkpath(".");
    }
    ui->haarDir->setText(QDir::homePath());
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

bool QdialogSettings::getUseGPU(){
    return ui->useGPU->isChecked();
}

void QdialogSettings::justSaveSettings(){
    settingsFile->setValue("CacheDir",getCacheDir());
    settingsFile->setValue("HaarDir",getHaarDir());
    settingsFile->setValue("UseGPU",getUseGPU());
}

void QdialogSettings::saveSettings(){
    if (settingsFile == NULL) {
        saveSettingsAs();
        return;
    }

    justSaveSettings();
}

void QdialogSettings::saveSettingsAs(){
    QFileDialog getDirDialog(this);
    getDirDialog.setDirectory(QDir::homePath());
    getDirDialog.setAcceptMode(QFileDialog::AcceptSave);

    QStringList fileNames;

    if(getDirDialog.exec()) {
        fileNames = getDirDialog.selectedFiles();
        foreach (QString fileName, fileNames) {
            settingsFile = new QSettings(fileName, QSettings::IniFormat);
            justSaveSettings();
        }
    }
}

void QdialogSettings::loadSettings(){
    QFileDialog getDirDialog(this);
    getDirDialog.setDirectory(QDir::homePath());
    getDirDialog.setAcceptMode(QFileDialog::AcceptOpen);

    QStringList fileNames;

    if(getDirDialog.exec()) {
        fileNames = getDirDialog.selectedFiles();
        foreach (QString fileName, fileNames) {
            settingsFile = new QSettings(fileName, QSettings::IniFormat);

            ui->cacheDir->setText(
                settingsFile->value("CacheDir", "Uninitialized").toString());
            ui->haarDir->setText(
                settingsFile->value("HaarDir", "Uninitialized").toString());
            ui->useGPU->setChecked(
                settingsFile->value("UseGPU", false).toBool());
        }
    }
}
