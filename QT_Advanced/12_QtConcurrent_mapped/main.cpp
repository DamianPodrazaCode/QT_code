#include <QCoreApplication>
#include <QDebug>
#include <QFuture>
#include <QFutureWatcher>
#include <QList>
#include <QtConcurrent>

int do_map(int value) {
    qInfo() << "do stuff: " << value << QThread::currentThread();
    int num = value * 10;
    return num;
}

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    QList<int> list;
    for (int i = 0; i < 100; ++i) {
        list << i;
    }

    //QFutureWatcher<int> watcher; // potrzebny co connect
    QFuture<int> future = QtConcurrent::mapped(list, &do_map);
    qInfo() << "za mapped";
    //watcher.setFuture(future);

    //watcher.waitForFinished();
    future.waitForFinished();
    qInfo() << "za wait";

    // wymusi wait
    qInfo() << future.results();

    qInfo() << list;

    return a.exec();
}
