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
// Templates
// qTimer
// Date Time
// qint
// QString
// QByteArray, Encoding, Decoding
// QVariant
// QMap

#include "cast1.h"
#include "cast2.h"
#include "cast3.h"
#include "mytimer.h"
#include "test1.h"
#include <QByteArray>
#include <QCoreApplication>
#include <QDate>
#include <QDateTime>
#include <QDebug>
#include <QMap>
#include <QString>
#include <QThread>
#include <QTime>
#include <QTimer>
#include <QVariant>
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
    // dziedziczenie, polimorfizm, przeciążeni, wirtualizacja i inne są takie same jak w klasach
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
// typename == class
template <typename T>
void fun(T value) {
    qInfo() << value;
}

template <class T, class A, class B>
T add(A in1, B in2) {
    return in1 + in2;
}

void template_() {
    int aaa = 10;
    double bbb = 20.123;
    QString ccc = "ok str";
    fun<int>(aaa);
    fun<double>(bbb);
    fun<QString>(ccc);

    qInfo() << (double)add<double, int, double>(10, 123.123);
}
// ------------------------------------------------
MyTimer myTimer;
void timer_() {
    myTimer.start();
}
// ------------------------------------------------
void dateTime_() {
    QDate dzisiaj = QDate::currentDate();
    qInfo() << dzisiaj //
            << dzisiaj.toString(Qt::DateFormat::ISODate) //
            << dzisiaj.toString(Qt::DateFormat::ISODateWithMs) //
            << dzisiaj.toString(Qt::DateFormat::RFC2822Date) //
            << dzisiaj.toString(Qt::DateFormat::TextDate);

    QTime czas = QTime::currentTime();
    qInfo() << czas //
            << czas.toString(Qt::DateFormat::ISODate) //
            << czas.toString(Qt::DateFormat::ISODateWithMs) //
            << czas.toString(Qt::DateFormat::RFC2822Date) //
            << czas.toString(Qt::DateFormat::TextDate);

    QDateTime teraz = QDateTime::currentDateTime();
    qInfo() << teraz //
            << teraz.toString(Qt::DateFormat::ISODate) //
            << teraz.toString(Qt::DateFormat::ISODateWithMs) //
            << teraz.toString(Qt::DateFormat::RFC2822Date) //
            << teraz.toString(Qt::DateFormat::TextDate);
}
// ------------------------------------------------
void qint_() {
    qint8 val8 = 0;
    qint16 val16 = 0;
    qint32 val32 = 0;
    qint64 val64 = 0;
    qint128 val128 = 0;
    qintptr *intPtr = &val64;
    qint128 *p_val128 = &val128;
    int *aaa = &val32;
    qInfo() << sizeof(val8) << sizeof(val16) << sizeof(val32) << sizeof(val64) << sizeof(val128) << sizeof(p_val128) << sizeof(intPtr)
            << sizeof(aaa);
}
// ------------------------------------------------
void qstring_() {
    QString str = "1q 2w 3e 4r 5t";
    qInfo() << str;
    qInfo() << str.mid(2, 6);
    qInfo() << str.split(" ");
    qInfo() << str.at(0);
    qInfo() << str.capacity();
    qInfo() << str.length();
    qInfo() << str.contains("2w");
    qInfo() << str.toUpper();
}
// ------------------------------------------------
void qbytearray_() {
    QString str = "1q 2w 3e 4r 5t";
    qInfo() << str;
    QByteArray buffer = str.toLatin1();
    qInfo() << buffer;
    qInfo() << buffer.replace(" ", ".");
    qInfo() << buffer.rightJustified(30, '*');

    // encoding
    QByteArray bufferEncoding = buffer.toBase64();
    qInfo() << bufferEncoding;
    // decoding
    qInfo() << QByteArray::fromBase64(bufferEncoding);

    // to HEX
    QByteArray bufferEncodingHex = bufferEncoding.toHex();
    qInfo() << bufferEncodingHex;
    // from HEX
    qInfo() << QByteArray::fromHex(bufferEncodingHex);
}
// ------------------------------------------------
void qvariant_() {
    // typ nieokreślony (zgadywany)
    QVariant val1 = 1;
    QVariant val2 = 2.123;
    QVariant val3 = "sadfasdf";
    qInfo() << val1 << val2 << val3;
    qInfo() << (QVariant)val1.toDouble();
    qInfo() << (QVariant)val2.toInt();
}
// ------------------------------------------------
void qmap_() {
    QMap<QString, int> mapa;
    mapa["one"] = 1;
    mapa["qwert"] = 123;
    mapa["three"] = 3;
    mapa["seven"] = 7;
    qInfo() << mapa;
    mapa.insert("asd", 43);
    qInfo() << mapa;
    mapa.insert("zasd", 143);
    qInfo() << mapa;
}
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
    // template_();
    // timer_();
    // dateTime_();
    // qint_();
    // qstring_();
    // qbytearray_();
    // qvariant_();
    qmap_();

           // return 0;
    return a.exec();
}
