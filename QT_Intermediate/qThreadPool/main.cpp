#include "task.h"
#include <QCoreApplication>
#include <QDebug>
#include <QThread>
#include <QThreadPool>

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    QThread::currentThread()->setObjectName("main");
    qInfo() << QThread::currentThread();
    qInfo() << QThreadPool::globalInstance()->maxThreadCount();

    for (int i = 0; i < 50; ++i) {
        Task *task = new Task();
        qInfo() << "task " << i;
        task->autoDelete();
        QThreadPool::globalInstance()->start(task);
    }

    return a.exec();
}
