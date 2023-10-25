#include "task.h"
#include <QCoreApplication>
#include <QDebug>
#include <QScopedPointer>
#include <QThread>

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    qInfo() << "Start work" << QThread::currentThread();

    Task *task = new Task(); // utworzenie nowego zadania z nadpisaniem metody run
    task->start(); // uruchomienie nowego zadania

    qInfo() << "End work" << QThread::currentThread();

    QThread::msleep(5000); //zatrzymanie na 5 sec. a w tle działa task
    task->terminate(); // zabicie taska
    delete task; // usunięcie z pamięci taska

    return a.exec();
}
