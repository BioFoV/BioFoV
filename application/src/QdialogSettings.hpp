#ifndef QDIALOGSETTINGS_HPP
#define QDIALOGSETTINGS_HPP

#include <QDialog>
#include <QFileDialog>
#include <QSettings>

namespace Ui {
class QdialogSettings;
}

/**
 * @brief The QdialogSettings class
 */
class QdialogSettings : public QDialog
{
	Q_OBJECT

public:
	explicit QdialogSettings(QWidget *parent = 0);
	~QdialogSettings();

	QString getCacheDir();
	QString getHaarDir();
	bool getUseGPU();

	void setHaarDir(QString newHaarDir);
	void setCacheDir(QString newHaarDir);

public slots:
	void saveSettings();
	void saveSettingsAs();
	void loadSettings();

private slots:
	void on_cacheButton_clicked();

	void on_haarButton_clicked();

private:
	/**
	 * @brief ui
	 */
	Ui::QdialogSettings *ui;

	/**
	 * @brief settingsFile
	 */
	QSettings *settingsFile;

	void justSaveSettings();
};

#endif // QDIALOGSETTINGS_HPP
