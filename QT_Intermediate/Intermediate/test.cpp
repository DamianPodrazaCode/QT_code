#include "test.h"

Test::Test(QObject *parent) : QObject{parent} {
    qInfo() << "konstruktor" << this << Q_FUNC_INFO;
}

Test::~Test() {
    qInfo() << "destruktor" << this << Q_FUNC_INFO;
}

void Test::work() {
    qInfo() << "worked" << this << Q_FUNC_INFO;
}
