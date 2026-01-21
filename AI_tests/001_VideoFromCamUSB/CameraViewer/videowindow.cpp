#include "videowindow.h"
#include <QKeyEvent>
#include <QResizeEvent>
#include <QFileDialog>
#include <QStandardPaths>
#include <QDateTime>
#include <QScreen>
#include <QGuiApplication>
#include <QMessageBox>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QDebug>
#include <QThread>

VideoWindow::VideoWindow(const QCameraDevice &cameraDevice, QWidget *parent)
    : QMainWindow(parent)
    , m_cameraDevice(cameraDevice)
    , m_camera(nullptr)
    , m_captureSession(nullptr)
    , m_recorder(nullptr)
    , m_videoSink(nullptr)
    , m_isFullScreen(false)
    , m_isRecording(false)
    , m_frameCount(0)
    , m_lastFpsTime(0)
{
    setAttribute(Qt::WA_DeleteOnClose, false);

    m_imageProcessor = new ImageProcessor(this);

    setupUI();
    setupMenuBar();

    qDebug() << "Inicjalizacja kamery:" << m_cameraDevice.description();

    // Inicjalizacja kamery
    m_camera = new QCamera(m_cameraDevice, this);
    m_captureSession = new QMediaCaptureSession(this);
    m_videoSink = new QVideoSink(this);
    m_recorder = new QMediaRecorder(this);

    // Konfiguracja sesji
    m_captureSession->setCamera(m_camera);
    m_captureSession->setVideoSink(m_videoSink);
    m_captureSession->setRecorder(m_recorder);

    // Połączenia sygnałów kamery
    connect(m_camera, &QCamera::activeChanged,
            this, &VideoWindow::onCameraActiveChanged);
    connect(m_camera, &QCamera::errorOccurred,
            this, &VideoWindow::onCameraErrorOccurred);
    connect(m_videoSink, &QVideoSink::videoFrameChanged,
            this, &VideoWindow::onFrameReceived);

    // Timer do aktualizacji czasu nagrywania
    m_recordingUpdateTimer = new QTimer(this);
    connect(m_recordingUpdateTimer, &QTimer::timeout,
            this, &VideoWindow::updateRecordingTime);

    // Timer do aktualizacji histogramu (rzadziej niż klatki)
    m_histogramTimer = new QTimer(this);
    m_histogramTimer->setInterval(200); // 5 razy na sekundę
    connect(m_histogramTimer, &QTimer::timeout, this, [this]() {
        if (!m_processedFrame.isNull()) {
            m_settingsWidget->updateHistogram(m_processedFrame);
        }
    });
    m_histogramTimer->start();

    populateResolutions();
    populateCameraControls();

    qDebug() << "VideoWindow utworzone pomyślnie";
}

VideoWindow::~VideoWindow()
{
    qDebug() << "VideoWindow destruktor";
    stopCamera();
}

void VideoWindow::setupMenuBar()
{
    QMenuBar *menuBar = this->menuBar();

    // Menu Plik
    QMenu *fileMenu = menuBar->addMenu("&Plik");

    QAction *snapshotAction = fileMenu->addAction("📷 Zrzut ekranu");
    snapshotAction->setShortcut(QKeySequence("Ctrl+S"));
    connect(snapshotAction, &QAction::triggered, this, &VideoWindow::takeSnapshot);

    QAction *recordAction = fileMenu->addAction("⏺ Nagrywaj");
    recordAction->setShortcut(QKeySequence("Ctrl+R"));
    connect(recordAction, &QAction::triggered, this, &VideoWindow::toggleRecording);

    fileMenu->addSeparator();

    QAction *closeAction = fileMenu->addAction("Zamknij");
    closeAction->setShortcut(QKeySequence::Close);
    connect(closeAction, &QAction::triggered, this, &VideoWindow::close);

    // Menu Widok
    QMenu *viewMenu = menuBar->addMenu("&Widok");

    QAction *fullScreenAction = viewMenu->addAction("Pełny ekran");
    fullScreenAction->setShortcut(QKeySequence("F11"));
    connect(fullScreenAction, &QAction::triggered, this, &VideoWindow::toggleFullScreen);

    QAction *settingsAction = viewMenu->addAction("Panel ustawień");
    settingsAction->setShortcut(QKeySequence("Ctrl+P"));
    settingsAction->setCheckable(true);
    settingsAction->setChecked(true);
    connect(settingsAction, &QAction::triggered, this, &VideoWindow::toggleSettingsPanel);

    // Menu Pomoc
    QMenu *helpMenu = menuBar->addMenu("&Pomoc");

    QAction *shortcutsAction = helpMenu->addAction("Skróty klawiszowe");
    connect(shortcutsAction, &QAction::triggered, this, [this]() {
        QMessageBox::information(this, "Skróty klawiszowe",
                                 "F11 / F - Pełny ekran\n"
                                 "Escape - Wyjście z pełnego ekranu\n"
                                 "Ctrl+S / Spacja - Zrzut ekranu\n"
                                 "Ctrl+R - Nagrywanie\n"
                                 "Ctrl+P - Panel ustawień\n"
                                 "Q - Zamknij"
                                 );
    });
}

void VideoWindow::setupUI()
{
    m_centralWidget = new QWidget(this);
    setCentralWidget(m_centralWidget);

    QHBoxLayout *mainLayout = new QHBoxLayout(m_centralWidget);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    // Lewy panel - wideo
    QWidget *videoContainer = new QWidget();
    QVBoxLayout *videoLayout = new QVBoxLayout(videoContainer);
    videoLayout->setContentsMargins(0, 0, 0, 0);
    videoLayout->setSpacing(0);

    // Video label
    m_videoLabel = new QLabel();
    m_videoLabel->setMinimumSize(640, 480);
    m_videoLabel->setStyleSheet("background-color: #1a1a1a;");
    m_videoLabel->setAlignment(Qt::AlignCenter);
    m_videoLabel->setText("Oczekiwanie na obraz...");
    m_videoLabel->setScaledContents(false);
    m_videoLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    videoLayout->addWidget(m_videoLabel, 1);

    // Panel kontrolny
    m_controlPanel = new QWidget();
    m_controlPanel->setFixedHeight(80);
    m_controlPanel->setStyleSheet(
        "QWidget { background-color: #252525; }"
        "QLabel { color: white; }"
        "QPushButton { background-color: #3a3a3a; color: white; "
        "border: none; padding: 8px 12px; border-radius: 4px; }"
        "QPushButton:hover { background-color: #4a4a4a; }"
        "QPushButton:checked { background-color: #c0392b; }"
        "QComboBox { background-color: #3a3a3a; color: white; "
        "border: none; padding: 5px 10px; border-radius: 4px; min-width: 100px; }"
        );

    QVBoxLayout *controlMainLayout = new QVBoxLayout(m_controlPanel);
    controlMainLayout->setContentsMargins(10, 5, 10, 5);
    controlMainLayout->setSpacing(5);

    // Górna linia - status
    QHBoxLayout *statusLayout = new QHBoxLayout();

    m_statusLabel = new QLabel("Inicjalizacja...");
    m_statusLabel->setMinimumWidth(100);
    statusLayout->addWidget(m_statusLabel);

    m_fpsLabel = new QLabel("FPS: --");
    m_fpsLabel->setMinimumWidth(70);
    statusLayout->addWidget(m_fpsLabel);

    m_resolutionLabel = new QLabel("--");
    m_resolutionLabel->setMinimumWidth(100);
    statusLayout->addWidget(m_resolutionLabel);

    m_recordingLabel = new QLabel("");
    m_recordingLabel->setStyleSheet("color: #e74c3c; font-weight: bold;");
    statusLayout->addWidget(m_recordingLabel);

    statusLayout->addStretch();
    controlMainLayout->addLayout(statusLayout);

    // Dolna linia - kontrolki
    QHBoxLayout *controlLayout = new QHBoxLayout();

    // Rozdzielczość
    controlLayout->addWidget(new QLabel("Rozdzielczość:"));
    m_resolutionCombo = new QComboBox();
    controlLayout->addWidget(m_resolutionCombo);

    // Focus mode
    controlLayout->addWidget(new QLabel("Focus:"));
    m_focusModeCombo = new QComboBox();
    controlLayout->addWidget(m_focusModeCombo);

    // Exposure mode
    controlLayout->addWidget(new QLabel("Ekspozycja:"));
    m_exposureModeCombo = new QComboBox();
    controlLayout->addWidget(m_exposureModeCombo);

    // White balance
    controlLayout->addWidget(new QLabel("Biel:"));
    m_whiteBalanceCombo = new QComboBox();
    controlLayout->addWidget(m_whiteBalanceCombo);

    controlLayout->addStretch();

    // Przyciski
    m_snapshotButton = new QPushButton("📷 Zdjęcie");
    controlLayout->addWidget(m_snapshotButton);

    m_recordButton = new QPushButton("⏺ Nagrywaj");
    m_recordButton->setCheckable(true);
    controlLayout->addWidget(m_recordButton);

    m_settingsButton = new QPushButton("⚙ Ustawienia");
    m_settingsButton->setCheckable(true);
    m_settingsButton->setChecked(true);
    controlLayout->addWidget(m_settingsButton);

    m_fullScreenButton = new QPushButton("⛶ Pełny ekran");
    controlLayout->addWidget(m_fullScreenButton);

    controlMainLayout->addLayout(controlLayout);

    videoLayout->addWidget(m_controlPanel);
    mainLayout->addWidget(videoContainer, 1);

    // Prawy panel - ustawienia (jako dock)
    m_settingsDock = new QDockWidget("Ustawienia obrazu", this);
    m_settingsDock->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);
    m_settingsDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

    m_settingsWidget = new CameraSettingsWidget();
    m_settingsDock->setWidget(m_settingsWidget);

    addDockWidget(Qt::RightDockWidgetArea, m_settingsDock);

    // Połączenia
    connect(m_fullScreenButton, &QPushButton::clicked, this, &VideoWindow::toggleFullScreen);
    connect(m_snapshotButton, &QPushButton::clicked, this, &VideoWindow::takeSnapshot);
    connect(m_recordButton, &QPushButton::clicked, this, &VideoWindow::toggleRecording);
    connect(m_settingsButton, &QPushButton::toggled, this, &VideoWindow::toggleSettingsPanel);
    connect(m_resolutionCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &VideoWindow::onResolutionChanged);
    connect(m_focusModeCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &VideoWindow::onFocusModeChanged);
    connect(m_exposureModeCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &VideoWindow::onExposureModeChanged);
    connect(m_whiteBalanceCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &VideoWindow::onWhiteBalanceChanged);
    connect(m_settingsWidget, &CameraSettingsWidget::settingsChanged,
            this, &VideoWindow::onSettingsChanged);

    // Ustawienia okna
    setWindowTitle(QString("Kamera - %1").arg(m_cameraDevice.description()));
    resize(1280, 800);

    // Centruj okno
    QScreen *screen = QGuiApplication::primaryScreen();
    if (screen) {
        QRect screenGeometry = screen->availableGeometry();
        int x = (screenGeometry.width() - width()) / 2 + screenGeometry.x();
        int y = (screenGeometry.height() - height()) / 2 + screenGeometry.y();
        move(x, y);
    }
}

void VideoWindow::populateCameraControls()
{
    // Focus modes
    m_focusModeCombo->clear();
    m_focusModeCombo->addItem("Auto", QVariant::fromValue(QCamera::FocusModeAuto));
    // m_focusModeCombo->addItem("Ciągły", QVariant::fromValue(QCamera::FocusModeContinuous));
    // m_focusModeCombo->addItem("Ciągły", QVariant::fromValue(QCamera::FocusModeContinuous));
    m_focusModeCombo->addItem("Nieskończoność", QVariant::fromValue(QCamera::FocusModeInfinity));
    m_focusModeCombo->addItem("Ręczny", QVariant::fromValue(QCamera::FocusModeManual));

    // Exposure modes
    m_exposureModeCombo->clear();
    m_exposureModeCombo->addItem("Auto", QVariant::fromValue(QCamera::ExposureAuto));
    m_exposureModeCombo->addItem("Ręczna", QVariant::fromValue(QCamera::ExposureManual));
    m_exposureModeCombo->addItem("Portret", QVariant::fromValue(QCamera::ExposurePortrait));
    m_exposureModeCombo->addItem("Sport", QVariant::fromValue(QCamera::ExposureSports));
    m_exposureModeCombo->addItem("Noc", QVariant::fromValue(QCamera::ExposureNight));

    // White balance
    m_whiteBalanceCombo->clear();
    m_whiteBalanceCombo->addItem("Auto", QVariant::fromValue(QCamera::WhiteBalanceAuto));
    m_whiteBalanceCombo->addItem("Słoneczny", QVariant::fromValue(QCamera::WhiteBalanceSunlight));
    m_whiteBalanceCombo->addItem("Pochmurny", QVariant::fromValue(QCamera::WhiteBalanceCloudy));
    m_whiteBalanceCombo->addItem("Cień", QVariant::fromValue(QCamera::WhiteBalanceShade));
    m_whiteBalanceCombo->addItem("Tungsten", QVariant::fromValue(QCamera::WhiteBalanceTungsten));
    m_whiteBalanceCombo->addItem("Fluorescent", QVariant::fromValue(QCamera::WhiteBalanceFluorescent));
    m_whiteBalanceCombo->addItem("Flash", QVariant::fromValue(QCamera::WhiteBalanceFlash));
}

void VideoWindow::onFocusModeChanged(int index)
{
    if (!m_camera || index < 0) return;

    QCamera::FocusMode mode = m_focusModeCombo->itemData(index).value<QCamera::FocusMode>();
    if (m_camera->isFocusModeSupported(mode)) {
        m_camera->setFocusMode(mode);
    }
}

void VideoWindow::onExposureModeChanged(int index)
{
    if (!m_camera || index < 0) return;

    QCamera::ExposureMode mode = m_exposureModeCombo->itemData(index).value<QCamera::ExposureMode>();
    if (m_camera->isExposureModeSupported(mode)) {
        m_camera->setExposureMode(mode);
    }
}

void VideoWindow::onWhiteBalanceChanged(int index)
{
    if (!m_camera || index < 0) return;

    QCamera::WhiteBalanceMode mode = m_whiteBalanceCombo->itemData(index).value<QCamera::WhiteBalanceMode>();
    if (m_camera->isWhiteBalanceModeSupported(mode)) {
        m_camera->setWhiteBalanceMode(mode);
    }
}

void VideoWindow::populateResolutions()
{
    m_resolutionCombo->clear();

    QList<QCameraFormat> formats = m_cameraDevice.videoFormats();
    qDebug() << "Dostępnych formatów:" << formats.size();

    if (formats.isEmpty()) {
        m_resolutionCombo->addItem("Domyślna");
        return;
    }

    QMap<QString, QCameraFormat> uniqueFormats;
    for (const QCameraFormat &format : formats) {
        QSize res = format.resolution();
        QString key = QString("%1x%2").arg(res.width()).arg(res.height());

        if (!uniqueFormats.contains(key) ||
            format.maxFrameRate() > uniqueFormats[key].maxFrameRate()) {
            uniqueFormats[key] = format;
        }
    }

    QList<QString> keys = uniqueFormats.keys();
    std::sort(keys.begin(), keys.end(), [](const QString &a, const QString &b) {
        int widthA = a.split('x')[0].toInt();
        int widthB = b.split('x')[0].toInt();
        return widthA > widthB;
    });

    for (const QString &key : keys) {
        const QCameraFormat &format = uniqueFormats[key];
        QString displayText = QString("%1 @ %2 fps")
                                  .arg(key)
                                  .arg(qRound(format.maxFrameRate()));
        m_resolutionCombo->addItem(displayText, QVariant::fromValue(format));
    }

    // Domyślnie 720p
    for (int i = 0; i < m_resolutionCombo->count(); ++i) {
        if (m_resolutionCombo->itemText(i).contains("1280x720")) {
            m_resolutionCombo->setCurrentIndex(i);
            break;
        }
    }
}

bool VideoWindow::startCamera()
{
    if (!m_camera) {
        qDebug() << "Błąd: kamera nie jest zainicjalizowana";
        return false;
    }

    qDebug() << "Uruchamianie kamery...";

    if (m_resolutionCombo->count() > 0 && m_resolutionCombo->currentData().isValid()) {
        QCameraFormat format = m_resolutionCombo->currentData().value<QCameraFormat>();
        qDebug() << "Ustawianie formatu:" << format.resolution();
        m_camera->setCameraFormat(format);
    }

    m_camera->start();

    m_lastFpsTime = QDateTime::currentMSecsSinceEpoch();
    m_frameCount = 0;

    return true;
}

void VideoWindow::stopCamera()
{
    if (m_isRecording) {
        toggleRecording();
    }

    if (m_camera && m_camera->isActive()) {
        m_camera->stop();
    }
}

void VideoWindow::onFrameReceived(const QVideoFrame &frame)
{
    if (!frame.isValid()) return;

    QVideoFrame cloneFrame(frame);
    cloneFrame.map(QVideoFrame::ReadOnly);

    QImage image = cloneFrame.toImage();
    cloneFrame.unmap();

    if (image.isNull()) return;

    m_lastFrame = image.copy();

    // Przetwarzanie obrazu
    m_imageProcessor->setEffects(m_settingsWidget->getEffects());
    m_processedFrame = m_imageProcessor->process(m_lastFrame);

    updateFrame(m_processedFrame);
    updateStats();
}

void VideoWindow::onSettingsChanged()
{
    // Efekty są stosowane przy każdej klatce
}

void VideoWindow::updateFrame(const QImage &image)
{
    if (image.isNull() || !m_videoLabel) return;

    QSize labelSize = m_videoLabel->size();
    QPixmap pixmap = QPixmap::fromImage(image);
    QPixmap scaled = pixmap.scaled(labelSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    m_videoLabel->setPixmap(scaled);
}

void VideoWindow::updateStats()
{
    m_frameCount++;
    qint64 currentTime = QDateTime::currentMSecsSinceEpoch();
    qint64 elapsed = currentTime - m_lastFpsTime;

    if (elapsed >= 1000) {
        double fps = m_frameCount * 1000.0 / elapsed;
        m_fpsLabel->setText(QString("FPS: %1").arg(fps, 0, 'f', 1));
        m_frameCount = 0;
        m_lastFpsTime = currentTime;
    }

    // Aktualizuj info o rozdzielczości
    if (!m_lastFrame.isNull()) {
        m_resolutionLabel->setText(QString("%1×%2")
                                       .arg(m_lastFrame.width())
                                       .arg(m_lastFrame.height()));
    }
}

void VideoWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);

    if (!m_processedFrame.isNull()) {
        updateFrame(m_processedFrame);
    }
}

void VideoWindow::onCameraActiveChanged(bool active)
{
    if (active) {
        m_statusLabel->setText("● Aktywna");
        m_statusLabel->setStyleSheet("color: #2ecc71; font-weight: bold;");
    } else {
        m_statusLabel->setText("○ Nieaktywna");
        m_statusLabel->setStyleSheet("color: #e74c3c;");
        m_videoLabel->setText("Kamera zatrzymana");
    }
}

void VideoWindow::onCameraErrorOccurred(QCamera::Error error, const QString &errorString)
{
    qDebug() << "Błąd kamery:" << error << "-" << errorString;

    m_statusLabel->setText("Błąd!");
    m_statusLabel->setStyleSheet("color: #e74c3c; font-weight: bold;");

    emit cameraError(error, errorString);
}

void VideoWindow::toggleFullScreen()
{
    m_isFullScreen = !m_isFullScreen;

    if (m_isFullScreen) {
        m_controlPanel->hide();
        m_settingsDock->hide();
        menuBar()->hide();
        showFullScreen();
    } else {
        m_controlPanel->show();
        if (m_settingsButton->isChecked()) {
            m_settingsDock->show();
        }
        menuBar()->show();
        showNormal();
    }
}

void VideoWindow::toggleSettingsPanel()
{
    m_settingsDock->setVisible(m_settingsButton->isChecked());
}

void VideoWindow::onResolutionChanged(int index)
{
    if (index < 0 || !m_camera) return;

    QVariant data = m_resolutionCombo->itemData(index);
    if (!data.isValid()) return;

    QCameraFormat format = data.value<QCameraFormat>();

    bool wasActive = m_camera->isActive();
    if (wasActive) m_camera->stop();

    m_camera->setCameraFormat(format);

    if (wasActive) m_camera->start();
}

void VideoWindow::takeSnapshot()
{
    if (m_processedFrame.isNull()) {
        QMessageBox::warning(this, "Błąd", "Brak obrazu do zapisania");
        return;
    }

    QString defaultPath = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);
    QString timestamp = QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss");
    QString defaultFileName = QString("%1/snapshot_%2.png").arg(defaultPath, timestamp);

    QString fileName = QFileDialog::getSaveFileName(
        this, "Zapisz zrzut ekranu", defaultFileName,
        "PNG (*.png);;JPEG (*.jpg);;BMP (*.bmp);;Wszystkie (*.*)"
        );

    if (!fileName.isEmpty()) {
        if (m_processedFrame.save(fileName)) {
            m_statusLabel->setText("📷 Zapisano!");
        } else {
            QMessageBox::warning(this, "Błąd", "Nie udało się zapisać pliku");
        }
    }
}

void VideoWindow::toggleRecording()
{
    if (!m_recorder) return;

    if (m_isRecording) {
        m_recorder->stop();
        m_isRecording = false;
        m_recordButton->setChecked(false);
        m_recordButton->setText("⏺ Nagrywaj");
        m_recordingLabel->setText("");
        m_recordingUpdateTimer->stop();
    } else {
        QString defaultPath = QStandardPaths::writableLocation(QStandardPaths::MoviesLocation);
        QString timestamp = QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss");
        QString fileName = QString("%1/recording_%2.mp4").arg(defaultPath, timestamp);

        fileName = QFileDialog::getSaveFileName(
            this, "Zapisz nagranie", fileName,
            "MP4 (*.mp4);;AVI (*.avi);;Wszystkie (*.*)"
            );

        if (!fileName.isEmpty()) {
            m_recorder->setOutputLocation(QUrl::fromLocalFile(fileName));
            m_recorder->record();
            m_isRecording = true;
            m_recordButton->setChecked(true);
            m_recordButton->setText("⏹ Stop");
            m_recordingTimer.start();
            m_recordingUpdateTimer->start(1000);
        }
    }
}

void VideoWindow::updateRecordingTime()
{
    if (m_isRecording) {
        qint64 ms = m_recordingTimer.elapsed();
        int secs = ms / 1000;
        int mins = secs / 60;
        secs %= 60;
        m_recordingLabel->setText(QString("⏺ REC %1:%2")
                                      .arg(mins, 2, 10, QChar('0'))
                                      .arg(secs, 2, 10, QChar('0')));
    }
}

void VideoWindow::closeEvent(QCloseEvent *event)
{
    stopCamera();
    emit closed();
    event->accept();
}

void VideoWindow::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Escape:
        if (m_isFullScreen) {
            toggleFullScreen();
        } else {
            close();
        }
        break;
    case Qt::Key_F:
    case Qt::Key_F11:
        toggleFullScreen();
        break;
    case Qt::Key_S:
        if (event->modifiers() & Qt::ControlModifier) {
            takeSnapshot();
        }
        break;
    case Qt::Key_Space:
        takeSnapshot();
        break;
    case Qt::Key_R:
        if (event->modifiers() & Qt::ControlModifier) {
            toggleRecording();
        }
        break;
    case Qt::Key_Q:
        close();
        break;
    default:
        QMainWindow::keyPressEvent(event);
    }
}
