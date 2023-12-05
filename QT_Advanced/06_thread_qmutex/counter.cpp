#include "counter.h"

Counter::Counter(QMutex* mutex, int* value) {
    m_mutex = mutex;
    m_value = value;
    qInfo() << "constr" << this;
}

Counter::~Counter() {
    qInfo() << "deconstr" << this;
}

// #define q_mutex
#define q_mutex_locker

#ifdef q_mutex
void Counter::run() {
    m_mutex->lock(); // czeka do momentu aż będzie można zablokować, zablokuje i wykona kod blokując innych

    QThread::currentThread()->msleep(10);
    *m_value = *m_value + 1;
    qInfo() << *m_value << QThread::currentThread();

    m_mutex->unlock(); // odblokowuje i pozwala wykonywać innym
}
#endif

#ifdef q_mutex_locker
void Counter::run() {

    QThread::currentThread()->msleep(10);

    QMutexLocker locker(m_mutex); // to samo co wyżej tylko blokuje wszystko co poniżej
    *m_value = *m_value + 1;
    qInfo() << *m_value << QThread::currentThread();

}
#endif
