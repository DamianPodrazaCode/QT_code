#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkDatagram>
#include <QUdpSocket>

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
    void on_pb_send_clicked();
    void readPendingDatagrams();
    void on_pb_bind_toggled(bool checked);

private:
    Ui::MainWindow *ui;
    QUdpSocket *udpSocket;
};
#endif // MAINWINDOW_H
