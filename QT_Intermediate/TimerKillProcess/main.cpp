#include <QCoreApplication>
#include <QProcess>
#include <QTimer>
#include <QThread>


int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    QProcess proc;
    // aplikacja własna bo windowsowe mają jaką blokade że nie można sobie wyłączyć prosesu
    proc.start("d:/__GitHub/DataVisualizer/DataVisualizer/release/DataVisualizer.exe", QStringList() << "\r\n");
    // proc.setProgram("notepad.exe");
    // proc.start();
    // proc.waitForStarted();

    qInfo() << proc.program() << proc.processId();

    QTimer::singleShot(3000, &proc, &QProcess::terminate);
    //proc.kill();

    return a.exec();
}
