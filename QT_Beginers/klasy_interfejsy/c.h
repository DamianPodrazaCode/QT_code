#ifndef C_H
#define C_H

#include "a.h"
#include "b.h"
#include <QDebug>
#include <QObject>

class C : public QObject, public A, public B {
    Q_OBJECT

public:
    explicit C(QObject *parent = nullptr);
    ~C();
    // B interface
    void makeB();
    // A interface
    void makeA();
};

#endif // C_H
