#include "perc2in.h"
#include <QCoreApplication>
#include <QList>

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    QList<double> lLearn = {23.0,  4.0,   -1, //
                            18.0,  3.0,   -1, //
                            8.0,   2.0,   -1, //
                            200.0, 30.0,  -1, //
                            8.0,   150.0, 1,  //
                            30.0,  350.0, 1,  //
                            5.0,   100.0, 1,  //
                            10.0,  200.0, 1};
    // qInfo() << &lLearn;

    Perc2in per1(nullptr, 2);
    per1.showState();
    per1.learn(&lLearn, 0.1);
    per1.showState();

    qInfo() << per1.get(50, 10); // -1
    qInfo() << per1.get(100, 10); // -1
    qInfo() << per1.get(5, 10); // 1
    qInfo() << per1.get(50, 100); // 1
    qInfo() << per1.get(50, 1000); // 1

    return a.exec();
}
