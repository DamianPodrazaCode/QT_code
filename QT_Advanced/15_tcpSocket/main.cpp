#include <QCoreApplication>
#include "client.h"

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    Client client;
    client.connectToHost("www.voidrealms.com", 80);

    return a.exec();
}
