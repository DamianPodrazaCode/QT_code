#include "counter.h"
#include <QCoreApplication>
#include <QDebug>
#include <QThread>
#include <QThreadPool>

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    QThread::currentThread()->setObjectName("main");
    qInfo() << "main start" << QThread::currentThread();

    QThreadPool *pool = QThreadPool::globalInstance();
    qInfo() << pool->maxThreadCount() << " - max threads.";

    for (int i = 0; i < 100; ++i) {
        Counter *c = new Counter();
        c->setAutoDelete(true);
        pool->start(c);
    }

    return a.exec();
}
