#include <QCoreApplication>
#include "c.h"

void init() {
    C obj1;
    obj1.makeA();
    obj1.makeB();
}

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    init();

    return a.exec();
}
