#include "b.h"

B::B(QObject *parent) : A{parent} {
    qInfo() << this << "konstruktor";
}

B::~B() {
    qInfo() << this << "destruktor";
}

void B::metodaB() {
}
