#include <QCoreApplication>
#include <QThread>
#include "worker.h"

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    qInfo() << "**** Start main ****";
    QThread::currentThread()->setObjectName("Main Thread");

    QThread thread;
    thread.setObjectName("Worker thread");
    Worker *worker = new Worker();
    worker->moveToThread(&thread);
    QObject::connect(&thread, &QThread::started, worker, &Worker::start);
    thread.start();

    qInfo() << "**** End main ****";

    return a.exec();
}
