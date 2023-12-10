#include <QCoreApplication>
#include "worker.h"

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    qInfo() << "**** Start main ****";
    QThread::currentThread()->setObjectName("main");

    Worker worker;
    worker.start();

    qInfo() << "**** End main ****";

    return a.exec();
}
