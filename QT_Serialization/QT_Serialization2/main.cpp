#include "test.h"
#include <QCoreApplication>
#include <QDebug>
#include <QList>

// qDeleteAll dla klas

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

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    qDeleteAll_();

    return a.exec();
}
