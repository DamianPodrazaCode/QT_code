#ifndef C_H
#define C_H

#include <QObject>
#include <QDebug>
#include "b.h"

class C : public B
{
    Q_OBJECT
public:
    explicit C(QObject *parent = nullptr);
    ~C();
    void metodaA1();
//    void metodaA2();
    void metodaB1();
//    void metodaB2();

signals:

};

#endif // C_H
