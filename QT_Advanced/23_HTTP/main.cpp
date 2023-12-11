#include "worker.h"
#include <QCoreApplication>

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    Worker worker;

    //GET
    worker.get("https://postman-echo.com/get?foo1=bar1&foo2=bar2");

    //POST
    QByteArray data;
    data.append("param1=hello");
    data.append("&");
    data.append("param2=foo");
    worker.post("https://postman-echo.com/post", data);

    return a.exec();
}
