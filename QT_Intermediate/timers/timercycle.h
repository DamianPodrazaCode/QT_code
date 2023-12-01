#ifndef TIMERCYCLE_H
#define TIMERCYCLE_H

#include <QDebug>>
#include <QObject>
#include <QTime>
#include <QTimer>

class TimerCycle : public QObject {
    Q_OBJECT

public:
    explicit TimerCycle(QObject *parent = nullptr);

signals:

public slots:
    void timeOut();
    void doStuff();

private:
    QTimer timer;
    int number;
};

#endif // TIMERCYCLE_H
