#include "c.h"

C::C(QObject *parent) : QObject{parent} {
    qInfo() << this << "konstuktor";
}

C::~C() {
    qInfo() << this << "destuktor";
}

void C::makeB() {
     qInfo() << this << "makeB";
}

void C::makeA() {
     qInfo() << this << "makeA";
}
