#ifndef A_H
#define A_H

#include <QDebug>
#include <QObject>

class A : public QObject {
    Q_OBJECT

public:
    explicit A(QObject *parent = nullptr);
    ~A();
    void metodaA1();
    void metodaA2();

signals:
};

#endif // A_H
