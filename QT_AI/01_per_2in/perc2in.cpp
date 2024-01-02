#include "perc2in.h"

Perc2in::Perc2in(QObject* parent, int inSize) : QObject{parent} {
    this->inSize = inSize;
    // w1 = -17.6;
    // w2 = 66.1;
    // wp = 5;

    // w1 = ((QRandomGenerator::global()->bounded(100)) - 50) / 100.0;
    // w2 = ((QRandomGenerator::global()->bounded(100)) - 50) / 100.0;
    // wp = ((QRandomGenerator::global()->bounded(100)) - 50) / 100.0;
}

void Perc2in::learn(QList<double>* in, double step) {
    qInfo() << "Ilość danych uczenia :" << in->count() / (inSize + 1);
    learnStep = step;
    QList<int> lTrue;
    QList<int> lOut;

    for (int j = 0; j < 100; j++) {
        lOut.clear();
        for (int i = 0; i < in->count(); i += (inSize + 1)) {
            in1 = in->at(i);
            in2 = in->at(i + 1);
            double in1N = in1 * w1;
            double in2N = in2 * w2;
            double outN = in1N + in2N + wp;
            lOut.append(outN > 0 ? 1 : -1);
            // wypełninie listy prawd, tylko pierwsze wykonanie pętli 'i'
            if (lTrue.count() < (in->count() / (inSize + 1))) {
                lTrue.append(in->at(i + 2));
                if (lTrue.count() == (in->count() / (inSize + 1)))
                    qInfo() << "Lista prawd: " << lTrue << "\n";
            }
        }
        qInfo() << "Iteracja nr:" << (j + 1) << lOut;
        // sprawdzenie poprawności wyliczeń, jeżeli prawda to wsztskie wagi ustawione są prawidłowo
        if (lOut == lTrue)
            break;

        for (int i = 0; i < lTrue.count(); i++) {
            if (lOut.at(i) != lTrue.at(i)) {
                int t1 = lTrue.at(i);
                w1 = (t1 * in->at(i * (inSize + 1)) * step) + w1;
                w2 = (t1 * in->at((i * (inSize + 1)) + 1) * step) + w2;
                wp = (t1 * step) + wp;
                break;
            }
        }
    }
    qInfo() << "\n";
}

void Perc2in::showState() {

    //qInfo() << "in1 -> " << in1 << ", in2 ->" << in2 << "\n";
    qInfo() << "Wagi: w1 =" << w1 << ", w2 =" << w2 << ", wp =" << wp << "\n";
}

int Perc2in::get(double in1, double in2) {
    double in1N = in1 * w1;
    double in2N = in2 * w2;
    double outN = in1N + in2N + wp;
    // return outN > 0 ? 1 : -1;
    return outN;
}
