#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDebug>
#include <QFuture>
#include <QMainWindow>
#include <QThread>
#include <QWidget>
#include <QtConcurrent>
#include <QtCore>
#include <QtGui>
#include <QThreadPool>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // stan wątku (włączony, wyłączony)
    bool th1_run = false;
    bool th2_run = false;
    bool th3_run = false;
    bool th4_run = false;
    bool th5_run = false;

    // liczniki dla każdego wątku
    int th1_count = 0;
    int th2_count = 0;
    int th3_count = 0;
    int th4_count = 0;
    int th5_count = 0;

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

    // ConcurentThread's - uproszczona wielowątkowość w celu wyeliminowania problemu miedzysystemowego.
    QFuture<void> thread1;
    QFuture<void> thread2;
    QFuture<void> thread3;
    QFuture<void> thread4;
    QFuture<void> thread5;

    QThreadPool *threadPool;
};
#endif // MAINWINDOW_H
