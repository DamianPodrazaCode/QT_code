#include "counter.h"

Counter::Counter(QObject *parent) : QObject{parent} {
    qInfo() << this << "Konstruktor";
}

Counter::~Counter() {
    qInfo() << this << "Dekonstruktor";
}

void Counter::start() {
    for (int i = 0; i < 20; ++i) {
        qInfo() << QThread::currentThread()->objectName() << " = " << i;
        auto value = static_cast<unsigned long>(QRandomGenerator::global()->bounded(500));
        QThread::currentThread()->msleep(value);
        qInfo() << QThread::currentThread()->objectName() << "Complete";
    }
    qInfo() << this << "Complited";
    deleteLater();

    QThread::currentThread()->quit();
}
