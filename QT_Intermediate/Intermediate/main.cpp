#include "test.h"
#include <QCoreApplication>
#include <QScopedPointer>
#include <QSharedPointer>
#include <QList>
#include <QString>
#include <QSet>

// new dadgling pointer
// smart poionter
// QScopedPointer
// QSharedPointer
// dynamic array QList
// fast lookup QSet

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
    qSet_();

    return a.exec();
}
