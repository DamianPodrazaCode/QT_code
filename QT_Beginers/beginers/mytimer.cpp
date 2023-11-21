#include "mytimer.h"

MyTimer::MyTimer(QObject *parent) : QObject{parent} {
    timer = new QTimer();
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(timeTick()));
}

MyTimer::~MyTimer() {
}

void MyTimer::start() {
    timer->start(500);
}

void MyTimer::timeTick() {
    qInfo() << this << Q_FUNC_INFO;
}
