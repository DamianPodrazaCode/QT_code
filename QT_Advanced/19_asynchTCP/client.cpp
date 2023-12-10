#include "client.h"

Client::Client(QObject *parent) : QObject{parent} {
    connect(&socket, &QTcpSocket::connected, this, &Client::connected);
    connect(&socket, &QTcpSocket::disconnected, this, &Client::disconnected);
    connect(&socket, &QTcpSocket::stateChanged, this, &Client::stateChanged);
    connect(&socket, &QTcpSocket::readyRead, this, &Client::readRead);
    connect(&socket, &QTcpSocket::errorOccurred, this, &Client::error);

// #define GO_PROXY
#ifdef GO_PROXY
    // proxy - od strony serwera będzie widoczny adres proxy a nie mój publiczny
    // https://free-proxy-list.net/
    // https://httpbin.org/ - fajny serwer do testowania działania na tcp
    QNetworkProxy proxy(QNetworkProxy::HttpProxy, "20.111.54.16", 80);

    // autoryzacja proxy jeżeli konieczna
    // proxy.setUser("user");
    // proxy.setPassword("pass");

    // dopięcie proxy do aplikacji
    QNetworkProxy::setApplicationProxy(proxy);
    // dopięcie proxy do soketu tcp
    socket.setProxy(proxy);
#endif
}

void Client::connectToHost(QString host, quint16 port) {
    qInfo() << Q_FUNC_INFO << QThread::currentThread();
    if (socket.isOpen())
        disconnect();
    qInfo() << "connecting to: " << host << " : " << port;
    socket.connectToHost(host, port);
}

void Client::disconnect() {
    socket.close();
    socket.waitForDisconnected();
}

void Client::connected() {
    qInfo() << "Connected:";
    qInfo() << "Send:";
    // socket.write("//get\r\n");

    QByteArray data;
    data.append("GET /get HTTP/1.1\r\n");
    data.append("User-Agent: Mozilla/4.0 (compatibile; MSIE 8.0; Windows NT 6.0; Trident/4.0)\r\n");
    data.append("Host: local\r\n");
    data.append("Connection: Close\r\n");
    data.append("\r\n");
    socket.write(data);
    socket.waitForBytesWritten();
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
