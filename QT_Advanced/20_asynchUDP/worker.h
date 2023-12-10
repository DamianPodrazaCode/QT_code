#ifndef WORKER_H
#define WORKER_H

#include <QDateTime>
#include <QDebug>
#include <QNetworkDatagram>
#include <QObject>
#include <QTimer>
#include <QUdpSocket>
#include <QThread>

class Worker : public QObject {
    Q_OBJECT

public:
    explicit Worker(QObject *parent = nullptr);

signals:

public slots:
    void start();
    void stop();
    void timeout();
    void readReady();
    void broadcast();

private:
    QUdpSocket socket;
    QTimer timer;
    quint16 port = 2020;
};

#endif // WORKER_H
