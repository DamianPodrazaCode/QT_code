#ifndef SERVER_H
#define SERVER_H

#include "client.h"
#include <QDebug>
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QThread>
#include <QThreadPool>

class Server : public QTcpServer {
    Q_OBJECT

public:
    explicit Server(QObject *parent = nullptr);
    ~Server();

signals:

public slots:
    void start(quint16 port);
    void quit();

private:
    QThreadPool pool;

    // QTcpServer interface
protected:
    void incomingConnection(qintptr handle) Q_DECL_OVERRIDE;
};

#endif // SERVER_H
