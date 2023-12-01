#include "timercycle.h"
#include <QCoreApplication>
#include <QTime>
#include <QTimer>

void testSingleShot() {
    qInfo() << "shot!!!";
}

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    // jeden strzał
    qInfo() << "wait!!! 2sec";
    QTimer::singleShot(2000, &testSingleShot);

    // a tu równolegle timer cykliczny na 10 strzałów
    TimerCycle timer;
    timer.doStuff();

    return a.exec();
}
