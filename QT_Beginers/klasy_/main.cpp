#include <QCoreApplication>
#include "a.h"
#include "b.h"

void initA() {
    A obj1;
    A obj2;
    A obj3;
}

void initB() {
    B obj1(nullptr, "obj1");
    B obj2(nullptr, "obj2");
    B obj3(nullptr, "obj3");
}

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    initA();
    initB();

    return a.exec();
}
