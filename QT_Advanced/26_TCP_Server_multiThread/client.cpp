#include "client.h"

Client::Client(QObject *parent, qintptr handle) : QObject{parent} {
    this->handle = handle;
}

void Client::run() {
    qInfo() << this << "run" << QThread::currentThread();
    QTcpSocket *socket = new QTcpSocket(nullptr);
    if (!socket->setSocketDescriptor(handle)) {
        qCritical() << socket->errorString();
        delete socket;
        return;
    }
    socket->waitForReadyRead();

    QByteArray request = socket->readAll();
    qInfo() << "Request Lenght: " << request.length();

    QByteArray data("Hello World!!!");
    QByteArray respone;
    respone.append("HTTP/1.1 200 OK\r\n");
    respone.append("Content-Type: text/plain\r\n");
    respone.append("Content-Lenght: " + QString::number(data.length()).toUtf8() + "\r\n");
    respone.append("Connection: close\r\n");
    respone.append("\r\n");
    respone.append(data);

    socket->write(respone);
    socket->waitForBytesWritten();
    socket->close();
    socket->deleteLater();

    qInfo() << this << "done" << QThread::currentThread();
}
