#ifndef RX_H
#define RX_H

#include <QObject>

class Rx : public QObject {
    Q_OBJECT

public:
    explicit Rx(QObject *parent = nullptr);

signals:
};

#endif // RX_H
