#include <QCoreApplication>
#include <QDebug>
#include <QFuture>
#include <QThread>
#include <QtConcurrent>

int test() {
    QThread *thread = QThread::currentThread();
    qInfo() << thread;

    int value = 0;
    for (int i = 0; i < 10; i++) {
        qInfo() << i << "on" << thread;
        value += 1;
    }
    qInfo() << thread;
    return value;
}

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    QFuture<int> future1 = QtConcurrent::run(&test);
    QFuture<int> future2 = QtConcurrent::run(&test);
    QFuture<int> future3 = QtConcurrent::run(&test);
    QFuture<int> future4 = QtConcurrent::run(&test);

    qInfo() << future1.result();
    qInfo() << future2.result();
    qInfo() << future3.result();
    qInfo() << future4.result();

    return a.exec();
}
