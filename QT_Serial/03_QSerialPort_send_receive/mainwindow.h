#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QMessageBox>
#include <QString>
#include <QSerialPort>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pbSend_clicked();
    void read_data();

private:
    Ui::MainWindow *ui;
    QSerialPort* COMPORT;
    QString dataFromSerial;
    bool dataReady = false;
};
#endif // MAINWINDOW_H
