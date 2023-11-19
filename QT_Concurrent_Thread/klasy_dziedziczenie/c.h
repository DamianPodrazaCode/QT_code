#ifndef C_H
#define C_H

#include "b.h"
#include <QDebug>
#include <QObject>

class C : public B {
    Q_OBJECT

public:
    explicit C(QObject *parent = nullptr);
    ~C();
    void metodaC();

signals:
};

#endif // C_H
