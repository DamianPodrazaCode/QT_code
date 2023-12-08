#ifndef CLIENT_H
#define CLIENT_H

#include <QAbstractSocket>
#include <QDebug>
#include <QMetaEnum>
#include <QNetworkProxy>
#include <QObject>
#include <QTcpSocket>

class Client : public QObject {
    Q_OBJECT

public:
    explicit Client(QObject *parent = nullptr);

signals:

public slots:
    void connectToHost(QString host, quint16 port);
    void disconnect();

private slots:
    void connected();
    void disconnected();
    void error(QAbstractSocket::SocketError socketError);
    void stateChanged(QAbstractSocket::SocketState socketState);
    void readRead();

private:
    QTcpSocket socket;
};

#endif // CLIENT_H
