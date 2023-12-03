#ifndef COUNTER_H
#define COUNTER_H

#include <QObject>

class Counter : public QObject {
    Q_OBJECT

public:
    explicit Counter(QObject *parent = nullptr);
    ~Counter();

signals:

public slots:
    void start();
};

#endif // COUNTER_H
