#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "task.h"

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

private slots:
    void on_pb_th1_toggled(bool checked);
    void update_l_th1(QString str);
    void on_pb_th2_toggled(bool checked);
    void update_l_th2(QString str);

private:
    Ui::MainWindow *ui;
    Task *task1;
    int count1 = 0;
    Task *task2;
    int count2 = 0;
};
#endif // MAINWINDOW_H
