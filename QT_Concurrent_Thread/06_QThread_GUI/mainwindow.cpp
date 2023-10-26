#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    qInfo() << QThread::currentThread();
    task1 = new Task();
    task1->count = &count1;
    connect(task1, SIGNAL(update_label(QString)), this, SLOT(update_l_th1(QString)));
    task2 = new Task();
    task2->count = &count2;
    connect(task2, SIGNAL(update_label(QString)), this, SLOT(update_l_th2(QString)));
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_pb_th1_toggled(bool checked) {
    if (checked) {
        task1->start();
        ui->pb_th1->setText("Thread1 On");
    } else {
        task1->terminate();
        ui->pb_th1->setText("Thread1 Off");
    }
}

void MainWindow::update_l_th1(QString str) {
    ui->l_th1->setText(str);
}

void MainWindow::on_pb_th2_toggled(bool checked) {
    if (checked) {
        task2->start();
        ui->pb_th2->setText("Thread2 On");
    } else {
        task2->terminate();
        ui->pb_th2->setText("Thread2 Off");
    }
}

void MainWindow::update_l_th2(QString str) {
      ui->l_th2->setText(str);
}
