#ifndef CLIENT_H
#define CLIENT_H

#include <QAbstractSocket>
#include <QDebug>
#include <QMetaEnum>
#include <QNetworkProxy>
#include <QObject>
#include <QTcpSocket>
#include <QThread>

class Client : public QObject {
    Q_OBJECT

public:
    explicit Client(QObject *parent = nullptr);
    ~Client();
    QString host() const;
    void setHost(const QString& newHost);

    quint16 port() const;
    void setPort(quint16 newPort);

signals:

public slots:
    void connectToHost(QString host, quint16 port);
    void disconnect();
    void run();

private slots:
    void connected();
    void disconnected();
    void error(QAbstractSocket::SocketError socketError);
    void stateChanged(QAbstractSocket::SocketState socketState);
    void readRead();

private:
    QTcpSocket socket;
    QString m_host;
    quint16 m_port;
};

#endif // CLIENT_H
