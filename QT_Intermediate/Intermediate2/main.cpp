#include "test.h"
#include <QCoreApplication>
#include <QDebug>
#include <QList>

// qDeleteAll dla klas
// wypełnianie kontenerów
// sortowanie w kontenerach
// porównywanie kontenerów
// kopiowanie kontenerów

void qDeleteAll_() {
    QList<test *> lTest;
    for (int i = 0; i < 10; ++i) {
        test *t = new test();
        t->setObjectName(QString::number(i));
        lTest.append(t);
    }

    qDeleteAll(lTest); // usunięcie objektów, ale nie listy wskaźników
    lTest.clear(); // dopiero teraz znika lista wskaźników
}

void fillCont_() {
    QList<int> lista = {1, 2, 3, 4};
    qInfo() << lista;
    lista.fill(9);
    qInfo() << lista;
    lista.resize(15);
    qInfo() << lista;
    lista.fill(9);
    qInfo() << lista;
    std::fill(lista.begin(), lista.end(), 3);
    qInfo() << lista;
}

void sortCont_() {
    QList<int> list = {123, 432, 12, 65, 765, 98, 101, 234, 5674, 23423, 12, 334, 324, 876};
    qInfo() << list;
    std::sort(list.begin(), list.end());
    qInfo() << list;
    std::reverse(list.begin(), list.end());
    qInfo() << list;
}

void compareCont_() {
    QList<int> list1 = {123, 432, 12, 65, 765, 98, 101, 234, 5674, 23423, 12, 334, 324, 876};
    QList<int> list2 = {223, 452, 62, 885, 65, 9, 11, 24, 45674, 223, 3212, 7334, 5324, 86};
    QList<int> list3 = {123, 432, 12, 65, 765, 98, 101, 234, 5674, 23423, 12, 334, 324, 876};
    qInfo() << list1;
    qInfo() << list2;
    qInfo() << std::equal(list1.begin(), list1.end(), list2.begin()); // false
    qInfo() << std::equal(list1.begin(), list1.end(), list3.begin()); // true
}

void copyCont_() {
    QList<int> list1 = {123, 432, 12, 65, 765, 98, 101, 234, 5674, 23423, 12, 334, 324, 876};
    QList<int> list2;
    qInfo() << list1;
    qInfo() << list2;
    list2.resize(list1.size());
    std::copy(list1.begin(), list1.end(), list2.begin());
    qInfo() << list1;
    qInfo() << list2;
    qInfo() << std::equal(list1.begin(), list1.end(), list2.begin());
}

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

           // qDeleteAll_();
           // fillCont_();
           // sortCont_();
           // compareCont_();
    copyCont_();

    return a.exec();
}
