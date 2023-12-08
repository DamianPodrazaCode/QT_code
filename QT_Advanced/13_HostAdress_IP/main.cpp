#include <QCoreApplication>
#include <QHostAddress>
#include <QNetworkInterface>
#include <QAbstractSocket>

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    QList<QHostAddress> list1 = QNetworkInterface::allAddresses();
    QList<QNetworkInterface> list2 = QNetworkInterface::allInterfaces();

    // qInfo() << "allAddresses" << list1;
    // qInfo() << "allInterfaces" << list2;

    qInfo() << "allAddresses";
    foreach (QHostAddress var, list1) {
        qInfo() << var;
        qInfo() << var.protocol();
        qInfo() << var.scopeId();
        qInfo() << "";
    }

    qInfo() << "";
    qInfo() << "allInterfaces";
    foreach (QNetworkInterface var, list2) {
        qInfo() << var.humanReadableName();
        qInfo() << var.name();
        qInfo() << var.hardwareAddress();
        qInfo() << var.type();
        qInfo() << var.flags();
        qInfo() << var.addressEntries();
        qInfo() << "";
    }

    return a.exec();
}
