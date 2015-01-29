#include "mainwindow.h"
#include <QApplication>
#include "cubie.h"
#include <QStyleFactory>
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QApplication::setStyle("Fusion");
	MainWindow w;
	w.show();

	return a.exec();
}
