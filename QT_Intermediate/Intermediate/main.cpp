#include "test.h"
#include <QBuffer>
#include <QCoreApplication>
#include <QDataStream>
#include <QDateTime>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QFileInfoList>
#include <QList>
#include <QLockFile>
#include <QMap>
#include <QRandomGenerator>
#include <QScopedPointer>
#include <QSet>
#include <QSettings>
#include <QSharedPointer>
#include <QStorageInfo>
#include <QString>
#include <QStringList>
#include <QTextStream>
#include <QThread>

// new - dadgling pointer
// smart poionter
// QScopedPointer
// QSharedPointer
// dynamic array QList
// fast lookup QSet
// QMap
// QStringList
// Qlist z objektami + smart poiner
// QMap z objektami
// QSettings -> zapis odczyt ustawień programu na dysku
// QIODevice
// qFileStreams - QTextStream
// qFileStreams - QDataStream
// dir
// fileinfo
// storageinfo
// lockFile
// QRandomGenerator, ASCII, UFT8 16 32, BASE64, HEX, encoding, decoding

// -------------------------------------------
void lifecycle() {
    Test T;
}
// -------------------------------------------
void dangling_pointer() {
    Test *pTest = new Test();
    pTest->work();
    delete pTest;

    pTest = nullptr;
    if (pTest != nullptr)
        pTest->work(); // ten pointer jest podpięty do nieistniejącego objektu
}
// -------------------------------------------
void smart_poionter() {
    // std::unique_ptr
    // std::weak_ptr
    // std::auto_ptr
    std::shared_ptr<Test> pTest = std::shared_ptr<Test>(new Test());
    pTest->work();
}
// -------------------------------------------
// pointer który się sam skasuje po wyjściu z zakresu
void qScopedPointer_() {
    QScopedPointer<Test> pTest(new Test());
    pTest->work();
}
// -------------------------------------------
// pointer który się skasuje nawet używając go poza zakresem
QSharedPointer<Test> getObj(QString name) {
    QSharedPointer<Test> pTest(new Test());
    pTest->setObjectName(name);
    pTest->work();
    return pTest;
}
void work(QSharedPointer<Test> qsp) {
    qsp->work();
}
void qSharedPointer_() {
    QSharedPointer<Test> ptrTest = getObj("nowy");
    work(ptrTest);
    ptrTest->work();
}
// -------------------------------------------
void qList_() {
    QList<int> listaInt;
    listaInt << 43 << 55 << 101 << 1 << 2 << 33 << 44;
    listaInt.append(43);
    qInfo() << listaInt;

    QStringList listaStr;
    listaStr << "sdfsd"
             << "3fdsf"
             << "htgf";
    qInfo() << listaStr;
    listaStr.sort();
    qInfo() << listaStr;
}
// -------------------------------------------
void qSet_() { // do szybkich operacji na zbiorach nieposortowanych, dodawanie zbioróqw odejmowanie i porównywanie
    QSet<QString> tab;
    tab << "gfgd"
        << "aaa"
        << "vvv"
        << "bbb"
        << "iyut";
    qInfo() << tab << tab.contains("bbb");
}
// -------------------------------------------
void qMap_() { // tablica dwuwymiarowa przeszukiwana po kluczach albo wartościach a nie po indeksie, automatyczne sortowana
    QMap<QString, int> mapa;
    mapa.insert("asd", 12);
    mapa.insert("agdfsd", 212);
    mapa.insert("werasd", 4512);
    mapa.insert("23asd", 152);
    mapa.insert("56asd", 1322);
    qInfo() << mapa;              // cała mapa
    qInfo() << mapa.keys();       // wszystkie klucze
    qInfo() << mapa.key(212);     // odzczyt klucza w/g wartości
    qInfo() << mapa.values();     // wszystkie wartości
    qInfo() << mapa.value("asd"); // odczyt wartości w/g klucza
    qInfo() << mapa.keys().at(0); // odzcyt wartości w/g indeksu posortowanej mapy
    qInfo() << mapa["23asd"];     // odczyt wartości w/g klucza
}
// -------------------------------------------
void qStringList_() { // zaawansowana tablica stringów QList
    QString str("qqq dfoigj serpot [aposdkf[ 9879 3420590 gvnosdf twrdcwtyr odfguihod");
    QStringList lista = str.split(' ');
    qInfo() << str;
    qInfo() << lista;
    QString fromList = lista.join(";");
    qInfo() << fromList;
    lista.sort();
    qInfo() << lista;
}
// -------------------------------------------
void qListObj_() {
    QList<Test *> lista; // klasa Test jest typu QObject i może być tworzona tylko przez wskaźnik
    lista.append(new Test());
    lista.append(new Test());
    lista.append(new Test());
    lista.append(new Test());
    lista.append(new Test());
    qDeleteAll(lista); // usuwa objekty z całej listy
    lista.clear();     // usuwa wskaźniki które pokazywały na nie istniejące już obiekty
    qInfo() << "end lista";

    // a teraz na smart pointer
    QList<QSharedPointer<Test>> listaSP;
    QSharedPointer<Test> item(new Test());
    listaSP.append(item);
    QSharedPointer<Test> item2(new Test());
    listaSP.append(item2);
    listaSP.clear();
    qInfo() << "end listaSP";
}
// -------------------------------------------
void qMapObj_() {
    QMap<QString, Test *> mapa;
    mapa.insert("aaa", new Test());
    mapa.insert("ccc", new Test());
    mapa.insert("bbb", new Test());
    qInfo() << mapa;
    qDeleteAll(mapa);
    mapa.clear();

    qInfo() << "";

    // smart pointer
    QMap<QString, QSharedPointer<Test>> mapaSP;
    QSharedPointer<Test> ptr(new Test());
    mapaSP.insert("aaa", ptr);
    QSharedPointer<Test> ptr2(new Test());
    mapaSP.insert("aaa", ptr2);
    mapaSP.clear();
}
// -------------------------------------------
QString getSettings(QString group, QString key) {
    QSettings settings("init.ini", QSettings::Format::IniFormat);
    return settings.value(group + "/" + key).toString();
}

void setSettings(QString group, QString key, QString value) {
    QSettings settings("init.ini", QSettings::Format::IniFormat);
    settings.setValue(group + "/" + key, value);
}

void qSettings_() {
    setSettings("settings1", "key1", "val1"); // ustawianie watrości i automatyczny zapis w pliku *.ini
    setSettings("settings1", "key2", "val343");
    setSettings("settings1", "key3", "val212");
    setSettings("settings1", "key4", "val3434");

    qInfo() << getSettings("settings1", "key1"); // automatyczny odczyt z plików ini
    qInfo() << getSettings("settings1", "key2");
    qInfo() << getSettings("settings1", "key3");
    qInfo() << getSettings("settings1", "key4");
}
// -------------------------------------------
void qiodevice_() {
    // Qbuffer in RAM
    QBuffer buffer;
    if (buffer.open(QIODevice::ReadWrite)) {
        qInfo() << "open";
        QByteArray data("asdf ghjk lkjh nbvfghj ljkcfh");
        buffer.write(data);
        buffer.seek(0);
        QByteArray data1("1234");
        buffer.write(data1);
        buffer.seek(0); // na początek bo po zapisie jest tam gdzie zapisano ostatni znak
        qInfo() << buffer.readAll();
        buffer.close();
    } else {
        qInfo() << "buffer not open";
    }

    // write file
    QString filename = "test.txt";
    QFile file(filename);
    if (file.open(QIODevice::ReadWrite)) {
        qInfo() << "file open";
        QString now = QDateTime::currentDateTime().toString();
        QByteArray data;
        data.append(now.toLocal8Bit());
        file.write(data);
        file.flush();
        file.close();
        qInfo() << "file saved";
    } else {
        qInfo() << "file not open " << file.errorString();
    }

    // read file small only
    filename = "test.txt";
    QFile fileRead(filename);
    if (fileRead.exists()) {
        if (fileRead.open(QIODevice::ReadWrite)) {
            qInfo() << "file open";
            qInfo() << fileRead.readAll();
            qInfo() << "file read all";
            fileRead.close();
        } else {
            qInfo() << "file not open " << file.errorString();
        }
    } else {
        qInfo() << "file not exist " << file.errorString();
    }
}
// -------------------------------------------
namespace qFileStreams {

void write(QFile &file) {
    if (!file.isWritable()) {
        qInfo() << "Unable to write to file! " << file.errorString();
        return;
    }
    QTextStream stream(&file);
    stream.setEncoding(QStringConverter::LastEncoding);

    // stream.seek(file.size());

    stream << QDateTime::currentDateTime().toString() << "\r\n";
    QThread::msleep(500);
    stream << QDateTime::currentDateTime().toString() << "\r\n";
    QThread::msleep(500);
    stream << QDateTime::currentDateTime().toString() << "\r\n";
    QThread::msleep(500);
    stream << QDateTime::currentDateTime().toString() << "\r\n";
}
void read(QFile &file) {
    if (!file.isReadable()) {
        qInfo() << "Unable to read to file! " << file.errorString();
        return;
    }

    QTextStream stream(&file);
    stream.seek(0);

    while (!stream.atEnd()) {
        qInfo() << stream.readLine();
    }
}

void qFileStreams_() {
    QString fileName = "test.txt";
    QFile file(fileName);
    file.remove();

    if (file.open(QIODevice::ReadWrite)) {
        QTextStream stream(&file);
        qInfo() << "Encoding : " << stream.encoding();
        write(file);
        read(file);

        file.close();
    } else {
        qInfo() << "Open file error. " << file.errorString();
    }
}

} // namespace qFileStreams
// -------------------------------------------
namespace qFileDataStreams {

bool write(QString fileName) {
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly)) {
        qInfo() << file.errorString();
        return false;
    }

    QDataStream stream(&file);
    stream.setVersion(QDataStream::Qt_6_6);

    int intData = 56;
    QString strData = "sdfgklsdlfkgsl";
    double dData = 1.23456;
    qint64 i64Data = 4235234534;
    float fData = 5.4323;
    qInfo() << intData << strData << dData << i64Data << fData;

    stream << intData << strData << dData << i64Data << fData;

    if (!file.flush()) {
        qInfo() << file.errorString();
        file.close();
        return false;
    }

    qInfo() << "Close file.";
    file.close();
    return true;
}

bool read(QString fileName) {
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        qInfo() << file.errorString();
        return false;
    }

    QDataStream stream(&file);
    if (stream.version() != QDataStream::Qt_6_6) {
        qInfo() << "Wrong file version.";
        file.close();
        return false;
    }

    int intData;
    QString strData;
    double dData;
    qint64 i64Data;
    float fData;

    stream >> intData;
    stream >> strData;
    stream >> dData;
    stream >> i64Data;
    stream >> fData;

    file.close();

    qInfo() << intData << strData << dData << i64Data << fData;

    return true;
}

void qFileDataStreams_() {
    QString fileName = "test.txt";

    if (write(fileName))
        read(fileName);
}

} // namespace qFileDataStreams
// -------------------------------------------
void listDirR(QDir &root) {
    qInfo() << "--------- Listing R---------";
    foreach (QFileInfo fi, root.entryInfoList(QDir::AllEntries | QDir::NoDotAndDotDot, QDir::Name)) {
        if (fi.isDir()) {
            qInfo() << "Dir " << fi.filePath();
        }

        if (fi.isDir()) {
            QDir child(fi.filePath());
            qInfo() << "Inspecting " << child.absolutePath();
            listDirR(child);
        }

        if (fi.isFile()) {
            qInfo() << "File " << fi.filePath();
        }
    }
}

void listDir(QDir &root) {
    qInfo() << "--------- Listing ---------";
    foreach (QFileInfo fi, root.entryInfoList(QDir::Filter::Dirs, QDir::Name)) {
        if (fi.isDir()) {
            qInfo() << fi.absoluteFilePath();
        }
    }
}
void dir_() {
    QDir dir(QCoreApplication::applicationDirPath());
    qInfo() << dir.dirName();
    qInfo() << dir.absolutePath();
    dir.cdUp();
    qInfo() << dir.absolutePath();
    listDir(dir);
    dir.mkdir("aaa");
    listDir(dir);
    dir.rmdir("aaa");
    listDir(dir);
    qInfo() << "";
    listDirR(dir);
}
// -------------------------------------------

void fileinfo_(QString path) {
    qInfo() << "List:" << path;
    QDir dir(path);
    QFileInfoList dirs = dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);
    QFileInfoList files = dir.entryInfoList(QDir::Files);

    foreach (QFileInfo fi, dirs) {
        qInfo() << fi.fileName();
    }
    foreach (QFileInfo fi, files) {
        qInfo() << fi.fileName();
        qInfo() << fi.size();
        qInfo() << fi.birthTime();
        qInfo() << fi.lastModified();
        qInfo() << fi.lastRead();
    }
    foreach (QFileInfo fi, dirs) {
        fileinfo_(fi.absoluteFilePath());
    }
}
// -------------------------------------------
void storageInfo_() {
    qInfo() << QStorageInfo::mountedVolumes();

    foreach (QStorageInfo storage, QStorageInfo::mountedVolumes()) {
        qInfo() << storage.displayName();
        qInfo() << storage.fileSystemType();
        qInfo() << storage.bytesTotal();
        qInfo() << storage.bytesAvailable();
        qInfo() << storage.bytesFree();
        qInfo() << storage.device();
        qInfo() << storage.isRoot();
        qInfo() << storage.blockSize();
    }

    QStorageInfo root = QStorageInfo::root();
    qInfo() << "root" << root.rootPath();
    QDir dir(root.rootPath());
    foreach (QFileInfo fi, dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot)) {
        qInfo() << fi.filePath();
    }
}
// -------------------------------------------
void lockFile_() {
    QString path = QDir::currentPath() + QDir::separator() + "test.txt";
    QFile file(path);
    QLockFile lock(file.fileName() + "l");
    lock.setStaleLockTime(5000);

    if (lock.tryLock()) {
        qInfo() << "lock";
        // plik zablokowany na 5000ms
        // po wykonaniy operacji odblkokować
        // lock.unlock();
    } else {
        qInfo() << "no lock";
    }
    qInfo() << "done";
    lock.unlock();
}
// -------------------------------------------
void randomGenerator_() {
    QString data;
    for (int i = 0; i < 10; ++i) {
        int gen = QRandomGenerator::global()->bounded(0xffff);
        data.append(QChar(gen));
    }

    qInfo() << "QString utf16 " << data;
    qInfo() << "QString toLatin1 " << data.toLatin1();
    qInfo() << "QString toUtf8 " << data.toUtf8();
    qInfo() << "QString toStdString " << data.toStdString();
    qInfo() << "QString toStdU16String " << data.toStdU16String();
    qInfo() << "QString toStdU32String " << data.toStdU32String();
    qInfo() << "QString toStdWString " << data.toStdWString();
    qInfo() << "QString toLocal8Bit " << data.toLocal8Bit();
    qInfo() << "QString toUcs4 " << data.toUcs4();
    qInfo() << "";

    QString qstr = "std string\r\n";
    qInfo() << "QString " << qstr;
    QByteArray stdStr = qstr.toLatin1();
    qInfo() << "String " << stdStr;
    QByteArray encoded = stdStr.toBase64();
    qInfo() << "String to encoded base64 " << encoded;
    QByteArray hex = stdStr.toHex();
    qInfo() << "String to encoded hex " << hex;
    QByteArray decoded = QByteArray::fromBase64(encoded);
    qInfo() << "QByteArray from Base64 " << decoded;
    QByteArray decodedHex = QByteArray::fromHex(hex);
    qInfo() << "QByteArray from HEX " << decodedHex;
}
// -------------------------------------------
// -------------------------------------------
// -------------------------------------------
// -------------------------------------------

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    // lifecycle();
    // dangling_pointer();
    // smart_poionter();
    // qScopedPointer_();
    // qSharedPointer_();
    // qList_();
    // qSet_();
    // qMap_();
    // qStringList_();
    // qListObj_();
    // qMapObj_();
    // qSettings_();
    // qiodevice_();
    // qFileStreams::qFileStreams_();
    // qFileDataStreams::qFileDataStreams_();
    // dir_();
    // fileinfo_("d:/145_GPS/");
    // storageInfo_();
    // lockFile_();
    randomGenerator_();

    return a.exec();
}
