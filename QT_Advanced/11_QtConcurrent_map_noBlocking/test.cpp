#include "test.h"

Test::Test(QObject *parent) : QObject{parent} {
}

void Test::finished() {
    qInfo() << this << "Processing...";
}
