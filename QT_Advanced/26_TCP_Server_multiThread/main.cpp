//https://www.joedog.org/siege-home/
// siege -c 10 127.0.0.1:2020

#include <QCoreApplication>
//#include "client.h"
#include "server.h"

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    Server server;
    server.start(2020);

    return a.exec();
}
