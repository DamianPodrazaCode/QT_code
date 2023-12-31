#include "server.h"

Server::Server(QObject *parent) : QObject{parent} {
    connect(&server, &QTcpServer::newConnection, this, &Server::newConnection);
}

void Server::start() {
    if (!server.listen(QHostAddress::Any, 2020)) {
        qWarning() << server.errorString();
        return;
    }

    qInfo() << "Listening ...";
}

void Server::quit() {
    server.close();
}

void Server::newConnection() {
    QTcpSocket *socket = server.nextPendingConnection();
    connect(socket, &QTcpSocket::disconnected, this, &Server::disconnected);
    connect(socket, &QTcpSocket::readyRead, this, &Server::readyRead);
    qInfo() << "Connected" << socket;
}

void Server::disconnected() {
    QTcpSocket *socket = qobject_cast<QTcpSocket *>(sender());
    qInfo() << "disonnected" << socket;
    qInfo() << "Parent" << socket->parent();
    socket->deleteLater();
}

void Server::readyRead() {
    QTcpSocket *socket = qobject_cast<QTcpSocket *>(sender());
    qInfo() << "readyRead" << socket;
    qInfo() << socket->readAll();
}
