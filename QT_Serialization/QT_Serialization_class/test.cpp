#include "test.h"

Test::Test(QObject* parent) : QObject{parent} {
    qInfo() << "konstruktor " << this << Q_FUNC_INFO;
}

Test::~Test() {
    qInfo() << "dekonstruktor " << this << Q_FUNC_INFO;
}

void Test::fill() {
    m_map.insert("1", "q");
    m_map.insert("2", "w");
    m_map.insert("3", "e");
    m_map.insert("4", "r");
    m_map.insert("5", "t");
    m_map.insert("6", "y");
    m_map.insert("7", "u");
    m_name = "tester";
}

QMap<QString, QString> Test::map() {
    return m_map;
}

QString Test::name() {
    return m_name;
}

void Test::setName(QString& newName) {
    m_name = newName;
}
