#ifndef B_H
#define B_H

#include "a.h"
#include <QDebug>
#include <QObject>

class B : public A { // dzidziczy po A, A dzidziczy po QObject
    Q_OBJECT

public:
    explicit B(QObject *parent = nullptr);
    ~B();
    void metodaB();

signals:
};

#endif // B_H
