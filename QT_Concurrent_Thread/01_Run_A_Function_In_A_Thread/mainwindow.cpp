#include "mainwindow.h"
#include "ui_mainwindow.h"

void threadFun(MainWindow *mainW) {
    qInfo() << "ConcurentThreadFun - START";
    while (mainW->thread_run) {
        mainW->thread_count++;
        qInfo() << "ConcurentThreadFun - RUNNING" << mainW->thread_count;
        QThread::msleep(100);
    }
    qInfo() << "ConcurentThreadFun - END";
}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    thread_run = false;
    ConcurentThread.waitForFinished();
    delete ui;
}

void MainWindow::on_pb_thread_toggled(bool checked) {
    if (checked) {
        thread_run = true;
        ConcurentThread = QtConcurrent::run(threadFun, this);
        ui->pb_thread->setText("thread3 ON");
    } else {
        thread_run = false;
        ConcurentThread.waitForFinished();
        ui->pb_thread->setText("thread3 OFF");
    }
}
