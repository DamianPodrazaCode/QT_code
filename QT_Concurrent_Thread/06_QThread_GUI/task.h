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

    int *count; //wskaźnik na zmienną z obiektu sterującego
    void run() override; // nadpisanie metody z QThread

signals:
    void update_label(QString str);
};

#endif // TASK_H
