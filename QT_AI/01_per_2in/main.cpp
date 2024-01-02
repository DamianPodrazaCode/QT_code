#include "perc2in.h"
#include <QCoreApplication>
#include <QList>

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    QList<double> lLearn = {23.0, 4.0, 18.0, 3.0, 8.0, 2.0, 200.0, 30.0, 8.0, 150.0, 30.0, 350.0, 5.0, 100.0, 10.0, 200.0};
    qInfo() << &lLearn;

    Perc2in per1;
    per1.showState();
    per1.learn(&lLearn, 0, 0, 0.2);

    return a.exec();
}
