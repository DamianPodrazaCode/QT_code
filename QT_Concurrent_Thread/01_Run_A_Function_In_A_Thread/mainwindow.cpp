#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

void ConcurentThreadFun(MainWindow *mainW) {
    qInfo() << "ConcurentThreadFun - START";
    int counter = 0;
    while(mainW->t_running) {
        qInfo() << "ConcurentThreadFun - RUNNING" << counter++;
        QThread::msleep(500);
    }
    qInfo() << "ConcurentThreadFun - END";
}

void MainWindow::on_pushButton_clicked() {
    if (!t_start) {
        t_start = true;
        ui->pushButton->setText("Stop Thread");
        t_running = true;
        ConcurentThread = QtConcurrent::run(ConcurentThreadFun, this);
        ConcurentThread.resume();
    } else {
        t_start = false;
        ui->pushButton->setText("Start Thread");
        t_running = false;
        ConcurentThread.suspend();
        ConcurentThread.cancel();
    }
}

