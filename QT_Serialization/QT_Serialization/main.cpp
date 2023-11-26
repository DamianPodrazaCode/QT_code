#include <QCoreApplication>
#include <QDataStream>
#include <QDebug>
#include <QFile>

bool saveFile(QString path) {
    QFile file(path);
    if (!file.open(QIODevice::WriteOnly))
        return false;

    QDataStream out(&file);
    out.setVersion(QDataStream::Qt_6_6);

    QString str = "string z numerem 345";
    qint64 num = 345;

    out << str << num;

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

    QString str;
    qint64 num;

    in >> str;
    in >> num;

    qInfo() << str << num;

    file.close();
    return true;
}

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    QString file = "test.txt";
    if (saveFile(file)) {
        qInfo() << "saved";
        loadFile(file);
    }

    return a.exec();
}
