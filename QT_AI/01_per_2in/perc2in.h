#ifndef PERC2IN_H
#define PERC2IN_H

#include <QDebug>
#include <QList>
#include <QObject>
#include <QRandomGenerator>

class Perc2in : public QObject {
    Q_OBJECT

public:
    explicit Perc2in(QObject *parent = nullptr);

    void learn(QList<double> *in, int size, int count, double step);
    void showState();
    int get(double in1, double in2);

private:
    int out = 0; // wyjście
    double in1;  // wejście 1
    double in2;  // wejście 2

    double w1;        // waga wejścia 1
    double w2;        // waga wejścia 2
    double wp;        // wartość progowa
    double learnStep; // szybkość/dokładność uczenia

signals:
};

#endif // PERC2IN_H
