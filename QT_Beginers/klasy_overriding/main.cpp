#include <QCoreApplication>
#include <c.h>

void init() {
    C obj;          // klasa C dzidziczy po klasie B a ta po klasie A
    obj.metodaA1(); // metoda przeciążona z C
    obj.metodaA2(); // metoda przeciążona z A
    obj.metodaB1(); // metoda przeciążona z C
    obj.metodaB2(); // metoda przeciążona z B
}

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    init();

    return a.exec();
}
