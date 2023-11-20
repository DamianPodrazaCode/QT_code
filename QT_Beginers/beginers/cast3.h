#ifndef CAST3_H
#define CAST3_H

#include <QDebug>
#include <QObject>

class Cast3 : public QObject {
    Q_OBJECT

public:
    explicit Cast3(QObject *parent = nullptr);
    ~Cast3();
    bool metodaA();
    void metodaB();
    int metodaC();

signals:
};

#endif // CAST3_H
