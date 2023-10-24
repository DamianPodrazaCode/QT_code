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
    bool t_running = false;
    bool t_running2 = false;

signals:
    void updateQlabel1_signal(QString str);
    void updateQlabel2_signal(QString str);

private slots:
    void updateQlabel1_slot(QString str);
    void updateQlabel2_slot(QString str);
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    bool t_start = false;
    QFuture<void> ConcurentThread;
    bool t_start2 = false;
    QFuture<void> ConcurentThread2;
};
#endif // MAINWINDOW_H
