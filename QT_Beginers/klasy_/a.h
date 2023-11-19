#ifndef A_H
#define A_H

// zwykła klasa z konstruktorem i destruktorem

#include <QObject>
#include <QDebug>

class A : public QObject {
    Q_OBJECT

public:
    explicit A(QObject *parent = nullptr);

    ~A();

signals:
};

#endif // A_H
