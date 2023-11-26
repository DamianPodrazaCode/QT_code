#include <QCoreApplication>
#include <QDataStream>
#include <QDebug>
#include <QFile>

bool saveFile(QString path) {
    QFile file(path);
    if (!file.open(QIODevice::WriteOnly))
        return false;


    file.close();
    return true;
}

bool loadFile(QString path) {
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly))
        return false;

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
