#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // ustawienia portu
    // w .pro dodać QT += serialport
    COMPORT = new QSerialPort();
    COMPORT->setPortName("COM1");
    COMPORT->setBaudRate(QSerialPort::Baud115200);
    COMPORT->setParity(QSerialPort::NoParity);
    COMPORT->setDataBits(QSerialPort::Data8);
    COMPORT->setStopBits(QSerialPort::OneStop);
    COMPORT->setFlowControl(QSerialPort::NoFlowControl);


    qInfo() << "Serial start";

    COMPORT->open(QIODeviceBase::ReadWrite);

    if (COMPORT->isOpen())
    {
        qInfo() << "Serial connected";
    }else{
        qInfo() << "Serial not connected";
    }
    qInfo() << COMPORT->error();


    qInfo() << "Serial stop";

    COMPORT->close();

    if (COMPORT->isOpen())
    {
        qInfo() << "Serial connected";
    }else{
        qInfo() << "Serial not connected";
    }
    qInfo() << COMPORT->error();

}

MainWindow::~MainWindow()
{
    delete ui;
}

