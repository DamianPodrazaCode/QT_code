#include "mainwindow.h"
#include "ui_mainwindow.h"

// wątki
void thread1Fun(MainWindow *mainW) {
    while(mainW->th1_run) {
        mainW->th1_count++;
        emit mainW->update_l_th1_signal(QString::number(mainW->th1_count));
        QThread::msleep(50);
    }
}
void thread2Fun(MainWindow *mainW) {
    while(mainW->th2_run) {
        mainW->th2_count++;
        emit mainW->update_l_th2_signal(QString::number(mainW->th2_count));
        QThread::msleep(60);
    }
}
void thread3Fun(MainWindow *mainW) {
    while(mainW->th3_run) {
        mainW->th3_count++;
        emit mainW->update_l_th3_signal(QString::number(mainW->th3_count));
        QThread::msleep(70);
    }
}
void thread4Fun(MainWindow *mainW) {
    while(mainW->th4_run) {
        mainW->th4_count++;
        emit mainW->update_l_th4_signal(QString::number(mainW->th4_count));
        QThread::msleep(110);
    }
}
void thread5Fun(MainWindow *mainW) {
    while(mainW->th5_run) {
        mainW->th5_count++;
        emit mainW->update_l_th5_signal(QString::number(mainW->th5_count));
        QThread::msleep(30);
    }
}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    connect(this, SIGNAL(update_l_th1_signal(QString)), this, SLOT(update_l_th1(QString)));
    connect(this, SIGNAL(update_l_th2_signal(QString)), this, SLOT(update_l_th2(QString)));
    connect(this, SIGNAL(update_l_th3_signal(QString)), this, SLOT(update_l_th3(QString)));
    connect(this, SIGNAL(update_l_th4_signal(QString)), this, SLOT(update_l_th4(QString)));
    connect(this, SIGNAL(update_l_th5_signal(QString)), this, SLOT(update_l_th5(QString)));
}

MainWindow::~MainWindow() {
    th1_run = false;
    th2_run = false;
    th3_run = false;
    th4_run = false;
    th5_run = false;
    thread1.waitForFinished();
    thread2.waitForFinished();
    thread3.waitForFinished();
    thread4.waitForFinished();
    thread5.waitForFinished();
    delete ui;
}

void MainWindow::on_pb_th1_toggled(bool checked) {
    if(checked) {
        th1_run = true;
        thread1 = QtConcurrent::run(thread1Fun, this);
        ui->pb_th1->setText("thread1 ON");
    } else {
        th1_run = false;
        ui->pb_th1->setText("thread1 OFF");
    }
}
void MainWindow::on_pb_th2_toggled(bool checked) {
    if(checked) {
        th2_run = true;
        thread2 = QtConcurrent::run(thread2Fun, this);
        ui->pb_th2->setText("thread2 ON");
    } else {
        th2_run = false;
        ui->pb_th2->setText("thread2 OFF");
    }
}
void MainWindow::on_pb_th3_toggled(bool checked) {
    if(checked) {
        th3_run = true;
        thread3 = QtConcurrent::run(thread3Fun, this);
        ui->pb_th3->setText("thread3 ON");
    } else {
        th3_run = false;
        ui->pb_th3->setText("thread3 OFF");
    }
}
void MainWindow::on_pb_th4_toggled(bool checked) {
    if(checked) {
        th4_run = true;
        thread4 = QtConcurrent::run(thread4Fun, this);
        ui->pb_th4->setText("thread4 ON");
    } else {
        th4_run = false;
        ui->pb_th4->setText("thread4 OFF");
    }
}
void MainWindow::on_pb_th5_toggled(bool checked) {
    if(checked) {
        th5_run = true;
        thread5 = QtConcurrent::run(thread5Fun, this);
        ui->pb_th5->setText("thread5 ON");
    } else {
        th5_run = false;
        ui->pb_th5->setText("thread5 OFF");
    }
}
void MainWindow::on_pb_th_all_toggled(bool checked) {
    if(checked) {
        ui->pb_th1->setChecked(true);
        ui->pb_th2->setChecked(true);
        ui->pb_th3->setChecked(true);
        ui->pb_th4->setChecked(true);
        ui->pb_th5->setChecked(true);
        ui->pb_th_all->setText("thread all ON");
    } else {
        ui->pb_th1->setChecked(false);
        ui->pb_th2->setChecked(false);
        ui->pb_th3->setChecked(false);
        ui->pb_th4->setChecked(false);
        ui->pb_th5->setChecked(false);
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

