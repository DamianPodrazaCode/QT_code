#include "b.h"

B::B(QObject *parent) : A{parent} {
    qInfo() << this << "konst";
}

B::~B() {
    qInfo() << this << "dest";
}

void B::metodaA1() {
    qInfo() << this << "metodaA1 z B";
}

//void B::metodaA2() {
//    qInfo() << this << "metodaA2 z B";
//}

void B::metodaB1() {
    qInfo() << this << "metodaB1 z B";
}

void B::metodaB2() {
    qInfo() << this << "metodaB2 z B";
}
