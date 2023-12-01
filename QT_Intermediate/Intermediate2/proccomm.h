#ifndef PROCCOMM_H
#define PROCCOMM_H

#include <QDebug>
#include <QObject>
#include <QProcess>
#include <QSysInfo>

class ProcComm : public QObject {
    Q_OBJECT

public:
    explicit ProcComm(QObject *parent = nullptr);
    ~ProcComm();

signals:

public slots:
    void readyRead();
    void action(QByteArray data);

private:
    QProcess proc;
    QString app;
    QString endl;
};

#endif // PROCCOMM_H
