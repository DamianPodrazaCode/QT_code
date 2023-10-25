#include "task.h"

Task::Task(QObject *parent) : QThread{parent} {
    qInfo() << "konstr " << this << QThread::currentThread();
}

Task::~Task() {
    qInfo() << "dekonstr " << this << QThread::currentThread();
}

void Task::run() {
    //    QThread *thread = QThread::currentThread();
    //    qInfo() << "thread" << thread;
    while (1) {
        qInfo() << "task";
        QThread::msleep(500);
    }
}
