#include "server.h"

Server::Server(QObject *parent) : QTcpServer{parent} {
}

void Server::setCert(QString value) {
    certPath = value;
}

void Server::setKey(QString value) {
    keyPath = value;
}

void Server::disconnected() {
    QSslSocket *socket = qobject_cast<QSslSocket *>(sender());
    qInfo() << "Disconnected" << socket;
    socket->deleteLater();
}

void Server::readyRead() {
    QSslSocket *socket = qobject_cast<QSslSocket *>(sender());
    qInfo() << "readyRead" << socket;
    qInfo() << socket->readAll();

    QByteArray data("Hello World!!!\r\n");
    QByteArray respone;
    respone.append("HTTP/1.1 200 OK\r\n");
    respone.append("Content-Type: text/plain\r\n");
    respone.append("Content-Lenght: " + QString::number(data.length()).toUtf8() + "\r\n");
    respone.append("Connection: close\r\n");
    respone.append("\r\n");
    respone.append(data);

    socket->write(respone);
    socket->waitForBytesWritten();
    socket->close();
    socket->deleteLater();
}

void Server::encrypted() {
    QSslSocket *socket = qobject_cast<QSslSocket *>(sender());
    qInfo() << "encrypted" << socket;
}

void Server::encryptedBytesWritten(qint64 written) {
    QSslSocket *socket = qobject_cast<QSslSocket *>(sender());
    qInfo() << "encryptedBytesWritten" << socket << written;
}

void Server::modeChanged(QSslSocket::SslMode mode) {
    QSslSocket *socket = qobject_cast<QSslSocket *>(sender());
    qInfo() << "modeChanged" << socket << mode;
}

void Server::peerVerifyError(const QSslError &error) {
    QSslSocket *socket = qobject_cast<QSslSocket *>(sender());
    qInfo() << "peerVerifyError" << socket << error;
}

void Server::sslErrors(const QList<QSslError> &errors) {
    QSslSocket *socket = qobject_cast<QSslSocket *>(sender());
    qInfo() << "sslErrors" << socket;
    socket->ignoreSslErrors(errors);
}

void Server::socketError(QAbstractSocket::SocketError err) {
    QMetaEnum metaenum = QMetaEnum::fromType<QAbstractSocket::SocketError>();
    QSslSocket *socket = qobject_cast<QSslSocket *>(sender());
    qInfo() << "SocketError" << socket << metaenum.valueToKey(err);
}

void Server::incomingConnection(qintptr handle) {
    qInfo() << "incomming connection " << handle;
    QSslSocket *socket = new QSslSocket(this);

    connect(socket, &QSslSocket::disconnected, this, &Server::disconnected);
    connect(socket, &QSslSocket::readyRead, this, &Server::readyRead);
    connect(socket, &QSslSocket::encrypted, this, &Server::encrypted);
    connect(socket, &QSslSocket::encryptedBytesWritten, this, &Server::encryptedBytesWritten);
    connect(socket, &QSslSocket::modeChanged, this, &Server::modeChanged);
    connect(socket, &QSslSocket::peerVerifyError, this, &Server::peerVerifyError);
    connect(socket, QOverload<const QList<QSslError> &>::of(&QSslSocket::sslErrors), this, &Server::sslErrors);
    connect(socket, &QSslSocket::errorOccurred, this, &Server::socketError);

    qInfo() << "Connected" << socket;
    socket->setSocketDescriptor(handle);
    socket->setLocalCertificate(certPath, QSsl::Pem);
    socket->setPrivateKey(keyPath, QSsl::Rsa, QSsl::Pem);
    socket->setPeerVerifyMode(QSslSocket::VerifyNone);

    QList<QSslCertificate> localChain;
    QSslCertificate cert;
    cert.fromPath(certPath);
    localChain.append(cert);
    socket->setLocalCertificateChain(localChain);

    socket->setProtocol(QSsl::SslProtocol::TlsV1_2);
    socket->startServerEncryption();
}
