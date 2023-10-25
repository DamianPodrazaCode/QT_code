#include "mainwindow.h"
#include "ui_mainwindow.h"

void threadFun(MainWindow *mainW) {
    while (mainW->thread_run) {
        mainW->thread_count++;
        emit mainW->update_label_thread_signal(QString::number(mainW->thread_count));
        QThread::msleep(50);
    }
}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    // płączenie wyzwalania w GUI, jeżeli tego niebędzie to po czasie przestanie działać GUI.
    connect(this, SIGNAL(update_label_thread_signal(QString)), this, SLOT(update_label_thread(QString)));
}

MainWindow::~MainWindow() {
    thread_run = false;                // wyjście z pętli w wątku
    ConcurentThread.waitForFinished(); // oczekiwanie na zakończenie wątku, jak tego nie będzie to wątek pozostanie
                                       // uruchomiony nawet po zamknięciu aplikacji
    delete ui;
}

void MainWindow::on_pb_thread_toggled(bool checked) {
    if (checked) {
        thread_run = true;
        // podpięcie i uruchomienie ,funkji wątku, pierwszy par. to nazwa funkcji, drugi i następne to refer. argumentów
        // funkcji funkcja jest urruchamiana raz, później wychodzi i umiera, więc o cyklicznoś w wewnątrz trzeba zadbać
        // samemu
        ConcurentThread = QtConcurrent::run(threadFun, this);
        ui->pb_thread->setText("thread ON");
    } else {
        thread_run = false;
        ConcurentThread.waitForFinished();
        ui->pb_thread->setText("thread OFF");
    }
}

void MainWindow::update_label_thread(QString str) { ui->l_thread->setText(str); }
