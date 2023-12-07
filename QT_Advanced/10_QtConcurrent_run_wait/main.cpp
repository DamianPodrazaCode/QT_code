#include <QCoreApplication>
#include <QThread>
#include <QThreadPool>
#include <QtConcurrent>
#include <QFuture>

void test(QString name, int max) {
    for (int i = 0; i < max; ++i) {
        qInfo() << name << i << QThread::currentThread();
    }
}

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);
    QThread::currentThread()->setObjectName("main");
    qInfo() << QThread::currentThread();

    QString name = "name";

    //future jest poto żeby kontorlować trwanie wątków, void jest typem zwracanym przez funkcje a parametry są podawane za nazwą funkcji
    QFuture<void> future = QtConcurrent::run(test, name, 5);
    qInfo() << "za run";
    future.waitForFinished(); // czeka na zakończenie wątków, synchronizacja
    qInfo() << "end";
    return a.exec();
}
