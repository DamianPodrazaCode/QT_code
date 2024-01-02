#ifndef PERC2IN_H
#define PERC2IN_H

#include <QList>
#include <QObject>
#include <QDebug>
#include <QRandomGenerator>

class Perc2in : public QObject {
    Q_OBJECT

public:
    explicit Perc2in(QObject *parent = nullptr);

    void learn(QList<double *> in, int size, int count, double step);
    void showState();
    int get(double in1, double in2);

private:
    int out = 0;
    double in1;
    double in2;

    double w1;
    double w2;
    double ws;
    double learnStep;

signals:
};

#endif // PERC2IN_H
