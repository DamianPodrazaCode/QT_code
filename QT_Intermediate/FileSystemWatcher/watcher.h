#ifndef WATCHER_H
#define WATCHER_H

#include <QDebug>
#include <QDir>
#include <QFileSystemWatcher>
#include <QObject>

class Watcher : public QObject {
    Q_OBJECT

public:
    explicit Watcher(QObject *parent = nullptr);

signals:

public slots:
    void fileChanger(const QString &path);
    void directoryChanger(const QString &path);

private:
    QFileSystemWatcher fsw;
};

#endif // WATCHER_H
