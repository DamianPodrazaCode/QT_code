#include "task.h"
#include <QCoreApplication>
#include <QThread>
#include <QScopedPointer>
#include <QDebug>

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    // thread main
    QThread *thread = QThread::currentThread();
    thread->setObjectName("main");
    //qInfo() << thread;

    // QObject move to thread
    // Thread
    QThread worker; // objekt thread
    worker.setObjectName("worker");
    // Task
    QScopedPointer<Task> t(new Task()); // wskaźnik auto delete
    Task *task = t.data(); // obiekt taska

    task->moveToThread(&worker); // przypisanie obiektu do taska

    // połaczenie taska do threada i uruchomienie
    worker.connect(&worker, &QThread::started, task, &Task::work);
    worker.start();

    qInfo() << "koniec" << QThread::currentThread();

    return a.exec();
}
