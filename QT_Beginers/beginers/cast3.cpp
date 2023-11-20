#include "cast3.h"

Cast3::Cast3(QObject *parent) : QObject{parent} {
    qInfo() << this << Q_FUNC_INFO;
}

Cast3::~Cast3() {
    qInfo() << this << Q_FUNC_INFO;
}

bool Cast3::metodaA() {
    qInfo() << this << Q_FUNC_INFO;
    return true;
}

void Cast3::metodaB() {
    qInfo() << this << Q_FUNC_INFO;
}

int Cast3::metodaC() {
    qInfo() << this << Q_FUNC_INFO;
    return 0;
}
