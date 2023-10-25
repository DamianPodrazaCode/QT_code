#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    connect(this, SIGNAL(update_l_th1_signal(QString)), this, SLOT(update_l_th1(QString)));
    connect(this, SIGNAL(update_l_th2_signal(QString)), this, SLOT(update_l_th2(QString)));
    connect(this, SIGNAL(update_l_th3_signal(QString)), this, SLOT(update_l_th3(QString)));
    connect(this, SIGNAL(update_l_th4_signal(QString)), this, SLOT(update_l_th4(QString)));
    connect(this, SIGNAL(update_l_th5_signal(QString)), this, SLOT(update_l_th5(QString)));
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_pb_th1_toggled(bool checked) {
    if(checked) {
        ui->pb_th1->setText("thread1 ON");
    } else {
        ui->pb_th1->setText("thread1 OFF");
    }
}
void MainWindow::on_pb_th2_toggled(bool checked) {
    if(checked) {
        ui->pb_th2->setText("thread2 ON");
    } else {
        ui->pb_th2->setText("thread2 OFF");
    }
}
void MainWindow::on_pb_th3_toggled(bool checked) {
    if(checked) {
        ui->pb_th3->setText("thread3 ON");
    } else {
        ui->pb_th3->setText("thread3 OFF");
    }
}
void MainWindow::on_pb_th4_toggled(bool checked) {
    if(checked) {
        ui->pb_th4->setText("thread4 ON");
    } else {
        ui->pb_th4->setText("thread4 OFF");
    }
}
void MainWindow::on_pb_th5_toggled(bool checked) {
    if(checked) {
        ui->pb_th5->setText("thread5 ON");
    } else {
        ui->pb_th5->setText("thread5 OFF");
    }
}
void MainWindow::on_pb_th_all_toggled(bool checked) {
    if(checked) {
        ui->pb_th_all->setText("thread all ON");
    } else {
        ui->pb_th_all->setText("thread all OFF");
    }
}

void MainWindow::update_l_th1(QString str) {
    ui->l_th1->setText(str);
}
void MainWindow::update_l_th2(QString str) {
    ui->l_th2->setText(str);
}
void MainWindow::update_l_th3(QString str) {
    ui->l_th3->setText(str);
}
void MainWindow::update_l_th4(QString str) {
    ui->l_th4->setText(str);
}
void MainWindow::update_l_th5(QString str) {
    ui->l_th5->setText(str);
}

