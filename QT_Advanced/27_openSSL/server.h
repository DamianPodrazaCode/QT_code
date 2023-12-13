#ifndef SERVER_H
#define SERVER_H

#include <QAbstractSocket>
#include <QDebug>
#include <QMetaEnum>
#include <QObject>
#include <QSslSocket>
#include <QTcpServer>
#include <QTcpSocket>

class Server : public QTcpServer {
    Q_OBJECT
  public:
    explicit Server(QObject *parent = nullptr);

    void setCert(QString value);
    void setKey(QString value);

  signals:

  public slots:
    void disconnected();
    void readyRead();
    void encrypted();
    void encryptedBytesWritten(qint64 written);
    void modeChanged(QSslSocket::SslMode mode);
    void peerVerifyError(const QSslError &error);
    void sslErrors(const QList<QSslError> &errors);
    void socketError(QAbstractSocket::SocketError err);

    // QTcpServer interface
  protected:
    void incomingConnection(qintptr handle) Q_DECL_OVERRIDE;

  private:
    QString certPath;
    QString keyPath;
};

#endif // SERVER_H
