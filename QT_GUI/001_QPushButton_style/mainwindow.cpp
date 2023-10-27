#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_pushButton_clicked() {
    qInfo() << "pushButtonClick";
}

void MainWindow::on_pushButton_2_toggled(bool checked) {
    if (checked) {
        qInfo() << "toogleButtonOn";
    } else {
        qInfo() << "toogleButtonOff";
    }
}
