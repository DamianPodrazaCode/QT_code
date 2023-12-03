#include <QCoreApplication>
#include <QDebug>
#include <QThread>
#include "manager.h"

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    QThread::currentThread()->setObjectName("main");
    qInfo() << "main start" << QThread::currentThread();

    Manager m;

    return a.exec();
}
