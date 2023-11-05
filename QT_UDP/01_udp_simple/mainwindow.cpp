#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    udpSocket = new QUdpSocket(this);
    connect(udpSocket, SIGNAL(readyRead()), this, SLOT(readPendingDatagrams()));
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_pb_send_clicked() {
    QByteArray data = ui->le_send->text().toLatin1();
    QHostAddress ipAdress(ui->le_send_ip->text());
    uint16_t port = ui->le_send_port->text().toUInt();
    udpSocket->writeDatagram(data, ipAdress, port);
}

void MainWindow::readPendingDatagrams() {
    while (udpSocket->hasPendingDatagrams()) {
        QNetworkDatagram datagram = udpSocket->receiveDatagram();
        ui->lw_read->addItem(datagram.data());
    }
}

void MainWindow::on_pb_bind_toggled(bool checked) {
    if (checked) {
        ui->pb_bind->setText("unBind");
        udpSocket->close();
        uint16_t port = ui->le_read_port->text().toUInt();
        udpSocket->bind(port);
    } else {
        ui->pb_bind->setText("Bind");
        udpSocket->close();
    }
}
