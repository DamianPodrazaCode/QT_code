#include "server.h"
#include <QCoreApplication>

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    Server server;
    server.setKey("/home/zombie/GitHub/QT_code/QT_Advanced/27_openSSL/OpenSSL/server.key");
    server.setCert("/home/zombie/GitHub/QT_code/QT_Advanced/27_openSSL/OpenSSL/server.crt");

    if (!server.listen(QHostAddress::Any, 2020)) {
        qInfo() << server.errorString();
    } else {
        qInfo() << "Listening on " << server.serverAddress() << ":" << server.serverPort();
    }

    return a.exec();
}
