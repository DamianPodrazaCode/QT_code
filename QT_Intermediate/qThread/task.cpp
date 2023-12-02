#include "task.h"

Task::Task(QObject *parent) : QObject{parent} {
    qInfo() << "Konstruktor " << this << " w " << QThread::currentThread();
}

Task::~Task() {
    qInfo() << "Dekonstruktor " << this << " w " << QThread::currentThread();
}

void Task::work() {
    QThread *thread = QThread::currentThread();
    qInfo() << "work tread -> " << thread;
    doSomting();
}

void Task::doSomting() {
    qInfo() << "somting -> " <<  QThread::currentThread();
}
