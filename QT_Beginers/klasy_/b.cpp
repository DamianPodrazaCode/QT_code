#include "b.h"

B::B(QObject *parent, QString name) : QObject{parent} {
    this->setObjectName(name);
    qInfo() << this << "konstruktor";
}

B::~B() {
    qInfo() << this << "destruktor";
}
