#include <QCoreApplication>
#include <QDateTime>
#include <QDebug>
#include <QNetworkDatagram>
#include <QUdpSocket>

bool bind(QUdpSocket *socket, quint16 port) {
    if (socket->bind(port, QUdpSocket::ShareAddress))
        return true;
    qInfo() << socket->errorString();
    return false;
}

void send(QUdpSocket *socket, quint16 port) {
    qInfo() << "sending ...";
    QString date = QDateTime::currentDateTime().toString();
    QByteArray data = date.toLatin1();

    QNetworkDatagram datagram(data, QHostAddress::Broadcast, port);
    if (socket->writeDatagram(datagram) <= 0)
        qInfo() << socket->errorString();
}

void read(QUdpSocket *socket) {
    qInfo() << "reading ...";
    socket->waitForReadyRead(60000);
    while (socket->hasPendingDatagrams()) {
        QNetworkDatagram datagram = socket->receiveDatagram();
        qInfo() << datagram.data();
    }
}

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    QUdpSocket broadcaster;
    QUdpSocket client;
    quint16 port = 4569;

    qInfo() << "binding ...";
    if (bind(&client, port)) {
        send(&broadcaster, port);
        read(&client);
    } else {
        qInfo() << "could not bind client";
    }

    return a.exec();
}
