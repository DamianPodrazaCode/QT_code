#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
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

    // readyRead() - sygał emitowany z portu com w momencie pojawienia się nowych danych
    // readyRead() - moja metoda do odbioru danych połączona z readyRead()
    connect(COMPORT,SIGNAL(readyRead()),this,SLOT(read_data()));
}

MainWindow::~MainWindow()
{
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

// wysyłanie komendy "On" "Off"
void MainWindow::on_pbSend_clicked() {
    if(COMPORT->isOpen()) {
        COMPORT->write(ui->leSend->text().toLatin1() + char(10));
        COMPORT->flush();
    }
}

// odczyt danych
void MainWindow::read_data() {
    if(COMPORT->isOpen()) {
        while(COMPORT->bytesAvailable()) {
            dataFromSerial += COMPORT->readAll();
        }
        if (dataFromSerial.at(dataFromSerial.length()-1) == char(10)){
            ui->pteDataFromSerial->appendPlainText(dataFromSerial);
            dataFromSerial = "";
        }
    }
}

