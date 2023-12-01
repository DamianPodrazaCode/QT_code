#include "proccomm.h"

ProcComm::ProcComm(QObject *parent) : QObject{parent} {
    // QSysInfo info;
    // linux
    app = "bash";
    endl = "\n";
#ifdef Q_OS_WIN
    // windows
    app = "cmd";
    endl = "\r\n";
#elif Q_OS_MACOS
    // mac
    app = "zsh";
    endl = "\n";
#endif
    proc.setProgram(app);
    proc.start();
    connect(&proc, &QProcess::readyRead, this, &ProcComm::readyRead);
    connect(&proc, &QProcess::readyReadStandardOutput, this, &ProcComm::readyRead);
    connect(&proc, &QProcess::readyReadStandardError, this, &ProcComm::readyRead);
}

ProcComm::~ProcComm() {
    if (proc.isOpen())
        proc.close();
}

void ProcComm::readyRead() {
    qint64 value = 0;
    do {
        QByteArray line = proc.readAll();
        qInfo() << line;
        value = line.length();
    } while (value > 0);
}

void ProcComm::action(QByteArray data) {
    if (!data.endsWith(endl.toLatin1()))
        data.append(endl.toUtf8());
    proc.write(data);
    proc.waitForBytesWritten(1000);
}
