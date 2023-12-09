#include <QCoreApplication>
#include <QDebug>
#include <QTcpSocket>

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    QTcpSocket socket;
    socket.connectToHost("httpbin.org", 80);
    //socket.connectToHost("voidrealms.com", 80);
    qInfo() << "connecting ...";

    if (socket.waitForConnected(6000)) {
        qInfo() << "conected, sending request";

        QByteArray data;
        data.append("GET /get HTTP/1.1\r\n");
        //data.append("User-Agent: Mozilla/4.0 (compatibile; MSIE 8.0; Windows NT 6.0; Trident/4.0)\r\n");
        data.append("Host: local\r\n");
        data.append("Connection: Close\r\n");
        data.append("\r\n");

        socket.write(data);
        socket.waitForBytesWritten();

        if (socket.waitForReadyRead(60000)) {
            QByteArray response = socket.readAll();
            qInfo() << "response lenght: " << response.length() << "bytes";
            qInfo() << "response: " << response;
        }

        socket.waitForDisconnected();
        qInfo() << "disconnect";

    } else {
        qInfo() << socket.errorString();
    }


    return a.exec();
}
