#ifndef CALIBRATIONDIALOG_HPP
#define CALIBRATIONDIALOG_HPP

// OpenCV
#ifndef OPENCV_INC
#define OPENCV_INC
#include <opencv2/opencv.hpp>
#endif

#include <QDialog>

namespace Ui {
class CalibrationDialog;
}

/**
 * @brief The CalibrationDialog class
 */
class CalibrationDialog : public QDialog
{
	Q_OBJECT

public:
	explicit CalibrationDialog(QWidget *parent = 0);
	~CalibrationDialog();

	int getNBoards();
	int getFrameStep();
	int getWidth();
	int getHeight();
	int getIterations();
	unsigned int getFlags();

private:
	/**
	 * @brief ui
	 */
	Ui::CalibrationDialog *ui;
};

#endif // CALIBRATIONDIALOG_HPP
