#include <QCoreApplication>
#include <QDebug>
#include <QTimer>

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    for (int var = 0; var < argc; ++var) {
        qInfo() << "arg nr." << var << " : " << argv[var];
    }

    QTimer::singleShot(3000, &a, SLOT(quit()));

    int code = a.exec();
    qInfo() << code;
    return code;
}
