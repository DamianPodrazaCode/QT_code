#include "test.h"
#include <QCoreApplication>
#include <QDataStream>
#include <QDebug>
#include <QDir>
#include <QFile>

bool saveFile(Test *t, QString path) {
    QFile file(path);
    if (!file.open(QIODevice::WriteOnly))
        return false;

    QDataStream out(&file);
    out.setVersion(QDataStream::Qt_6_6);

    out << *t;

    file.close();
    return true;
}

bool loadFile(QString path) {
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly))
        return false;

    QDataStream in(&file);
    if (in.version() != QDataStream::Qt_6_6) {
        qCritical() << "wersja nie pasuje";
        file.close();
        return false;
    }

    Test t;
    in >> t;

    file.close();

    qInfo() << t.name();
    qInfo() << t.map();

    return true;
}

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    QString path = "test.txt";
    Test t;
    t.fill();
    if (saveFile(&t, path)) {
        loadFile(path);
    }

    return a.exec();
}
