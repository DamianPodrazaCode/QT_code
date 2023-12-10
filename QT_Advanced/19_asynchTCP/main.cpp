#include <QCoreApplication>
#include <QThread>
#include "client.h"

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);
    QThread::currentThread()->setObjectName("main");

    Client client;
    //client.connectToHost("www.httpbin.org", 80);

    qInfo() << "end main";
    return a.exec();
}
