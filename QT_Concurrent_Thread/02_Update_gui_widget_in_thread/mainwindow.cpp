#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    connect(this, SIGNAL(updateQlabel1_signal(QString)),this,SLOT(updateQlabel1_slot(QString)));
    connect(this, SIGNAL(updateQlabel2_signal(QString)),this,SLOT(updateQlabel2_slot(QString)));
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::updateQlabel1_slot(QString str) {
    ui->label->setText(str);
}

void ConcurentThreadFun(MainWindow *mainW) {
    qInfo() << "ConcurentThreadFun - START";
    int counter = 0;
    while(mainW->t_running) {
        counter++;
       // qInfo() << "ConcurentThreadFun - RUNNING" << counter;
        emit mainW->updateQlabel1_signal(QString::number(counter));
        QThread::msleep(5);
    }
    qInfo() << "ConcurentThreadFun - END";
}

void MainWindow::on_pushButton_clicked() {
    if (!t_start) {
        t_start = true;
        ui->pushButton->setText("Stop tread 1");
        t_running = true;
        ConcurentThread = QtConcurrent::run(ConcurentThreadFun, this);
        ConcurentThread.resume();
    } else {
        t_start = false;
        ui->pushButton->setText("Start thread 1");
        t_running = false;
        ConcurentThread.suspend();
        ConcurentThread.cancel();
    }
}

void MainWindow::updateQlabel2_slot(QString str) {
    ui->label_2->setText(str);
}

void ConcurentThreadFun2(MainWindow *mainW) {
    qInfo() << "ConcurentThreadFun2 - START";
    int counter = 0;
    while(mainW->t_running2) {
        counter++;
       // qInfo() << "ConcurentThreadFun2 - RUNNING" << counter;
        emit mainW->updateQlabel2_signal(QString::number(counter));
        QThread::msleep(3);
    }
    qInfo() << "ConcurentThreadFun2 - END";
}

void MainWindow::on_pushButton_2_clicked() {
    if (!t_start2) {
        t_start2 = true;
        ui->pushButton_2->setText("Stop tread 2");
        t_running2 = true;
        ConcurentThread2 = QtConcurrent::run(ConcurentThreadFun2, this);
        ConcurentThread2.resume();
    } else {
        t_start2 = false;
        ui->pushButton_2->setText("Start thread 2");
        t_running2 = false;
        ConcurentThread2.suspend();
        ConcurentThread2.cancel();
    }
}

