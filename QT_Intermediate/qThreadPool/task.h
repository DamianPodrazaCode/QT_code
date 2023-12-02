#ifndef TASK_H
#define TASK_H

#include <QDebug>
#include <QObject>
#include <QRunnable>
#include <QThread>

class Task : public QObject, public QRunnable {
    Q_OBJECT

public:
    explicit Task(QObject *parent = nullptr);
    ~Task();

signals:

public slots:
    void run(); // virtualna, refaktoryzacja z QRunnable
};

#endif // TASK_H
