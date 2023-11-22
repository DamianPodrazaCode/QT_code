#include "test.h"
#include <QCoreApplication>

// new dadgling pointer

void lifecycle() {
    Test T;
}

void dangling_pointer() {
    Test *pTest = new Test();
    pTest->work();
    delete pTest;

    pTest = nullptr;
    //if (pTest != nullptr)
        pTest->work(); // ten pointer jest podpięty do nieistniejącego objektu
}

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    // lifecycle();
    dangling_pointer();

    return a.exec();
}
