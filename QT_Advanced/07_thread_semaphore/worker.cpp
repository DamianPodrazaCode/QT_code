#include "worker.h"

Worker::Worker(QSemaphore* sema, QList<int>* values, QObject* parent) : QObject{parent} {
    m_sema = sema;
    m_values = values;
}

void Worker::run() {
    qInfo() << "run" << QThread::currentThread();
    int max = QRandomGenerator::global()->bounded(1, m_values->size());

    qInfo() << "acquiring" << max << QThread::currentThread();
    m_sema->acquire(max); // rezerwacja miejsc

    qInfo() << "acquire" << m_sema->available() << QThread::currentThread();
    for (int i = 0; i < max; ++i) {
        qInfo() << "modify" << i << QThread::currentThread();
        int val = QRandomGenerator::global()->bounded(100);
        m_values->replace(i, val);
    }

    qInfo() << "release" << max << QThread::currentThread();
    m_sema->release(max);
}
