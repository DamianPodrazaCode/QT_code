#include "task.h"

Task::Task(QObject *parent) : QObject{parent} {
    qInfo() << "Konstruktor" << this << " w " << QThread::currentThread();
}

Task::~Task() {
    qInfo() << "Dekonstruktor" << this << " w " << QThread::currentThread();
}

void Task::run() {
    QThread *thread = QThread::currentThread();
    qInfo() << "run" << this << " w " << thread;
}
