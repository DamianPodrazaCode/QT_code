#ifndef TEST_H
#define TEST_H

#include <QObject>
#include <QDebug>

class Test : public QObject {
    Q_OBJECT

public:
    explicit Test(QObject *parent = nullptr);
    ~Test();
    void fill();
    QString name() const;
    void setName(const QString& newName);
    QMap<QString, QString> map;

private:
    QString m_name;
    QMap<QString, QString> n_map;

signals:
};

#endif // TEST_H
