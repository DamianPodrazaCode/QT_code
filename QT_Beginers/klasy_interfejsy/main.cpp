#include <QCoreApplication>
#include "c.h"

// po co ?
// Interfejsy są potrzebne do tworzenia wyższej abstrakcji programu
// klasy A,B są stworzone po to żeby służyć zastępowaniu metod wirtualnych w klasach które po nich dziedziczą
// lepszy porządek w kodzie
// ukrywanie implementacji

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
