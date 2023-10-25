#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFuture>
#include <QtConcurrent>
#include <QtCore>
#include <QtGui>
#include <QWidget>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // stan wątku (włączony, wyłączony)
    bool t1_run = false;
    bool t2_run = false;
    bool t3_run = false;
    bool t4_run = false;
    bool t5_run = false;

signals:
    void update_l_th1_signal(QString str);
    void update_l_th2_signal(QString str);
    void update_l_th3_signal(QString str);
    void update_l_th4_signal(QString str);
    void update_l_th5_signal(QString str);

private slots:
    void on_pb_th1_toggled(bool checked);
    void on_pb_th2_toggled(bool checked);
    void on_pb_th3_toggled(bool checked);
    void on_pb_th4_toggled(bool checked);
    void on_pb_th5_toggled(bool checked);
    void on_pb_th_all_toggled(bool checked);

    void update_l_th1(QString str);
    void update_l_th2(QString str);
    void update_l_th3(QString str);
    void update_l_th4(QString str);
    void update_l_th5(QString str);

private:
    Ui::MainWindow *ui;

    // liczniki dla każdego wątku
    int th1_count = 0;
    int th2_count = 0;
    int th3_count = 0;
    int th4_count = 0;
    int th5_count = 0;

    // ConcurentThread's - uproszczona wielowątkowość w celu wyeliminowania problemu miedzysystemowego.
    QFuture<void> thread1;
    QFuture<void> thread2;
    QFuture<void> thread3;
    QFuture<void> thread4;
    QFuture<void> thread5;

};
#endif // MAINWINDOW_H
