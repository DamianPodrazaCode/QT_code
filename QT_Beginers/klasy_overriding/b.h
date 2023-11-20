#ifndef B_H
#define B_H

#include <QObject>
#include <QDebug>
#include "a.h"

class B : public A
{
    Q_OBJECT
public:
    explicit B(QObject *parent = nullptr);
    ~B();
    void metodaA1();
    void metodaB1();
    void metodaB2();

signals:

};

#endif // B_H
