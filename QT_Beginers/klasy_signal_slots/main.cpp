#include <QCoreApplication>
#include "tx.h"
#include "rx.h"

void init() {
    Tx nadajnik;
    Rx odbiornik;

    QObject::connect(&nadajnik, SIGNAL(info_singnal(QString)), &odbiornik, SLOT(info_slot(QString)));

    nadajnik.start();
    odbiornik.info_slot("z main ");

    QObject::disconnect(&nadajnik, SIGNAL(info_singnal(QString)), &odbiornik, SLOT(info_slot(QString)));
}

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    init();

    return a.exec();
}
