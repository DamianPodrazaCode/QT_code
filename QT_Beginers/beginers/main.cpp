// qInfo()
// enum
// struct
// array
// cout cin cerr
// qDebug
// operator ?: (ternary)

#include <QCoreApplication>
#include <QDebug>
#include <array>
#include <iostream>

// ------------------------------------------------
void enum_() {
    enum Color {
        red,
        green,
        blue,
        redH = 0xff0000,
        greenH = 0x00ff00,
        blueH = 0x0000ff
    };

    Color myColor = Color::blue;

    qInfo() << "myColor = " << myColor;
    qInfo() << red << redH;
    qInfo("%x %x %x", redH, greenH, blueH);
}
// ------------------------------------------------
void struct_() {
    struct test {
        int aaa = 0;
        float bbb = 10.12345;
        test() { // konstruktor struktury
            aaa = 1;
            bbb = 1.12;
            qInfo() << this << "konstruktor";
        }
        ~test() { // destruktor struktury
            qInfo() << this << "destruktor";
        }
        void start() { // metoda struktury
            qInfo() << this << "metoda start";
        }
    };
    test myStruct;
    qInfo() << myStruct.aaa << myStruct.bbb;
    myStruct.start();
    // struktura działa taksamo jak klasa poza tym że domyślnie klasa jest private a struktura public
    // dziedziczenie, polimorfizm, przeciążeni, wirtualizacja i inne są takiesame jak w klasach
}
// ------------------------------------------------
void array_() {
    using namespace std;
    array<int, 5> tab; // stałowymiarowy bufor
    // array<int, 5> tab = {1,2,3,4,5};  // z inicjalizacją

    tab.at(0) = 10;
    tab[1] = 2;
    // tab[5] = 10; // tego błędu program nie wykryje
    // tab.at(5) = 10; //błąd na poziomie wykonywania programu, wyśweitlany w terminalu
    qInfo() << "Ilość elementów tablicy - " << tab.size() << ". Ilość bajtów tablicy - " << sizeof(tab) << ". Element 0 - " << tab.at(0);
}
// ------------------------------------------------
void cout_cin_cerr() {
    using namespace std;
    cout << "cout " << endl;

    int in;
    cin >> in;
    cout << in << endl;

    cerr << "cerr" << endl;
}
// ------------------------------------------------
void qdebug_() {
    qInfo() << "qInfo";
    qDebug() << "qDebug";
    qWarning() << "qWarning";
    qCritical() << "qCritical";
    qFatal("qFatal");  // przerywa aplikacje
}
// ------------------------------------------------
void ternary() {
    int a = 10;
    int b = 20;
    qInfo() << (a < b ? "true" : "false");
    qInfo() << (a > b ? "true" : "false");
}
// ------------------------------------------------
// ------------------------------------------------
// ------------------------------------------------
// ------------------------------------------------
// ------------------------------------------------
// ------------------------------------------------
// ------------------------------------------------
// ------------------------------------------------

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);


    // enum_();
    // struct_();
    // array_();
    // cout_cin_cerr();
    // qdebug_();
    ternary();

    return a.exec();
}
