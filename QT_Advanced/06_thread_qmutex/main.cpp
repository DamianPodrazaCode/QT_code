#include "counter.h"
#include <QCoreApplication>
#include <QDebug>
#include <QMutex>
#include <QThread>
#include <QThreadPool>

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    QThread::currentThread()->setObjectName("main");
    qInfo() << "main start" << QThread::currentThread();

    QThreadPool *pool = QThreadPool::globalInstance();
    qInfo() << pool->maxThreadCount() << " - max threads.";

    QMutex mutex;
    int value = 0;

    for (int i = 0; i < 100; ++i) {
        Counter *c = new Counter(&mutex, &value);
        c->setAutoDelete(true);
        pool->start(c);
    }

    return a.exec();
}
