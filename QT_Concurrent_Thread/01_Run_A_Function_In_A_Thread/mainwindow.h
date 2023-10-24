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

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool t_running = false;

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;

    bool t_start = false;
    QFuture<void> ConcurentThread;
};
#endif // MAINWINDOW_H
