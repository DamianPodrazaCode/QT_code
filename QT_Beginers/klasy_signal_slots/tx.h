#ifndef TX_H
#define TX_H

#include <QObject>
#include <QDebug>

class Tx : public QObject {
    Q_OBJECT

    QString m_message;

public:
    explicit Tx(QObject *parent = nullptr);
    ~Tx();
    void start();

signals:
    void info_singnal(QString str);
};

#endif // TX_H
