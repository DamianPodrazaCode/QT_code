#ifndef TASK_H
#define TASK_H

#include <QDebug>
#include <QObject>
#include <QThread>

class Task : public QThread {
    Q_OBJECT

public:
    explicit Task(QObject *parent = nullptr);
    ~Task();

    void run() override;
};

#endif // TASK_H
