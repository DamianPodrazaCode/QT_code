// qInfo()
// enum
// struct
// array
// cout cin cerr
// qDebug
// operator ?: (ternary)
// Q_FUNC_INFO -> zwraca nazwę funkcji, metody
// unique_ptr -> automatyczny wskaźnik
// rzutowanie zmiennych i objektów
// Exeption

#include "cast1.h"
#include "cast2.h"
#include "cast3.h"
#include "test1.h"
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
    qFatal("qFatal"); // przerywa aplikacje
}
// ------------------------------------------------
void ternary() {
    int a = 10;
    int b = 20;
    qInfo() << (a < b ? "true" : "false");
    qInfo() << (a > b ? "true" : "false");
}
// ------------------------------------------------
void qFunInfo_() {
    qInfo() << Q_FUNC_INFO; // nazwa wykonywanej funkcji
}
// ------------------------------------------------
void uniquePTR() {
    // zwykłe tworzenie na stercie
    Test1 *obj1 = new Test1();
    obj1->metoda1();
    delete obj1;
    qInfo() << "";

    // automatyczny wskażnik na stercie
    std::unique_ptr<Test1> obj2 = std::make_unique<Test1>();
    obj2->metoda1();
    qInfo() << "";
    // Próba przypisania lub skopiowania std::unique_ptr prowadzi do błędu kompilacji, co pomaga zapobiegać wyciekom pamięci.

    // objekt na stosie
    Test1 obj3;
    obj3.metoda1();
    qInfo() << "";
}
// ------------------------------------------------
void casting_() {
    double value = 1.23;
    // Implicit - niejawna konwersja
    int out = value;
    qInfo() << out;
    // Explicit - jawna konwersja
    out = (int)value;
    qInfo() << out;

    {
        // Dynamic casting,
        qInfo() << "";
        qInfo() << "Dynamic casting";
        // rzutowanie z możliwą utratą danych, możliwe tylko między klasami dziedziczącymi,
        // trzeba pamiętać że w tym przypadku obiekt jest cały czas ten sam, rzutowanie następuje tylko pomiędzy wskaźnikami
        // sprawdzanie rzutowania na poziomie programu
        Cast2 *obj1 = new Cast2(); // tworzenie objektu z klasy Cast2 która dzidziczy po Cast1, i zawiera didatkowe metody i pola

        Cast1 *obj2 = dynamic_cast<Cast1 *>(obj1); // rzutowanie na nowy wskażnik innego typu, obj1 dziedziczy po obj2
        if (obj2) {
            qInfo() << "utworzony" << obj2;
            obj2->metoda1();
            obj2->metoda2();
        } else {
            qInfo() << "nie utworzony" << obj2;
        }

        Cast3 *obj3 = dynamic_cast<Cast3 *>(obj1); // rzutowanie na nowy wskażnik innego typu, obj3 jest całkowicie inny niż obj1
        if (obj3) {
            qInfo() << "utworzony" << obj3;
        } else {
            qInfo() << "nie utworzony" << obj3;
        }

        Cast2 *obj4 = dynamic_cast<Cast2 *>(obj2); // rzutowanie na nowy wskażnik innego typu, obj1 dziedziczy po obj2
        if (obj4) {
            qInfo() << "utworzony" << obj4;
            obj4->metoda3();
            obj4->metoda1();
            obj4->metoda2();
        } else {
            qInfo() << "nie utworzony" << obj4;
        }
        delete obj1;
    }
    {
        // Static casting,
        // nowy_typ_wynikowy = static_cast<nowy_typ_wynikowy>(wyrażenie_do_rzutowania);
        qInfo() << "";
        qInfo() << "Static casting";
        // rzutowanie z możliwą utratą danych, możliwe tylko między klasami dziedziczącymi,
        // trzeba pamiętać że w tym przypadku obiekt jest cały czas ten sam, rzutowanie następuje tylko pomiędzy wskaźnikami
        // sprawdzanie rzutowania na poziomie kompilatora
        Cast2 *obj1 = new Cast2(); // tworzenie objektu z klasy Cast2 która dzidziczy po Cast1, i zawiera didatkowe metody i pola

        Cast1 *obj2 = static_cast<Cast1 *>(obj1); // rzutowanie na nowy wskażnik innego typu, obj1 dziedziczy po obj2
        if (obj2) {
            qInfo() << "utworzony" << obj2;
        } else {
            qInfo() << "nie utworzony" << obj2;
        }

        // błąd kompilatora
        // Cast3 *obj3 = static_cast<Cast3 *>(obj1); // rzutowanie na nowy wskażnik innego typu, obj3 jest całkowicie inny niż obj1
        // if (obj3)
        // qInfo() << "utworzony" << obj3;
        // else
        // qInfo() << "nie utworzony" << obj3;

        Cast2 *obj4 = static_cast<Cast2 *>(obj2); // rzutowanie na nowy wskażnik innego typu, obj1 dziedziczy po obj2
        if (obj4) {
            qInfo() << "utworzony" << obj4;
        } else {
            qInfo() << "nie utworzony" << obj4;
        }
        delete obj1;
    }
    {
        // Reinpreted casting,
        // nowy_typ_wynikowy = reinterpret_cast<nowy_typ_wynikowy>(wyrażenie_do_rzutowania);
        qInfo() << "";
        qInfo() << "Reinpreted casting";
        // rzutowanie z możliwą utratą danych, możliwe każde rzutowanie,
        // trzeba pamiętać że w tym przypadku obiekt jest cały czas ten sam, rzutowanie następuje tylko pomiędzy wskaźnikami
        // sprawdzanie rzutowania na poziomie programu
        Cast2 *obj1 = new Cast2(); // tworzenie objektu z klasy Cast2 która dzidziczy po Cast1, i zawiera didatkowe metody i pola

        Cast1 *obj2 = reinterpret_cast<Cast1 *>(obj1); // rzutowanie na nowy wskażnik innego typu, obj1 dziedziczy po obj2
        if (obj2) {
            qInfo() << "utworzony" << obj2;
        } else {
            qInfo() << "nie utworzony" << obj2;
        }

        Cast3 *obj3 = reinterpret_cast<Cast3 *>(obj1); // rzutowanie na nowy wskażnik innego typu, obj3 jest całkowicie inny niż obj1
        if (obj3) {
            qInfo() << "utworzony" << obj3;
            obj3->metodaA();
            obj3->metodaB();
            obj3->metodaC();
        } else {
            qInfo() << "nie utworzony" << obj3;
        }

        Cast2 *obj4 = reinterpret_cast<Cast2 *>(obj2); // rzutowanie na nowy wskażnik innego typu, obj1 dziedziczy po obj2
        if (obj4) {
            qInfo() << "utworzony" << obj4;
        } else {
            qInfo() << "nie utworzony" << obj4;
        }
        delete obj1;

        double data1 = 1.987;
        double *ptr_data1 = &data1;

        uint32_t *ptr_data2 = reinterpret_cast<uint32_t *>(ptr_data1);
        qInfo() << *ptr_data1;
        qInfo("%x", *ptr_data2);
    }
    {
        // QOBJECT casting,
        // T *qobject_cast<T>(QObject *object);
        qInfo() << "";
        qInfo() << "QObject casting";
        // rzutowanie z możliwą utratą danych, możliwe rzutowanie tylko na objektach dzidziczących po QOBJECT,
        // trzeba pamiętać że w tym przypadku obiekt jest cały czas ten sam, rzutowanie następuje tylko pomiędzy wskaźnikami
        // sprawdzanie rzutowania na poziomie programu
        Cast2 *obj1 = new Cast2(); // tworzenie objektu z klasy Cast2 która dzidziczy po Cast1, i zawiera didatkowe metody i pola

        Cast1 *obj2 = qobject_cast<Cast1 *>(obj1); // rzutowanie na nowy wskażnik innego typu, obj1 dziedziczy po obj2
        if (obj2) {
            qInfo() << "utworzony" << obj2;
        } else {
            qInfo() << "nie utworzony" << obj2;
        }

        Cast3 *obj3 = qobject_cast<Cast3 *>(obj1); // rzutowanie na nowy wskażnik innego typu, obj3 jest całkowicie inny niż obj1
        if (obj3) {
            qInfo() << "utworzony" << obj3;
        } else {
            qInfo() << "nie utworzony" << obj3;
        }

        Cast2 *obj4 = qobject_cast<Cast2 *>(obj2); // rzutowanie na nowy wskażnik innego typu, obj1 dziedziczy po obj2
        if (obj4) {
            qInfo() << "utworzony" << obj4;
        } else {
            qInfo() << "nie utworzony" << obj4;
        }
        delete obj1;
    }
}
// ------------------------------------------------
void exeption_() {
    int aaa = 10;
    int bbb = 6;
    try {
        if (bbb == 0)
            throw QString("dzielenie przez zero.");
        if (bbb == 5)
            throw 5;
        qInfo() << "ok";
        qInfo() << aaa / bbb;
    } catch (QString e) {
        qInfo() << e;
        return;
    } catch (int e) {
        qInfo() << e;
        return;
    }

    //    try {
    //        // Kod, w którym może wystąpić wyjątek
    //        throw std::runtime_error("To jest wyjątek!");
    //    } catch (const std::exception &e) {
    //        // Obsługa wyjątku std::exception lub jego pochodnych
    //        std::cerr << "Złapany wyjątek: " << e.what() << std::endl;
    //    } catch (...) {
    //        // Obsługa innych typów wyjątków
    //        std::cerr << "Złapany inny wyjątek." << std::endl;
    //    }
}
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
    // ternary();
    // qFunInfo_();
    // uniquePTR();
    // casting_();
    // exeption_();

    return a.exec();
}
