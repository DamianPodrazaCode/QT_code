#include <QCoreApplication>
#include <QProcess>
#include <QTimer>

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    QProcess proc;
    proc.start("calc");
    // proc.setProgram("notepad.exe");
    // proc.start();
    // proc.waitForStarted();
    //uint32_t id = proc.processId();
    qInfo() << proc.program() << proc.processId();

    QTimer::singleShot(3000, &proc, &QProcess::kill);
    // proc.kill();

    return a.exec();
}
