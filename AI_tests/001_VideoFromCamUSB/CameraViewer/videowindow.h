#ifndef VIDEOWINDOW_H
#define VIDEOWINDOW_H

#include <QWidget>
#include <QCamera>
#include <QMediaCaptureSession>
#include <QMediaRecorder>
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
#include <QTimer>
#include <QElapsedTimer>
#include <QDockWidget>
#include <QMainWindow>

#include "camerasettingswidget.h"
#include "imageprocessor.h"

class VideoWindow : public QMainWindow
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
    void onSettingsChanged();
    void toggleFullScreen();
    void onResolutionChanged(int index);
    void takeSnapshot();
    void toggleRecording();
    void updateRecordingTime();
    void toggleSettingsPanel();
    void onFocusModeChanged(int index);
    void onExposureModeChanged(int index);
    void onWhiteBalanceChanged(int index);

private:
    void setupUI();
    void setupMenuBar();
    void populateResolutions();
    void populateCameraControls();
    void updateFrame(const QImage &image);
    void updateStats();

    QCameraDevice m_cameraDevice;
    QCamera *m_camera;
    QMediaCaptureSession *m_captureSession;
    QMediaRecorder *m_recorder;
    QVideoSink *m_videoSink;

    // Central widget
    QWidget *m_centralWidget;
    QLabel *m_videoLabel;

    // Control panel
    QWidget *m_controlPanel;
    QLabel *m_statusLabel;
    QLabel *m_fpsLabel;
    QLabel *m_resolutionLabel;
    QLabel *m_recordingLabel;
    QPushButton *m_fullScreenButton;
    QPushButton *m_snapshotButton;
    QPushButton *m_recordButton;
    QPushButton *m_settingsButton;
    QComboBox *m_resolutionCombo;

    // Camera controls
    QComboBox *m_focusModeCombo;
    QComboBox *m_exposureModeCombo;
    QComboBox *m_whiteBalanceCombo;

    // Settings dock
    QDockWidget *m_settingsDock;
    CameraSettingsWidget *m_settingsWidget;

    // Image processing
    ImageProcessor *m_imageProcessor;

    // State
    bool m_isFullScreen;
    bool m_isRecording;
    QImage m_lastFrame;
    QImage m_processedFrame;

    // Stats
    int m_frameCount;
    qint64 m_lastFpsTime;
    QElapsedTimer m_recordingTimer;
    QTimer *m_recordingUpdateTimer;

    // Histogram update timer
    QTimer *m_histogramTimer;
};

#endif // VIDEOWINDOW_H
