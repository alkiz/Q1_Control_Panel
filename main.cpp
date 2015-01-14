#include "mainwindow.h"
#include <QApplication>
#include "cubie.h"
#include <QStyleFactory>
#include <SDL.h>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setStyle("Fusion");
    MainWindow w;
    w.show();

    //foreach (QString it, QStyleFactory::keys()) {
    //        qDebug() << it << "\n";
    //   }
    return a.exec();
}
