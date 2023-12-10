#ifndef WORKER_H
#define WORKER_H

#include <QDateTime>
#include <QDebug>
#include <QNetworkDatagram>
#include <QObject>
#include <QTimer>
#include <QUdpSocket>
#include <QThread>
#include <QEventLoop>

class Worker : public QObject {
    Q_OBJECT

public:
    explicit Worker(QObject *parent = nullptr);
    ~Worker();
signals:

public slots:
    void start();
    void stop();
    void timeout();
    void readReady();
    void broadcast();

private:
    QUdpSocket *socket;
    QTimer *timer;
    QEventLoop *loop;
    quint16 port = 2020;
    int counter = 0;
};

#endif // WORKER_H
