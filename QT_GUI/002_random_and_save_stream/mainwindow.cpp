#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    start();
}

MainWindow::~MainWindow() {
    if (file.isOpen())
        file.close();
    delete ui;
}

void MainWindow::start() {
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateTimer()));
}

void MainWindow::updateTimer() {
    QString temp = QString::number(QRandomGenerator::global()->bounded(0xfff));
    ui->pte_random->appendPlainText(temp);
}

void MainWindow::on_pb_random_toggled(bool checked) {
    if (checked) {
        timer->start(300);
        ui->pb_random->setText("Stop Random");
    } else {
        timer->stop();
        ui->pb_random->setText("Start Random");
    }
}

void MainWindow::on_pb_save_toggled(bool checked) {
    if (checked) {
        fSaveStrem = false;
        QString path = QFileDialog::getSaveFileName(this, "Save to file");
        file.setFileName(path);
        if (!file.open(QIODevice::ReadWrite)) {
            qInfo() << "file error";
        }
        fSaveStrem = true;
        ui->pb_save->setText("Stop Save");
    } else {
        fSaveStrem = false;
        file.close();
        ui->pb_save->setText("Start Save");
    }
}
