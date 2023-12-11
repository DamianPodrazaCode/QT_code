#include "worker.h"

Worker::Worker(QObject* parent) : QObject{parent} {
    connect(&manager, &QNetworkAccessManager::authenticationRequired, this, &Worker::authenticationRequired);
    connect(&manager, &QNetworkAccessManager::encrypted, this, &Worker::encrypted);
    connect(&manager, &QNetworkAccessManager::preSharedKeyAuthenticationRequired, this, &Worker::preSharedKeyAuthenticationRequired);
    connect(&manager, &QNetworkAccessManager::proxyAuthenticationRequired, this, &Worker::proxyAuthenticationRequired);
    connect(&manager, &QNetworkAccessManager::sslErrors, this, &Worker::sslErrors);
}

Worker::~Worker() {
}

void Worker::get(QString location) {
    qInfo() << "Getting from server ...";
    QNetworkReply* replay = manager.get(QNetworkRequest(QUrl(location)));
    connect(replay, &QNetworkReply::readyRead, this, &::Worker::readyRead);
}

void Worker::post(QString location, QByteArray data) {
    qInfo() << "Posting to the server ...";

    QNetworkRequest request = QNetworkRequest(QUrl(location));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "test/plain"); // mime type

    QNetworkReply* replay = manager.post(request, data);
    connect(replay, &QNetworkReply::readyRead, this, &::Worker::readyRead);
}

void Worker::readyRead() {
    qInfo() << "readyRead";
    QNetworkReply* replay = qobject_cast<QNetworkReply*>(sender());
    if (replay)
        qInfo() << replay->readAll();
}

void Worker::authenticationRequired(QNetworkReply* reply, QAuthenticator* authenticator) {
    Q_UNUSED(reply);
    Q_UNUSED(authenticator);
    qInfo() << "authenticationRequired";
}

void Worker::encrypted(QNetworkReply* reply) {
    Q_UNUSED(reply);
    qInfo() << "encrypted";
}

void Worker::finished(QNetworkReply* reply) {
    Q_UNUSED(reply);
    qInfo() << "finished";
}

void Worker::preSharedKeyAuthenticationRequired(QNetworkReply* reply, QSslPreSharedKeyAuthenticator* authenticator) {
    Q_UNUSED(reply);
    Q_UNUSED(authenticator);
    qInfo() << "preSharedKeyAuthenticationRequired";
}

void Worker::proxyAuthenticationRequired(const QNetworkProxy& proxy, QAuthenticator* authenticator) {
    Q_UNUSED(proxy);
    Q_UNUSED(authenticator);
    qInfo() << "proxyAuthenticationRequired";
}

void Worker::sslErrors(QNetworkReply* reply, const QList<QSslError>& errors) {
    Q_UNUSED(reply);
    Q_UNUSED(errors);
    qInfo() << "sslErrors";
}
