#include <QCoreApplication>
#include <QSemaphore>
#include <QThread>
#include "worker.h"


int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    QList<int> values;
    values.resize(10);
    values.fill(0);

    QSemaphore sema(values.size());
    qInfo() << values;

    QThread thread1;
    QThread thread2;
    thread1.setObjectName("Thread 1");
    thread2.setObjectName("Thread 2");

    Worker work1(&sema, &values);
    Worker work2(&sema, &values);
    work1.moveToThread(&thread1);
    work2.moveToThread(&thread2);

    QObject::connect(&thread1, SIGNAL(started()), &work1, SLOT(run()));
    QObject::connect(&thread2, SIGNAL(started()), &work2, SLOT(run()));

    thread1.start();
    thread2.start();

    return a.exec();
}
