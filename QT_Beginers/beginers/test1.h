#ifndef TEST1_H
#define TEST1_H

#include <QDebug>
#include <QObject>

class Test1 : public QObject {
    Q_OBJECT

public:
    explicit Test1(QObject *parent = nullptr);
    ~Test1();
    void metoda1();

public slots:
    void timerTick();

signals:
};

#endif // TEST1_H
