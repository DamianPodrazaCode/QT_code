#include "test.h"

test::test(QObject *parent) : QObject{parent} {
    qInfo() << this << "konstruktor" << Q_FUNC_INFO;
}

test::~test() {
    qInfo() << this << "dekonstruktor" << Q_FUNC_INFO;
}

void test::start() {
    qInfo() << this << "metoda start" << Q_FUNC_INFO;
}
