#include "c.h"

C::C(QObject *parent) : B{parent} {
    qInfo() << this << "konstruktor";
}

C::~C() {
    qInfo() << this << "destruktor";
}

void C::metodaC() {
    qInfo() << this << "metodaC";
}
