#ifndef VIDEOWINDOW_H
#define VIDEOWINDOW_H

#include <QWidget>
#include <QCamera>
#include <QMediaCaptureSession>
#include <QVideoSink>
#include <QCameraDevice>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QComboBox>
#include <QCloseEvent>
#include <QImage>
#include <QVideoFrame>

class VideoWindow : public QWidget
{
    Q_OBJECT

public:
    explicit VideoWindow(const QCameraDevice &cameraDevice, QWidget *parent = nullptr);
    ~VideoWindow();

    bool startCamera();
    void stopCamera();

signals:
    void closed();
    void cameraError(QCamera::Error error, const QString &errorString);

protected:
    void closeEvent(QCloseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void onCameraActiveChanged(bool active);
    void onCameraErrorOccurred(QCamera::Error error, const QString &errorString);
    void onFrameReceived(const QVideoFrame &frame);
    void toggleFullScreen();
    void onResolutionChanged(int index);
    void takeSnapshot();

private:
    void setupUI();
    void populateResolutions();
    void updateFrame(const QImage &image);

    QCameraDevice m_cameraDevice;
    QCamera *m_camera;
    QMediaCaptureSession *m_captureSession;
    QVideoSink *m_videoSink;

    // UI Controls
    QLabel *m_videoLabel;          // Wyświetla obraz z kamery
    QWidget *m_controlPanel;
    QLabel *m_statusLabel;
    QLabel *m_fpsLabel;
    QPushButton *m_fullScreenButton;
    QPushButton *m_snapshotButton;
    QComboBox *m_resolutionCombo;

    bool m_isFullScreen;
    QImage m_lastFrame;

    // FPS counter
    int m_frameCount;
    qint64 m_lastFpsTime;
};

#endif // VIDEOWINDOW_H
