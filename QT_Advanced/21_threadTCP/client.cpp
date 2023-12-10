#include "client.h"

Client::Client(QObject *parent) : QObject{parent} {


    m_host = "";
    m_port = 0;

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

Client::~Client() {
    qInfo() << Q_FUNC_INFO << QThread::currentThread();
    qInfo() << "destruktor";
}

void Client::connectToHost(QString host, quint16 port) {
    qInfo() << Q_FUNC_INFO << QThread::currentThread();
    if (socket->isOpen())
        disconnect();
    qInfo() << "connecting to: " << host << " : " << port;
    socket->connectToHost(host, port);
}

void Client::disconnect() {
    qInfo() << Q_FUNC_INFO << QThread::currentThread();
    socket->close();
    // socket.waitForDisconnected();
}

void Client::run() {
    // tutaj startuje wątek Client-a
    qInfo() << Q_FUNC_INFO << QThread::currentThread();

    socket = new QTcpSocket(this);
    connect(socket, &QTcpSocket::connected, this, &Client::connected);
    connect(socket, &QTcpSocket::disconnected, this, &Client::disconnected);
    connect(socket, &QTcpSocket::stateChanged, this, &Client::stateChanged);
    connect(socket, &QTcpSocket::readyRead, this, &Client::readRead);
    connect(socket, &QTcpSocket::errorOccurred, this, &Client::error);

    connectToHost(m_host, m_port);
    socket->waitForDisconnected(); // metoda blokująca
    qInfo() << "complete";
    deleteLater();

}

void Client::connected() {
    qInfo() << Q_FUNC_INFO << QThread::currentThread();
    qInfo() << "Connected:";
    qInfo() << "Send:";
    socket->write("HELLO\r\n");

    // QByteArray data;
    // data.append("GET /get HTTP/1.1\r\n");
    // data.append("User-Agent: Mozilla/4.0 (compatibile; MSIE 8.0; Windows NT 6.0; Trident/4.0)\r\n");
    // data.append("Host: local\r\n");
    // data.append("Connection: Close\r\n");
    // data.append("\r\n");
    // socket->write(data);
    // socket.waitForBytesWritten();
}

void Client::disconnected() {
    qInfo() << Q_FUNC_INFO << QThread::currentThread();
    qInfo() << "Disconnected:";
}

void Client::error(QAbstractSocket::SocketError socketError) {
    qInfo() << Q_FUNC_INFO << QThread::currentThread();
    qInfo() << "ERROR : " << socketError << " " << socket->errorString();
}

void Client::stateChanged(QAbstractSocket::SocketState socketState) {
    // zajebista rzecz która zamienia enumy zwracane w postaci liczba na nazwy używane w qt
    QMetaEnum metaenum = QMetaEnum::fromType<QAbstractSocket::SocketState>();
    qInfo() << "State" << metaenum.valueToKey(socketState);
}

void Client::readRead() {
    qInfo() << Q_FUNC_INFO << QThread::currentThread();
    qInfo() << "data from : " << sender() << "bytes : " << socket->bytesAvailable();
    qInfo() << "Data : " << socket->readAll();
}

quint16 Client::port() const {
    return m_port;
}

void Client::setPort(quint16 newPort) {
    m_port = newPort;
}

QString Client::host() const {
    return m_host;
}

void Client::setHost(const QString& newHost) {
    m_host = newHost;
}
