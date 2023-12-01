#include "watcher.h"

Watcher::Watcher(QObject* parent) : QObject{parent} {
    fsw.addPath(QDir::currentPath());
    fsw.addPath(QDir::currentPath() + "/test.txt");
    //qInfo() << QDir::currentPath() + QDir::separator() + "test.txt";

    connect(&fsw, SIGNAL(fileChanged(QString)), this, SLOT(fileChanger(QString)));
    connect(&fsw, SIGNAL(directoryChanged(QString)), this, SLOT(directoryChanger(QString)));
}

void Watcher::fileChanger(const QString& path) {
    qInfo() << "plik zminiony : " << path;
    if (fsw.files().length()) {
        qInfo() << "zmienione pliki -> ";
        foreach (QString file, fsw.files()) {
            qInfo() << file;
        }
    }
}

void Watcher::directoryChanger(const QString& path) {
    qInfo() << "katalog zminiony : " << path;
    if (fsw.directories().length()) {
        qInfo() << "zmienione katalogi -> ";
        foreach (QString dir, fsw.directories()) {
            qInfo() << dir;
        }
    }
}
