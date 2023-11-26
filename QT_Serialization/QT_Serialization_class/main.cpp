#include <QCoreApplication>
#include <QDataStream>
#include <QDebug>
#include <QDir>
#include <QFile>
#include "test.h"

bool saveFile(Test *t, QString path) {
    QFile file(path);
    if (!file.open(QIODevice::WriteOnly))
        return false;

    QDataStream out(&file);
    out.setVersion(QDataStream::Qt_6_6);

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

    file.close();
    return true;
}

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    QString path = "test.txt";
    Test t;
    qInfo() << t.map;
    t.fill();
    qInfo() << t.map;

    //    if (saveFile(&t, path)) {
//        loadFile(path);
//    }


    return a.exec();
}
