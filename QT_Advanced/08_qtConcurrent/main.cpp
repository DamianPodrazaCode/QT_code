#include <QCoreApplication>
#include <QtConcurrent>

int do_map(int value) {
    qInfo() << "do stuff: " << value;
    int num = value * 10;
    return num;
}

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    QList<int> values;
    values << 0 << 1 << 2 << 3 << 4 << 5 << 6 << 7 << 8 << 9;

    qInfo() << "Starting";
    QList<int> updated = QtConcurrent::blockingMapped(values, &do_map); //wykona do_map na wszystkich elementach listy pokolei, w tym samym wątku
    qInfo() << "Finished";

    return a.exec();
}
