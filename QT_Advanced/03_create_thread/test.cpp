#include "test.h"

Test::Test(QObject *parent) : QObject{parent} {
}

Test::~Test() {
}

void Test::run() {
    qInfo() << "Test start" << QThread::currentThread();
    m_timer.singleShot(3000, this, &Test::timeout);
    qInfo() << "Test end" << QThread::currentThread();
}

void Test::timeout() {
    qInfo() << "timeout" << QThread::currentThread();
}
