#include "worker.h"

Worker::Worker(QObject *parent) : QObject{parent} {
    connect(&timer, &QTimer::timeout, this, &Worker::timeout);
    connect(&socket, &QUdpSocket::readyRead, this, &Worker::readReady);
    timer.setInterval(1000);
}

void Worker::start() {
}

void Worker::stop() {
}

void Worker::timeout() {
}

void Worker::readReady() {
}

void Worker::broadcast() {
}
