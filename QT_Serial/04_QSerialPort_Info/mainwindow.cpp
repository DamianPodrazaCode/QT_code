#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    for (const QSerialPortInfo &portInfo : QSerialPortInfo::availablePorts()) {
        qInfo() << "portName : " << portInfo.portName();
        qInfo() << "description : " << portInfo.description();
        qInfo() << "manufacturer : " << portInfo.manufacturer();
        qInfo() << "serialNumber : " << portInfo.serialNumber();
        qInfo() << "productIdentifier : " << "(hex)" << QString::number(portInfo.productIdentifier(),16);
        qInfo() << "vendorIdentifier : " << "(hex)" << QString::number(portInfo.vendorIdentifier(),16);
        qInfo() << "systemLocation : " << portInfo.systemLocation();
    }

    COMPORT = new QSerialPort();
    COMPORT->setPortName("COM14");
    COMPORT->setBaudRate(QSerialPort::Baud115200);
    COMPORT->setParity(QSerialPort::NoParity);
    COMPORT->setDataBits(QSerialPort::Data8);
    COMPORT->setStopBits(QSerialPort::OneStop);
    COMPORT->setFlowControl(QSerialPort::NoFlowControl);

    qInfo() << "Serial start";

    COMPORT->open(QIODeviceBase::ReadWrite);

    if (COMPORT->isOpen()) {
        qInfo() << "Serial connected";
    } else {
        qInfo() << "Serial not connected";
    }
    qInfo() << COMPORT->error();

    qInfo() << "Serial stop";

    COMPORT->close();

    if (COMPORT->isOpen()) {
        qInfo() << "Serial connected";
    } else {
        qInfo() << "Serial not connected";
    }
    qInfo() << COMPORT->error();
}

MainWindow::~MainWindow() {
    delete ui;
}

