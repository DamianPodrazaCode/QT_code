#include <QBuffer>
#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QTextStream>

// twirzenie pliku do testu
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

// zwraca stringa z nagłówkiem
QByteArray getHeader() {
    QByteArray header;
    header.append("@!~!@");
    return header;
}

// compresuje do pliku w postaci >nagłówek<>dane skompresowane o rozmiarze size<>nagłówek<>dane....
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

// dekompresja
bool decompressFile(QString originalFile, QString newFile) {
    QFile oFile(originalFile);
    QFile nFile(newFile);
    QByteArray header = getHeader();

    if (!oFile.open(QIODevice::ReadOnly))
        return false;
    if (!nFile.open(QIODevice::WriteOnly))
        return false;
    int size = 1024;

    QByteArray buffer = oFile.peek(size); // odczyt do buffer bez przesuwania wskaźnika w pliku
    if (!buffer.startsWith(header)) {     // sprawdzenie czy bufor zaczyna się od danego nagłóWka
        qCritical() << "to nie plik do dekompresji";
        oFile.close();
        nFile.close();
        return false;
    }

    oFile.seek(header.length()); // ustawienie za pierwszym nagłówkiem

    while (!oFile.atEnd()) {
        buffer = oFile.peek(size);             // odczyt do buffer bez przesuwania wskaźnika w pliku
        qint64 index = buffer.indexOf(header); // index na następnym nagłówku, czyli ilość danych do odzcytania
        qInfo() << "head found at:" << index;
        if (index > -1) { // jeżeli jest następny nagłówek
            // jest nagłówek
            qint64 maxbytes = index; // ilość danych do odczytania
            qInfo() << "reading :" << maxbytes;
            buffer = oFile.read(maxbytes); // odczytanie danych
            oFile.read(header.length());   // odczytanie następnego nagłóWka i przesunięcie wskaźnika
        } else {
            // niema nagłówka
            qInfo() << "read all no header";
            buffer = oFile.readAll(); // odczyt końcówki pliku
        }

        QByteArray decompressed = qUncompress(buffer);
        nFile.write(decompressed);
        nFile.flush();
    }

    oFile.close();
    nFile.close();
    qInfo() << "dekompresja zakończona";
    return true;
}

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    QString originalFile = "original.txt";
    QString compressedFile = "compressed.txt";
    QString decompressedFile = "decompressed.txt";

    if (makeFile(originalFile)) {
        qInfo() << "makeFile";
        if (compressFile(originalFile, compressedFile)) {
            qInfo() << "compressedFile";
            if (decompressFile(compressedFile, decompressedFile)) {
                qInfo() << "decompressedFile";
            }
        }
    }

    return a.exec();
}
