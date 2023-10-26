#ifndef TASK_H
#define TASK_H

#include <QObject>
#include <QThread>
#include <QDebug>

class Task : public QThread {
    Q_OBJECT

public:
    explicit Task(QObject *parent = nullptr);
    ~Task();

    int *count;
    void run() override;

signals:
    void update_label(QString str);
};

#endif // TASK_H
