#ifndef A_H
#define A_H

#include <QObject>
#include <QDebug>

class A : public QObject { // dzidziczy po QObject
    Q_OBJECT

public:
    explicit A(QObject *parent = nullptr);
    ~A();
    void metodaA();

signals:
};

#endif // A_H
