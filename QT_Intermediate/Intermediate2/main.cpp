#include "test.h"
#include "proccomm.h"
#include <QCoreApplication>
#include <QDebug>
#include <QList>
#include <QProcess>
#include <QSysInfo>

// qDeleteAll dla klas
// wypełnianie kontenerów
// sortowanie w kontenerach
// porównywanie kontenerów
// kopiowanie kontenerów
// biblioteka BOOST <<<<<<<<<<<<<<<< open source <<<<<<<<<<<<<<<
// qSystemInfo
// qProcess
// qProcess execute

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

void fillCont_() {
    QList<int> lista = {1, 2, 3, 4};
    qInfo() << lista;
    lista.fill(9);
    qInfo() << lista;
    lista.resize(15);
    qInfo() << lista;
    lista.fill(9);
    qInfo() << lista;
    std::fill(lista.begin(), lista.end(), 3);
    qInfo() << lista;
}

void sortCont_() {
    QList<int> list = {123, 432, 12, 65, 765, 98, 101, 234, 5674, 23423, 12, 334, 324, 876};
    qInfo() << list;
    std::sort(list.begin(), list.end());
    qInfo() << list;
    std::reverse(list.begin(), list.end());
    qInfo() << list;
}

void compareCont_() {
    QList<int> list1 = {123, 432, 12, 65, 765, 98, 101, 234, 5674, 23423, 12, 334, 324, 876};
    QList<int> list2 = {223, 452, 62, 885, 65, 9, 11, 24, 45674, 223, 3212, 7334, 5324, 86};
    QList<int> list3 = {123, 432, 12, 65, 765, 98, 101, 234, 5674, 23423, 12, 334, 324, 876};
    qInfo() << list1;
    qInfo() << list2;
    qInfo() << std::equal(list1.begin(), list1.end(), list2.begin()); // false
    qInfo() << std::equal(list1.begin(), list1.end(), list3.begin()); // true
}

void copyCont_() {
    QList<int> list1 = {123, 432, 12, 65, 765, 98, 101, 234, 5674, 23423, 12, 334, 324, 876};
    QList<int> list2;
    qInfo() << list1;
    qInfo() << list2;
    list2.resize(list1.size());
    std::copy(list1.begin(), list1.end(), list2.begin());
    qInfo() << list1;
    qInfo() << list2;
    qInfo() << std::equal(list1.begin(), list1.end(), list2.begin());
}

void qSystemInfo_() {
    QSysInfo sys;
    qInfo() << sys.currentCpuArchitecture();
    qInfo() << sys.buildCpuArchitecture();
    qInfo() << sys.buildAbi();
    qInfo() << sys.kernelType();
    qInfo() << sys.productVersion();
    qInfo() << sys.machineHostName();
    qInfo() << sys.prettyProductName();
    qInfo() << sys.machineUniqueId();
    qInfo() << sys.bootUniqueId();
    qInfo() << sys.kernelVersion();
    qInfo() << sys.productType();
}

void qProcess_() {
    QProcess proc;
    proc.start("notepad.exe");
    qInfo() << proc.processId();
    proc.waitForFinished();
}

void qProcessExe_() {
    QProcess proc;
    proc.execute("calc.exe");
    qInfo() << proc.exitCode();
}

ProcComm cmd;
void qProcessCommand_() {
    // ProcComm cmd;
    cmd.action(QByteArray("arp"));
    cmd.action(QByteArray("calc"));
    cmd.action(QByteArray("d:/__GitHub/DataVisualizer/DataVisualizer/release/DataVisualizer.exe"));
}

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    // qDeleteAll_();
    // fillCont_();
    // sortCont_();
    // compareCont_();
    // copyCont_();
    // qSystemInfo_();
    // qProcess_();
    // qProcessExe_();
    // qProcessCommand_();

    return a.exec();
}
