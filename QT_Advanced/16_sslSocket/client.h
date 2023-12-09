#ifndef CLIENT_H
#define CLIENT_H

#include <QAbstractSocket>
#include <QDebug>
#include <QMetaEnum>
#include <QNetworkProxy>
#include <QObject>
#include <QTcpSocket>
#include <QSslSocket>
#include <QSslPreSharedKeyAuthenticator>

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
    // SSL
    void encrypted();
    void encryptedBytesWritten(qint64 written);
    void modeChanged(QSslSocket::SslMode mode);
    void peerVerifyError(const QSslError &error);
    void preSharedKeyAutenticationRequired(QSslPreSharedKeyAuthenticator *autenticator);
    void sslErrors(const QList<QSslError> &errors);

private:
    QSslSocket socket;
};

#endif // CLIENT_H
