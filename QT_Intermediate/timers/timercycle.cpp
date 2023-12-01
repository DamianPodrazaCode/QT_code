#include "timercycle.h"

TimerCycle::TimerCycle(QObject *parent) : QObject{parent} {
    number = 0;
    timer.setInterval(300);
    connect(&timer, SIGNAL(timeout()), this, SLOT(timeOut()));
}

void TimerCycle::timeOut() {
    number++;
    qInfo() << "tick" << number << " " << QTime::currentTime();
    if (number >= 10) {
        timer.stop();
        number = 0;
    }
}

void TimerCycle::doStuff() {
    timer.start();
}
