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
    bool thread_run = false;
    int thread_count = 0;

private slots:

    void on_pb_thread_toggled(bool checked);

private:
    Ui::MainWindow *ui;

    QFuture<void> ConcurentThread;
};
#endif // MAINWINDOW_H
