#include "tx.h"

Tx::Tx(QObject *parent) : QObject{parent} {
    this->setObjectName(Q_FUNC_INFO);
    qInfo() << "konstruktor" << this << Q_FUNC_INFO;
}

Tx::~Tx() {
    qInfo() << "dekonstruktor" << this << Q_FUNC_INFO;
}

void Tx::start() {
    emit info_singnal("info od ");
}
