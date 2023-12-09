#include <QCoreApplication>
#include "client.h"

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    Client client;
    client.connectToHost("httpbin.org", 443); // SSL - OpenSSL

    return a.exec();
}
