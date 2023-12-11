#ifndef CLIENT_H
#define CLIENT_H

#include <QDebug>
#include <QObject>
#include <QRunnable>
#include <QTcpSocket>
#include <QThread>

class Client : public QObject, public QRunnable {
    Q_OBJECT

public:
    explicit Client(QObject *parent = nullptr, qintptr handle = 0);

signals:

    // QRunnable interface

public:
    void run();

private:
    qintptr handle;
};

#endif // CLIENT_H
