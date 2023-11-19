#include "a.h"

A::A(QObject *parent) : QObject{parent} {
    qInfo() << this << "konstruktor";
}

A::~A() {
    qInfo() << this << "destruktor";
}

void A::metodaA() {

}
