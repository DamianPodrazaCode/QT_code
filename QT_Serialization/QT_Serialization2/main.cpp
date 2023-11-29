#include "test.h"
#include <QCoreApplication>
#include <QDebug>
#include <QList>

// qDeleteAll dla klas

void qDelteAll_() {
    QList<test*> lTest;
    for (int i = 0; i < 10; ++i) {
        test *t = new test();
        t->setObjectName(QString::number(i));
        lTest.append(t);
    }
}

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    return a.exec();
}
