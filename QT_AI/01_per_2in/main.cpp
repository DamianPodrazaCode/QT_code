#include "perc2in.h"
#include <QCoreApplication>
#include <QList>

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    Perc2in per1;
    per1.showState();

    return a.exec();
}
