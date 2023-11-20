#include "a.h"
#include "b.h"
#include "c.h"
#include <QCoreApplication>

void init() {
    A obj1;
    B obj2; // dziedziczy po A
    C obj3; // dziedziczy po B która dziedziczy po A

    // wg klasy A
    obj1.metodaA();

    // wg klasy B z metodami klasy A
    obj2.metodaA();
    obj2.metodaB();

    // wg klasy C z metodami klasy A,B
    obj3.metodaA();
    obj3.metodaB();
    obj3.metodaC();
}

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    init();

    return a.exec();
}
