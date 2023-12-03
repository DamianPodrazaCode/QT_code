#include <QCoreApplication>
#include <QThread>
#include <QTimer>

// kod asynchrioniczy na jednym wątku

void test() {
    qInfo() << "test" << QThread::currentThread();
}

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    QThread::currentThread()->setObjectName("main");
    qInfo() << "main start" << QThread::currentThread();

    // timer nie uruchamia sie w osobnym wątku
    QTimer timer;
    timer.singleShot(3000, test); //funkcja uruchamia się po 3 sec. nie blokując głównego wątku

    qInfo() << "main end" << QThread::currentThread();

    return a.exec();
}
