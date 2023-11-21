#ifndef TX_H
#define TX_H

#include <QObject>

class Tx : public QObject {
    Q_OBJECT

public:
    explicit Tx(QObject *parent = nullptr);

signals:
};

#endif // TX_H
