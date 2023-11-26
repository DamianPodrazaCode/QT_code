#include <QBuffer>
#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QTextStream>

bool makeFile(QString path) {
    QFile file(path);
    if (file.open(QIODevice::WriteOnly)) {
        return true;
    }
    return false;
}

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);



    return a.exec();
}
