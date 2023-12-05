#ifndef WORKER_H
#define WORKER_H

#include <QDebug>
#include <QList>
#include <QObject>
#include <QRandomGenerator>
#include <QSemaphore>
#include <QThread>

class Worker : public QObject {
    Q_OBJECT

public:
    explicit Worker(QSemaphore *sema, QList<int> *values, QObject *parent = nullptr);

signals:

public slots:
    void run();

private:
    QSemaphore *m_sema;
    QList<int> *m_values;
};

#endif // WORKER_H
