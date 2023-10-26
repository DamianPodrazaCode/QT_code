#include "task.h"

Task::Task(QObject *parent) : QThread{parent} {
}

Task::~Task() {
}

void Task::run() {
    qInfo() << QThread::currentThread();
    while (1) {
        emit update_label(QString::number((*count)++));
        QThread::msleep(100);
    }
}
