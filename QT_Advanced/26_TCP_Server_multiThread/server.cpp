#include "server.h"

Server::Server(QObject *parent) : QTcpServer{parent} {
    pool.setMaxThreadCount(200);
    qInfo() << "Thread max: " << pool.maxThreadCount();
}

Server::~Server() {
}

void Server::start(quint16 port) {
    qInfo() << this << " start " << QThread::currentThread();
    if (this->listen(QHostAddress::Any, port)) {
        qInfo() << " Server staart on " << port;
    } else {
        qCritical() << this->errorString();
    }
}

void Server::quit() {
    this->close();
    qInfo() << "Server stopped!";
}

void Server::incomingConnection(qintptr handle) {
    qInfo() << "Incomming connection " << handle << " on " << QThread::currentThread();
    Client *client = new Client(nullptr, handle);
    client->setAutoDelete(true);
    pool.start(client);
}
