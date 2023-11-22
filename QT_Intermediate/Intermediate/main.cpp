#include "test.h"
#include <QCoreApplication>

void lifecycle() {
    Test T;
}

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    lifecycle();

    return a.exec();
}
