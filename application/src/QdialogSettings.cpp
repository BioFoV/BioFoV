#include "QdialogSettings.hpp"
#include "ui_qdialogsettings.h"

/**
 * @brief QdialogSettings::QdialogSettings
 * @param parent
 */
QdialogSettings::QdialogSettings(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::QdialogSettings)
{
	ui->setupUi(this);
	settingsFile = NULL;

	// check if Linux/Mac
	QString uname = qgetenv("USER");
	if (uname.isEmpty()) // if not then it is windows
		uname = qgetenv("USERNAME");

	QDir cacheFolder(QDir::tempPath() + QDir::separator() + \
					 "forensics-" + uname);

	ui->cacheDir->setText(cacheFolder.path());
	if(!cacheFolder.exists()){
		cacheFolder.mkpath(".");
	}
	ui->haarDir->setText(QDir::homePath());
}

/**
 * @brief QdialogSettings::~QdialogSettings
 */
QdialogSettings::~QdialogSettings()
{
	delete ui;
}

/**
 * @brief QdialogSettings::on_cacheButton_clicked
 */
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

/**
 * @brief QdialogSettings::on_haarButton_clicked
 */
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

/**
 * @brief QdialogSettings::getHaarDir
 * @return
 */
QString QdialogSettings::getHaarDir(){
	return ui->haarDir->text();
}

/**
 * @brief QdialogSettings::getCacheDir
 * @return
 */
QString QdialogSettings::getCacheDir(){
	return ui->cacheDir->text();
}

/**
 * @brief QdialogSettings::getUseGPU
 * @return
 */
bool QdialogSettings::getUseGPU(){
	return ui->useGPU->isChecked();
}

/**
 * @brief QdialogSettings::justSaveSettings
 */
void QdialogSettings::justSaveSettings(){
	settingsFile->setValue("CacheDir",getCacheDir());
	settingsFile->setValue("HaarDir",getHaarDir());
	settingsFile->setValue("UseGPU",getUseGPU());
}

/**
 * @brief QdialogSettings::saveSettings
 */
void QdialogSettings::saveSettings(){
	if (settingsFile == NULL) {
		saveSettingsAs();
		return;
	}

	justSaveSettings();
}

/**
 * @brief QdialogSettings::saveSettingsAs
 */
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

/**
 * @brief QdialogSettings::loadSettings
 */
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
