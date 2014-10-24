#ifndef SPLITDIALOG_HPP
#define SPLITDIALOG_HPP

#include <QDialog>

// the following are in seconds
#define DEFAULT_MAX_TIME 5
#define DEFAULT_MIN_TIME 2
#define DEFAULT_HIST	 20

namespace Ui {
class SplitDialog;
}

/**
 * @brief Class to control the split settings input menu.
 */
class SplitDialog : public QDialog
{
	Q_OBJECT

public:
	explicit SplitDialog(QWidget *parent = 0);
	~SplitDialog();

	// Set
	void setFPS(unsigned int FPS);

	// Get
	int getThreshold();
	int getMaxFrames();
	int getMinFrames();
	int getHistory();
	int getvarThreshold();
	bool getbShadowDetection();

private slots:
	void on_maxseconds_valueChanged(int arg1);

	void on_minseconds_valueChanged(int arg1);

	void on_maxframes_valueChanged(int arg1);

	void on_minframes_valueChanged(int arg1);

	void on_historyseconds_valueChanged(int arg1);

	void on_historyframes_valueChanged(int arg1);

private:
	/**
	 * @brief ui
	 */
	Ui::SplitDialog *ui;

	/**
	 * @brief fps
	 */
	unsigned int fps;
};

#endif // SPLITDIALOG_HPP
