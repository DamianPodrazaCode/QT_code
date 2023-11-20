#include "c.h"

C::C(QObject *parent) : B{parent} {
    qInfo() << this << "konst";
}

C::~C() {
    qInfo() << this << "dest";
}

void C::metodaA1() {
    qInfo() << this << "metodaA1 z C";
}

//void C::metodaA2() {
//    qInfo() << this << "metodaA2 z C";
//}

void C::metodaB1() {
    qInfo() << this << "metodaB1 z C";
}

//void C::metodaB2() {
//    qInfo() << this << "metodaB2 z C";
//}
