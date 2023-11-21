#include "rx.h"

Rx::Rx(QObject *parent) : QObject{parent} {
    this->setObjectName(Q_FUNC_INFO);
    qInfo() << "konstruktor" << this << Q_FUNC_INFO;
}

Rx::~Rx() {
    qInfo() << "dekonstruktor" << this << Q_FUNC_INFO;
}

void Rx::info_slot(QString str) {
    qInfo() << str << Q_FUNC_INFO;
}
