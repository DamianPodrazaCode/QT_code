#ifndef A_H
#define A_H

#include <QDebug>

class A {
public:
    A() {
        qInfo() << this << "k A";
    }
    virtual void makeA() = 0;
};

#endif // A_H
