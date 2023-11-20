#include "cast1.h"

Cast1::Cast1(QObject *parent) : QObject{parent} {
    qInfo() << this << Q_FUNC_INFO;
}

Cast1::~Cast1() {
    qInfo() << this << Q_FUNC_INFO;
}

void Cast1::metoda1() {
    qInfo() << this << Q_FUNC_INFO;
}

bool Cast1::metoda2() {
    qInfo() << this << Q_FUNC_INFO;
    return 0;
}
