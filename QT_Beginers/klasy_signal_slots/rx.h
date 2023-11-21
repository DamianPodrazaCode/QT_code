#ifndef RX_H
#define RX_H

#include <QDebug>
#include <QObject>

class Rx : public QObject {
    Q_OBJECT

public:
    explicit Rx(QObject *parent = nullptr);
    ~Rx();

public slots:
    void info_slot(QString str);

signals:
};

#endif // RX_H
