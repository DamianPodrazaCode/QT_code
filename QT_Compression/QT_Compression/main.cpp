#include <QCoreApplication>
#include <QDebug>

// zlib, QuaZIP

void display(QString title, QByteArray &tab) {
    qDebug() << "-----" << title << "-----";
    qDebug() << "length -> " << tab.length();
    qDebug() << "data -> " << tab;
}

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    QByteArray data(
        "to jest długi text, bardzo długi,to jest długi text, bardzo długi,to jest długi text, bardzo długi,to jest długi text, bardzo długi,to jest długi text, bardzo długi,to jest długi text, bardzo długi,to jest długi text, bardzo długi,to jest długi text, bardzo długi,to jest długi text, bardzo długi,to jest długi text, bardzo długi,to jest długi text, bardzo długi,to jest długi text, bardzo długi,to jest długi text, bardzo długi,");

    QByteArray compressed9 = qCompress(data, 9);
    QByteArray compressed6 = qCompress(data, 6);
    QByteArray compressed4 = qCompress(data, 4);
    QByteArray compressed2 = qCompress(data, 2);
    QByteArray uncompressed = qUncompress(compressed9);

    display("orginał", data);
    display("po kompresji 9", compressed9);
    display("po kompresji 6", compressed6);
    display("po kompresji 4", compressed4);
    display("po kompresji 2", compressed2);
    display("po dekompresji", uncompressed);

    return a.exec();
}
