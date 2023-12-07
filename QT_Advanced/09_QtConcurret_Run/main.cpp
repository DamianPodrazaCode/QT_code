#include <QCoreApplication>
#include <QThread>
#include <QThreadPool>
#include <QtConcurrent>

void loop() {
    for (int i = 0; i < 10; ++i) {
        qInfo() << "loop " << i << "on: " << QThread::currentThread();
    }
}

void test() {
    qInfo() << "test: " << QThread::currentThread();
    loop();
}

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    QThread::currentThread()->setObjectName("main");

    QThreadPool pool;
    QFuture<void> future = QtConcurrent::run(&pool, test);
    qInfo() << "main: " << QThread::currentThread();

    return a.exec();
}
