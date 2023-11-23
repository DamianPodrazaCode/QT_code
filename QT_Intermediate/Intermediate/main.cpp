#include "test.h"
#include <QCoreApplication>
#include <QList>
#include <QMap>
#include <QScopedPointer>
#include <QSet>
#include <QSharedPointer>
#include <QString>
#include <QStringList>
#include <QSettings>

// new dadgling pointer
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
    QList<Test *> lista;  // klasa Test jest typu QObject i może być tworzona tylko przez wskaźnik
    lista.append(new Test());
    lista.append(new Test());
    lista.append(new Test());
    lista.append(new Test());
    lista.append(new Test());
    qDeleteAll(lista); // usuwa objekty z całej listy
    lista.clear(); // usuwa wskaźniki które pokazywały na nie istniejące już obiekty
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
    qSettings_();

    return a.exec();
}
