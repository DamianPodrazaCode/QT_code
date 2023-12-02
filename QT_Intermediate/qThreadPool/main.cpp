#include <QCoreApplication>
#include <QDebug>
#include <QThread>
#include <QThreadPool>>
#include "task.h"

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    QThread::currentThread()->setObjectName("main");
    qInfo() << QThread::currentThread();
    qInfo() << QThreadPool::globalInstance()->maxThreadCount();


    return a.exec();
}
