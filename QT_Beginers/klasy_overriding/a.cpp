#include "a.h"

A::A(QObject *parent) : QObject{parent} {
    qInfo() << this << "konst";
}

A::~A() {
    qInfo() << this << "dest";
}

void A::metodaA1() {
    qInfo() << this << "metodaA1 z A";
}

void A::metodaA2() {
    qInfo() << this << "metodaA2 z A";
}
