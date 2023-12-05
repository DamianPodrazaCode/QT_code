#include "counter.h"

Counter::Counter(QMutex* mutex, int* value) {
    m_mutex = mutex;
    m_value = value;
}

void Counter::run() {
    m_mutex->lock(); //czeka do momentu aż będzie można zablokować, zablokuje i wykona kod blokując innych

    QThread::currentThread()->msleep(500);
    *m_value = *m_value + 1;
    qInfo() << *m_value << QThread::currentThread();

    m_mutex->unlock(); //odblokowuje i pozwala wykonywać innym
}
