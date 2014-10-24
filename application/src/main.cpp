#include "QwindowMain.hpp"
#include <QApplication>
#include <QLibraryInfo>
#include <QTranslator>

/**
 * @brief main
 * @param argc Number of arguments
 * @param argv Array of arguments
 * @return
 */
int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	QTranslator qtTranslator;
	qtTranslator.load("qt_" + QLocale::system().name(),
		 QLibraryInfo::location(QLibraryInfo::TranslationsPath));
	app.installTranslator(&qtTranslator);

	QTranslator myappTranslator;
	myappTranslator.load("myapp_" + QLocale::system().name());
	app.installTranslator(&myappTranslator);

	MainWindow w;
	w.show();

	return app.exec();
}
