#include "mainwindow.h"

#include <QApplication>
#include <QNetworkProxy>
#include <QNetworkDatagram>
// test

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
