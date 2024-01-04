#ifndef PERC2IN_H
#define PERC2IN_H

#include <QDebug>
#include <QList>
#include <QObject>
#include <QRandomGenerator>

class Perc2in : public QObject {
    Q_OBJECT

public:
    explicit Perc2in(QObject *parent = nullptr, int inSize = 2);

    void learn(QList<double> *in, double step);
    void showState();
    int get(double in1, double in2);

private:
    int out = 0;            // wyjście
    double in1 = 0;         // wejście 1
    double in2 = 0;         // wejście 2
    int inSize = 2;         // ilość wejść
    double w1 = 0;          // waga wejścia 1
    double w2 = 0;          // waga wejścia 2
    double wp = 0;          // wartość progowa
    double learnStep = 0.1; // szybkość uczenia

signals:
};

#endif // PERC2IN_H
