#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    COMPORT = new QSerialPort();
    COMPORT->setPortName("COM3");
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
}

MainWindow::~MainWindow() {
    qInfo() << "Serial stop";

    COMPORT->close();

    if (COMPORT->isOpen()) {
        qInfo() << "Serial connected";
    } else {
        qInfo() << "Serial not connected";
    }
    qInfo() << COMPORT->error();

    delete ui;
}


void MainWindow::on_pbSend_clicked() {
    if(COMPORT->isOpen()) {
        COMPORT->write(ui->leSend->text().toLatin1() + char(10));  //wysłanie komendy na port (komenda "On" włacza leda "Off" wyłącza)
    }
}

