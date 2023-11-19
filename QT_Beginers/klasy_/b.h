#ifndef B_H
#define B_H

#include <QObject>
#include <QString>
#include <QDebug>

class B : public QObject {
    Q_OBJECT

public:
    explicit B(QObject *parent = nullptr, QString name = "");
    ~B();

signals:
};

#endif // B_H
