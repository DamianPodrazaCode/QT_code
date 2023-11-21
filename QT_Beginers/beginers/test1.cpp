#include "test1.h"

Test1::Test1(QObject *parent) : QObject{parent} {
    qInfo() << this << "konstruktor" << Q_FUNC_INFO;
}

Test1::~Test1() {
    qInfo() << this << "destruktor" << Q_FUNC_INFO;
}

void Test1::metoda1() {
    qInfo() << this << Q_FUNC_INFO;
}

void Test1::timerTick() {
    qInfo() << this << Q_FUNC_INFO;
}
