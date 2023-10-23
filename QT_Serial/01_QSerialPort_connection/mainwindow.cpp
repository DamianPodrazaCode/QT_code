#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // ustawienia portu
    // w .pro dodać QT += serialport
    // dodać #include <QSerialPort>
    // dodać do klasy QSerialPort* COMPORT;
    COMPORT = new QSerialPort();
    COMPORT->setPortName("COM3");
    COMPORT->setBaudRate(QSerialPort::Baud115200);
    COMPORT->setParity(QSerialPort::NoParity);
    COMPORT->setDataBits(QSerialPort::Data8);
    COMPORT->setStopBits(QSerialPort::OneStop);
    COMPORT->setFlowControl(QSerialPort::NoFlowControl);
    COMPORT->clearError();

    ui->plainTextEdit->appendPlainText("Serial start");
    // otwarcie portu szeregowego
    COMPORT->open(QIODeviceBase::ReadWrite);

    if (COMPORT->isOpen()) {
        ui->plainTextEdit->appendPlainText("Serial connected");
    }else{
        ui->plainTextEdit->appendPlainText("Serial not connected");
    }
    ui->plainTextEdit->appendPlainText(COMPORT->errorString());
    //qInfo() << COMPORT->error();


    ui->plainTextEdit->appendPlainText("Serial stop");
    // zamknięcie portu szeregowego
    COMPORT->close();

    if (COMPORT->isOpen()) {
        ui->plainTextEdit->appendPlainText("Serial connected");
    }else{
        ui->plainTextEdit->appendPlainText("Serial not connected");
    }
    ui->plainTextEdit->appendPlainText(COMPORT->errorString());


}

MainWindow::~MainWindow() {
    delete ui;
}

