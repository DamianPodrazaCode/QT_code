#ifndef COUNTER_H
#define COUNTER_H

#include <QDebug>
#include <QRunnable>
#include <QThread>
#include <QMutex>
#include <QMutexLocker>>

class Counter : public QRunnable {
public:
    Counter(QMutex *mutex, int *value);
    ~Counter();
    // QRunnable interface

public:
    void run();

private:
    int *m_value;
    QMutex *m_mutex;
};

#endif // COUNTER_H
