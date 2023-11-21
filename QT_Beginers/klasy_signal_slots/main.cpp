#include <QCoreApplication>
#include "tx.h"
#include "rx.h"

void init() {

    Tx nadajnik;
    Rx odbiornik;

    odbiornik.connect(&nadajnik, SIGNAL(info_singnal(QString)), &odbiornik, SLOT(info_slot(QString)));
    //nadajnik.connect(&nadajnik, SIGNAL(info_singnal(QString)), &odbiornik, SLOT(info_slot(QString)));
    //QObject::connect(&nadajnik, &Tx::info_singnal, &odbiornik, &Rx::info_slot);
    //QObject::connect(&nadajnik, SIGNAL(info_singnal(QString)), &odbiornik, SLOT(info_slot(QString)));

    nadajnik.start(); // jeżeli pójdzie przez emit to będzie sender
    odbiornik.info_slot("z main "); // jeżeli pójdzie bezpośrednio to sender będzie 0x0

    QObject::disconnect(&nadajnik, SIGNAL(info_singnal(QString)), &odbiornik, SLOT(info_slot(QString)));

}

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    init();

    return a.exec();
}
