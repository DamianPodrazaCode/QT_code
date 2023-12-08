#include "client.h"

Client::Client(QObject *parent) : QObject{parent} {
    connect(&socket, &QTcpSocket::connected, this, &Client::connected);
    connect(&socket, &QTcpSocket::disconnected, this, &Client::disconnected);
    connect(&socket, &QTcpSocket::stateChanged, this, &Client::stateChanged);
    connect(&socket, &QTcpSocket::readyRead, this, &Client::readRead);
    connect(&socket, &QTcpSocket::errorOccurred, this, &Client::error);
}

void Client::connectToHost(QString host, quint16 port) {
    if (socket.isOpen())
        disconnect();

    qInfo() << "connecting to: " << host << " : " << port;
    socket.connectToHost(host, port);
    // socket.waitForConnected();
}

void Client::disconnect() {
    socket.close();
    socket.waitForDisconnected();
}

void Client::connected() {
    qInfo() << "Connected:";
    qInfo() << "Send:";
    socket.write("HELLO\r\n");
}

void Client::disconnected() {
    qInfo() << "Disconnected:";
}

void Client::error(QAbstractSocket::SocketError socketError) {
    qInfo() << "ERROR : " << socketError << " " << socket.errorString();
}

void Client::stateChanged(QAbstractSocket::SocketState socketState) {
    // zajebista rzecz która zamienia enumy zwracane w postaci liczba na nazwy używane w qt
    QMetaEnum metaenum = QMetaEnum::fromType<QAbstractSocket::SocketState>();
    qInfo() << "State" << metaenum.valueToKey(socketState);
}

void Client::readRead() {
    qInfo() << "data from : " << sender() << "bytes : " << socket.bytesAvailable();
    qInfo() << "Data : " << socket.readAll();
}
