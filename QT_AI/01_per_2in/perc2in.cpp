#include "perc2in.h"

Perc2in::Perc2in(QObject* parent) : QObject{parent} {
    w1 = (QRandomGenerator::global()->bounded(100)) / 10;
    w2 = (QRandomGenerator::global()->bounded(100)) / 10;
    ws = (QRandomGenerator::global()->bounded(100)) / 10;
}

void Perc2in::learn(QList<double>* in, int size, int count, double step) {
    learnStep = step;
    qInfo() << *in << in;
}

void Perc2in::showState() {
    qInfo() << "in1 -> " << in1 << ", in2 ->" << in2 << "\n";
    qInfo() << "w1 -> " << w1 << ", w2 ->" << w2 << ", ws ->" << ws << ", out ->" << out << "\n";
}

int Perc2in::get(double in1, double in2) {
    return in1 + in2;
}
