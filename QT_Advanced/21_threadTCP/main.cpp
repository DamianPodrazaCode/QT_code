#include "client.h"
#include <QCoreApplication>
#include <QThread>

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);
    QThread::currentThread()->setObjectName("Main thread");

    QThread thread;
    thread.setObjectName("Client thread");

    // Client client;
    // client.connectToHost("www.httpbin.org", 80);
    // client.connectToHost("www.voidrealms.com", 80);

    Client *client = new Client();
    client->moveToThread(&thread);
    QObject::connect(&thread, &QThread::started, client, &Client::run);
    client->setHost("voidrealms.com");
    client->setPort(80);

    thread.start();

    qInfo() << "end main";
    return a.exec();
}
