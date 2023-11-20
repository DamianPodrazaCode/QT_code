#ifndef CAST2_H
#define CAST2_H

#include "cast1.h"
#include <QDebug>
#include <QObject>

class Cast2 : public Cast1 {
    Q_OBJECT

public:
    explicit Cast2(QObject *parent = nullptr);
    ~Cast2();
    float dataFloat = 32.1;
    void metoda3();

signals:
};

#endif // CAST2_H
