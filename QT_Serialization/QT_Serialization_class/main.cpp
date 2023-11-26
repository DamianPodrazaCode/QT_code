#include <QCoreApplication>
#include <QDataStream>
#include <QDebug>
#include <QDir>
#include <QFile>

bool saveFile(QString path) {
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
        qCritical() << "wersjia nie pasuje";
        file.close();
        return false;
    }

    file.close();
    return true;
}

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    return a.exec();
}
