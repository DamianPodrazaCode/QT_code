#include "test.h"
#include <QCoreApplication>
#include <QDebug>
#include <QFuture>
#include <QFutureWatcher>
#include <QList>
#include <QtConcurrent>

void do_map(int value) {
    qInfo() << "do stuff: " << value << QThread::currentThread();
}

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    QList<int> list;
    for (int i = 0; i < 100000; ++i) {
        list << i;
    }

    // FutureWatcher - nadzoruje co się dzieje z wątkiem
    QFutureWatcher<void> watcher; // "void" jest od funkcji do_map
    Test test;                    // poto żeby powiązać z FutureWatcher

    // powiązanie jak wątek skończy to ma zareagować
    QObject::connect(&watcher, &QFutureWatcher<void>::finished, &test, &Test::finished);

    // map jest void, bez zwrotu
    QFuture<void> future = QtConcurrent::map(list, &do_map); // każde wywołanie do_map będzie na innynm wątku
    qInfo() << "za map";
    watcher.setFuture(future);
    qInfo() << "za setFuture";

    watcher.waitForFinished();
    qInfo() << "za wait";

    qInfo() << list;

    return a.exec();
}
