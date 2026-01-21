#include "videowindow.h"
#include <QKeyEvent>
#include <QResizeEvent>
#include <QFileDialog>
#include <QStandardPaths>
#include <QDateTime>
#include <QScreen>
#include <QGuiApplication>
#include <QMessageBox>
#include <QDebug>
#include <QElapsedTimer>

VideoWindow::VideoWindow(const QCameraDevice &cameraDevice, QWidget *parent)
    : QWidget(parent)
    , m_cameraDevice(cameraDevice)
    , m_camera(nullptr)
    , m_captureSession(nullptr)
    , m_videoSink(nullptr)
    , m_isFullScreen(false)
    , m_frameCount(0)
    , m_lastFpsTime(0)
{
    // Ważne: ustaw atrybuty okna
    setAttribute(Qt::WA_DeleteOnClose, false);
    setWindowFlags(Qt::Window);

    setupUI();

    qDebug() << "Inicjalizacja kamery:" << m_cameraDevice.description();
    qDebug() << "ID kamery:" << m_cameraDevice.id();

    // Inicjalizacja kamery
    m_camera = new QCamera(m_cameraDevice, this);
    m_captureSession = new QMediaCaptureSession(this);
    m_videoSink = new QVideoSink(this);

    // Konfiguracja sesji
    m_captureSession->setCamera(m_camera);
    m_captureSession->setVideoSink(m_videoSink);

    // Połączenia sygnałów kamery
    connect(m_camera, &QCamera::activeChanged,
            this, &VideoWindow::onCameraActiveChanged);
    connect(m_camera, &QCamera::errorOccurred,
            this, &VideoWindow::onCameraErrorOccurred);

    // Odbieranie klatek wideo - KLUCZOWE!
    connect(m_videoSink, &QVideoSink::videoFrameChanged,
            this, &VideoWindow::onFrameReceived);

    populateResolutions();

    qDebug() << "VideoWindow utworzone pomyślnie";
}

VideoWindow::~VideoWindow()
{
    qDebug() << "VideoWindow destruktor";
    stopCamera();
}

void VideoWindow::setupUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    // Label do wyświetlania wideo (zamiast QVideoWidget)
    m_videoLabel = new QLabel(this);
    m_videoLabel->setMinimumSize(640, 480);
    m_videoLabel->setStyleSheet("background-color: #1a1a1a;");
    m_videoLabel->setAlignment(Qt::AlignCenter);
    m_videoLabel->setText("Oczekiwanie na obraz...");
    m_videoLabel->setScaledContents(false);  // Będziemy skalować ręcznie
    m_videoLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    mainLayout->addWidget(m_videoLabel, 1);

    // Panel kontrolny
    m_controlPanel = new QWidget(this);
    m_controlPanel->setFixedHeight(50);
    m_controlPanel->setStyleSheet(
        "QWidget { background-color: #2d2d2d; }"
        "QLabel { color: white; }"
        "QPushButton { background-color: #4a4a4a; color: white; "
        "border: none; padding: 8px 15px; border-radius: 4px; min-width: 80px; }"
        "QPushButton:hover { background-color: #5a5a5a; }"
        "QComboBox { background-color: #4a4a4a; color: white; "
        "border: none; padding: 5px 10px; border-radius: 4px; min-width: 120px; }"
        "QComboBox::drop-down { border: none; }"
        "QComboBox QAbstractItemView { background-color: #3a3a3a; color: white; }"
        );

    QHBoxLayout *controlLayout = new QHBoxLayout(m_controlPanel);
    controlLayout->setContentsMargins(10, 5, 10, 5);

    // Status
    m_statusLabel = new QLabel("Inicjalizacja...", this);
    m_statusLabel->setMinimumWidth(120);
    controlLayout->addWidget(m_statusLabel);

    // FPS
    m_fpsLabel = new QLabel("FPS: --", this);
    m_fpsLabel->setMinimumWidth(80);
    controlLayout->addWidget(m_fpsLabel);

    controlLayout->addStretch();

    // Wybór rozdzielczości
    QLabel *resLabel = new QLabel("Rozdzielczość:", this);
    controlLayout->addWidget(resLabel);

    m_resolutionCombo = new QComboBox(this);
    m_resolutionCombo->setMinimumWidth(150);
    controlLayout->addWidget(m_resolutionCombo);

    controlLayout->addSpacing(20);

    // Przyciski
    m_snapshotButton = new QPushButton("Zrzut ekranu", this);
    controlLayout->addWidget(m_snapshotButton);

    m_fullScreenButton = new QPushButton("Pełny ekran", this);
    controlLayout->addWidget(m_fullScreenButton);

    mainLayout->addWidget(m_controlPanel);

    // Połączenia
    connect(m_fullScreenButton, &QPushButton::clicked,
            this, &VideoWindow::toggleFullScreen);
    connect(m_snapshotButton, &QPushButton::clicked,
            this, &VideoWindow::takeSnapshot);
    connect(m_resolutionCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &VideoWindow::onResolutionChanged);

    // Ustawienia okna
    setWindowTitle(QString("Wideo - %1").arg(m_cameraDevice.description()));
    resize(800, 650);

    // Centruj okno
    QScreen *screen = QGuiApplication::primaryScreen();
    if (screen) {
        QRect screenGeometry = screen->availableGeometry();
        int x = (screenGeometry.width() - width()) / 2 + screenGeometry.x();
        int y = (screenGeometry.height() - height()) / 2 + screenGeometry.y();
        move(x, y);
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

    // Zbierz unikalne rozdzielczości
    QMap<QString, QCameraFormat> uniqueFormats;
    for (const QCameraFormat &format : formats) {
        QSize res = format.resolution();
        QString key = QString("%1x%2").arg(res.width()).arg(res.height());

        if (!uniqueFormats.contains(key) ||
            format.maxFrameRate() > uniqueFormats[key].maxFrameRate()) {
            uniqueFormats[key] = format;
        }
    }

    // Posortuj od najwyższej rozdzielczości
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
        qDebug() << "Dodano rozdzielczość:" << displayText;
    }

    // Wybierz 720p lub pierwszą dostępną
    int defaultIndex = 0;
    for (int i = 0; i < m_resolutionCombo->count(); ++i) {
        if (m_resolutionCombo->itemText(i).contains("1280x720")) {
            defaultIndex = i;
            break;
        }
    }
    m_resolutionCombo->setCurrentIndex(defaultIndex);
}

bool VideoWindow::startCamera()
{
    if (!m_camera) {
        qDebug() << "Błąd: kamera nie jest zainicjalizowana";
        return false;
    }

    qDebug() << "Uruchamianie kamery...";

    // Ustaw wybraną rozdzielczość
    if (m_resolutionCombo->count() > 0 && m_resolutionCombo->currentData().isValid()) {
        QCameraFormat format = m_resolutionCombo->currentData().value<QCameraFormat>();
        qDebug() << "Ustawianie formatu:" << format.resolution();
        m_camera->setCameraFormat(format);
    }

    m_camera->start();

    m_lastFpsTime = QDateTime::currentMSecsSinceEpoch();
    m_frameCount = 0;

    qDebug() << "Kamera uruchomiona, oczekiwanie na klatki...";
    return true;
}

void VideoWindow::stopCamera()
{
    qDebug() << "Zatrzymywanie kamery...";
    if (m_camera && m_camera->isActive()) {
        m_camera->stop();
    }
}

void VideoWindow::onFrameReceived(const QVideoFrame &frame)
{
    if (!frame.isValid()) {
        return;
    }

    // Konwersja klatki do QImage
    QVideoFrame cloneFrame(frame);
    cloneFrame.map(QVideoFrame::ReadOnly);

    QImage image = cloneFrame.toImage();
    cloneFrame.unmap();

    if (image.isNull()) {
        qDebug() << "Nie udało się przekonwertować klatki do QImage";
        return;
    }

    // Zapisz ostatnią klatkę do zrzutu ekranu
    m_lastFrame = image.copy();

    // Aktualizuj wyświetlanie
    updateFrame(image);

    // Oblicz FPS
    m_frameCount++;
    qint64 currentTime = QDateTime::currentMSecsSinceEpoch();
    qint64 elapsed = currentTime - m_lastFpsTime;

    if (elapsed >= 1000) {
        double fps = m_frameCount * 1000.0 / elapsed;
        m_fpsLabel->setText(QString("FPS: %1").arg(fps, 0, 'f', 1));
        m_frameCount = 0;
        m_lastFpsTime = currentTime;
    }
}

void VideoWindow::updateFrame(const QImage &image)
{
    if (image.isNull() || m_videoLabel == nullptr) {
        return;
    }

    // Skaluj obraz do rozmiaru labela zachowując proporcje
    QSize labelSize = m_videoLabel->size();
    QPixmap pixmap = QPixmap::fromImage(image);
    QPixmap scaled = pixmap.scaled(labelSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    m_videoLabel->setPixmap(scaled);
}

void VideoWindow::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);

    // Przerysuj ostatnią klatkę po zmianie rozmiaru
    if (!m_lastFrame.isNull()) {
        updateFrame(m_lastFrame);
    }
}

void VideoWindow::onCameraActiveChanged(bool active)
{
    qDebug() << "Stan kamery zmieniony:" << (active ? "aktywna" : "nieaktywna");

    if (active) {
        m_statusLabel->setText("● Aktywna");
        m_statusLabel->setStyleSheet("color: #4CAF50; font-weight: bold;");
    } else {
        m_statusLabel->setText("○ Nieaktywna");
        m_statusLabel->setStyleSheet("color: #f44336;");
        m_videoLabel->setText("Kamera zatrzymana");
    }
}

void VideoWindow::onCameraErrorOccurred(QCamera::Error error, const QString &errorString)
{
    qDebug() << "Błąd kamery:" << error << "-" << errorString;

    m_statusLabel->setText("Błąd!");
    m_statusLabel->setStyleSheet("color: #f44336; font-weight: bold;");
    m_videoLabel->setText(QString("Błąd: %1").arg(errorString));

    emit cameraError(error, errorString);
}

void VideoWindow::toggleFullScreen()
{
    m_isFullScreen = !m_isFullScreen;

    if (m_isFullScreen) {
        m_controlPanel->hide();
        showFullScreen();
        m_fullScreenButton->setText("Wyjdź");
    } else {
        m_controlPanel->show();
        showNormal();
        m_fullScreenButton->setText("Pełny ekran");
    }
}

void VideoWindow::onResolutionChanged(int index)
{
    if (index < 0 || !m_camera) return;

    QVariant data = m_resolutionCombo->itemData(index);
    if (!data.isValid()) return;

    QCameraFormat format = data.value<QCameraFormat>();
    qDebug() << "Zmiana rozdzielczości na:" << format.resolution();

    bool wasActive = m_camera->isActive();
    if (wasActive) {
        m_camera->stop();
    }

    m_camera->setCameraFormat(format);

    if (wasActive) {
        m_camera->start();
    }
}

void VideoWindow::takeSnapshot()
{
    if (m_lastFrame.isNull()) {
        QMessageBox::warning(this, "Błąd", "Brak obrazu do zapisania");
        return;
    }

    QString defaultPath = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);
    QString timestamp = QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss");
    QString defaultFileName = QString("%1/snapshot_%2.png").arg(defaultPath, timestamp);

    QString fileName = QFileDialog::getSaveFileName(
        this, "Zapisz zrzut ekranu", defaultFileName,
        "Obrazy PNG (*.png);;Obrazy JPEG (*.jpg);;Wszystkie pliki (*.*)"
        );

    if (!fileName.isEmpty()) {
        if (m_lastFrame.save(fileName)) {
            m_statusLabel->setText("Zapisano!");
            QMessageBox::information(this, "Sukces",
                                     QString("Zrzut zapisano do:\n%1").arg(fileName));
        } else {
            QMessageBox::warning(this, "Błąd", "Nie udało się zapisać pliku");
        }
    }
}

void VideoWindow::closeEvent(QCloseEvent *event)
{
    qDebug() << "Zamykanie okna wideo";
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
    default:
        QWidget::keyPressEvent(event);
    }
}
