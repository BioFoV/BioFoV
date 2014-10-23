#ifndef ABOUT_H
#define ABOUT_H

#include <QDialog>

namespace Ui {
class About;
}

/**
 * @brief The About class
 */
class About : public QDialog
{
	Q_OBJECT

public:
	explicit About(QWidget *parent = 0);
	~About();

private:
	/**
	 * @brief ui
	 */
	Ui::About *ui;
};

#endif // ABOUT_H
