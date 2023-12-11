#include "mainwindow.h"

#include <QApplication>
#include <QNetworkProxy>
#include <QNetworkDatagram>
// test
//test2

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
