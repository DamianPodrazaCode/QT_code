#include <QBuffer>
#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QTextStream>

bool makeFile(QString path) {
    QFile file(path);
    if (file.open(QIODevice::WriteOnly)) {
        QByteArray data;
        for (int i = 0; i < 1000; ++i) {
            data.append(QString::number(i).toUtf8() + "\r\n");
        }
        file.write(data);
        file.close();
        return true;
    }
    return false;
}

QByteArray getHeader() {
    QByteArray header;
    header.append("@!~!@");
    return header;
}

bool compressFile(QString originalFile, QString newFile) {
    QFile oFile(originalFile);
    QFile nFile(newFile);
    QByteArray header = getHeader();

    if (!oFile.open(QIODevice::ReadOnly))
        return false;
    if (!nFile.open(QIODevice::WriteOnly))
        return false;
    int size = 1024;

    while (!oFile.atEnd()) {
        QByteArray buffer = oFile.read(size);
        QByteArray compressed = qCompress(buffer, 9);
        nFile.write(header);
        nFile.write(compressed);
    }

    oFile.close();
    nFile.close();
    qInfo() << "kompresja zakończona";
    return true;
}

bool deompressFile(QString originalFile, QString newFile) {
    QFile oFile(originalFile);
    QFile nFile(newFile);
    QByteArray header = getHeader();

    if (!oFile.open(QIODevice::ReadOnly))
        return false;
    if (!nFile.open(QIODevice::WriteOnly))
        return false;
    int size = 1024;


    oFile.close();
    nFile.close();
    qInfo() << "dekompresja zakończona";
    return true;
}

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    return a.exec();
}
