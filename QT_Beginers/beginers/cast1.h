#ifndef CAST1_H
#define CAST1_H

#include <QDebug>
#include <QObject>

class Cast1 : public QObject {
    Q_OBJECT

public:
    explicit Cast1(QObject *parent = nullptr);
    ~Cast1();
    int dataInt = 5;
    double dataDouble = 2.345;
    void metoda1();
    bool metoda2();

signals:
};

#endif // CAST1_H
