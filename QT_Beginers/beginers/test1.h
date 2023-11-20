#ifndef TEST1_H
#define TEST1_H

#include <QObject>
#include <QDebug>

class Test1 : public QObject {
    Q_OBJECT

public:
    explicit Test1(QObject *parent = nullptr);
    ~Test1();
    void metoda1();

signals:
};

#endif // TEST1_H
