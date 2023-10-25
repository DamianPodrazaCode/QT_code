#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDebug>
#include <QFuture>
#include <QMainWindow>
#include <QWidget>
#include <QtConcurrent>
#include <QtCore>
#include <QtGui>

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

    bool thread_run = false;
    int thread_count = 0;

signals:
    void update_label_thread_signal(QString str);

private slots:
    void update_label_thread(QString str);
    void on_pb_thread_toggled(bool checked);

private:
    Ui::MainWindow *ui;
    QFuture<void> ConcurentThread;
};
#endif // MAINWINDOW_H
