#include <QCoreApplication>
#include <QThread>

void taskFun() {
    qInfo() << "taskFun" << QThread::currentThread();
}

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    qInfo() << "main start" << QThread::currentThread();

    QThread *task = QThread::create(taskFun);
    task->start();

    qInfo() << "main end" << QThread::currentThread();

    return a.exec();
}
