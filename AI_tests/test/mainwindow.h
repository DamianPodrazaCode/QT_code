#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QComboBox>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QCamera>
#include <QMediaDevices>
#include <QCameraDevice>
#include <QList>

#include "videowindow.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void refreshCameraList();
    void startCamera();
    void stopCamera();
    void onCameraSelectionChanged(int index);
    void onCameraError(QCamera::Error error, const QString &errorString);
    void onVideoWindowClosed();

private:
    void setupUI();
    void updateButtonStates();

    // UI Elements
    QComboBox *cameraComboBox;
    QPushButton *refreshButton;
    QPushButton *startButton;
    QPushButton *stopButton;
    QLabel *statusLabel;
    QLabel *cameraInfoLabel;

    // Camera
    QList<QCameraDevice> availableCameras;
    QCamera *camera;
    VideoWindow *videoWindow;

    bool isCameraRunning;
};

#endif // MAINWINDOW_H
