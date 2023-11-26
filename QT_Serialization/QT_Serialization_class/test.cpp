#include "test.h"

Test::Test(QObject* parent) : QObject{parent} {
    qInfo() << "konstruktor " << this << Q_FUNC_INFO;
}

Test::~Test() {
    qInfo() << "dekonstruktor " << this << Q_FUNC_INFO;
}

void Test::fill() {
    map.insert("1", "q");
    map.insert("2", "w");
    map.insert("3", "e");
    map.insert("4", "r");
    map.insert("5", "t");
    map.insert("6", "y");
    map.insert("7", "u");
}

QString Test::name() const {
    return m_name;
}

void Test::setName(const QString& newName) {
    m_name = newName;
}
