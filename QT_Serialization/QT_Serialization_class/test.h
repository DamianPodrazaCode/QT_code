#ifndef TEST_H
#define TEST_H

#include <QDebug>
#include <QObject>

class Test : public QObject {
    Q_OBJECT

public:
    explicit Test(QObject *parent = nullptr);
    ~Test();
    void fill();
    QMap<QString, QString> map();

    friend QDataStream &operator<<(QDataStream &stream, const Test &t) {
        qInfo() << "Operator <<";
        stream << t.m_name;
        stream << t.m_map;
        return stream;
    }

    friend QDataStream &operator>>(QDataStream &stream, Test &t) {
        qInfo() << "Operator >>";
        stream >> t.m_name;
        stream >> t.m_map;
        return stream;
    }

    QString name();
    void setName(QString &newName);

private:
    QString m_name;
    QMap<QString, QString> m_map;

signals:
};

#endif // TEST_H
