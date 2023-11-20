#include "cast2.h"

Cast2::Cast2(QObject *parent) : Cast1{parent} {
    qInfo() << this << Q_FUNC_INFO;
}

Cast2::~Cast2() {
    qInfo() << this << Q_FUNC_INFO;
}

void Cast2::metoda3() {
    qInfo() << this << Q_FUNC_INFO;
}
