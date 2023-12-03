#include <QCoreApplication>
#include <QThread>
#include "test.h"

// stworzenie osobnego objektu i uruchomienie go na osobnym wątku.

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    QThread::currentThread()->setObjectName("main");
    qInfo() << "main start" << QThread::currentThread();

    // wątek
    QThread worker;
    worker.setObjectName("worker");

    //obiekt
    Test test;
    test.moveToThread(&worker); //podpięcie do wątku

    // połączenie wątku z metodą obiektu
    QObject::connect(&worker, SIGNAL(started()), &test, SLOT(run()));
    worker.start();

    qInfo() << "main end" << QThread::currentThread();

    return a.exec();
}
