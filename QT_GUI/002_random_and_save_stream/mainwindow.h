#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDebug>
#include <QFile>
#include <QMainWindow>
#include <QRandomGenerator>
#include <QTextStream>
#include <QTimer>
#include <QDialog>
#include <QFileDialog>

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

    void start();

private slots:
    void updateTimer();
    void on_pb_random_toggled(bool checked);

    void on_pb_save_toggled(bool checked);

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    bool fSaveStrem = false;
    QFile file;
    QTextStream strem;
};
#endif // MAINWINDOW_H
