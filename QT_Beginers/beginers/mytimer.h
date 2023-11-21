#ifndef MYTIMER_H
#define MYTIMER_H

#include <QDebug>
#include <QObject>
#include <QTimer>

class MyTimer : public QObject {
    Q_OBJECT

public:
    explicit MyTimer(QObject *parent = nullptr);
    ~MyTimer();

    void start();

public slots:
    void timeTick();

signals:

private:
    QTimer *timer;
};

#endif // MYTIMER_H
