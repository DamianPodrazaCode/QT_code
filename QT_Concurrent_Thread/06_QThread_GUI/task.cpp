#include "task.h"

Task::Task(QObject *parent) : QThread{parent} {
    qInfo() << "konstr" << this;
}

Task::~Task() {
    qInfo() << "dekonstr" << this;
}

void Task::run() {
    qInfo() << QThread::currentThread();
    while (1) {
        emit update_label(QString::number((*count)++));
        QThread::msleep(1);
    }
}
