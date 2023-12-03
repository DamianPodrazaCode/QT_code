#include <QCoreApplication>
#include <QThread>

// wszystko zsynchronizowane w jednym wątku

void test() {
    qInfo() << "test" << QThread::currentThread();
}

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    QThread::currentThread()->setObjectName("main");
    qInfo() << "main" << QThread::currentThread();

    test();

    return a.exec();
}
