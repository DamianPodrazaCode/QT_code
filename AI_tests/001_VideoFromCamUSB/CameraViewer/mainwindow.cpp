#include "mainwindow.h"
#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , camera(nullptr)
    , videoWindow(nullptr)
    , isCameraRunning(false)
{
    setupUI();
    refreshCameraList();
    updateButtonStates();
}

MainWindow::~MainWindow()
{
    stopCamera();
}

void MainWindow::setupUI()
{
    // Główny widget
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->setSpacing(15);
    mainLayout->setContentsMargins(20, 20, 20, 20);

    // === Sekcja wyboru kamery ===
    QGroupBox *selectionGroup = new QGroupBox("Wybór kamery", this);
    QVBoxLayout *selectionLayout = new QVBoxLayout(selectionGroup);

    // ComboBox z kamerami
    QHBoxLayout *comboLayout = new QHBoxLayout();
    QLabel *cameraLabel = new QLabel("Dostępne kamery:", this);
    cameraComboBox = new QComboBox(this);
    cameraComboBox->setMinimumWidth(300);
    cameraComboBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    refreshButton = new QPushButton("🔄 Odśwież", this);
    refreshButton->setFixedWidth(100);

    comboLayout->addWidget(cameraLabel);
    comboLayout->addWidget(cameraComboBox, 1);
    comboLayout->addWidget(refreshButton);

    selectionLayout->addLayout(comboLayout);

    // Informacje o kamerze
    cameraInfoLabel = new QLabel("Wybierz kamerę z listy", this);
    cameraInfoLabel->setStyleSheet("color: #666; font-style: italic; padding: 10px;");
    cameraInfoLabel->setWordWrap(true);
    selectionLayout->addWidget(cameraInfoLabel);

    mainLayout->addWidget(selectionGroup);

    // === Sekcja sterowania ===
    QGroupBox *controlGroup = new QGroupBox("Sterowanie", this);
    QHBoxLayout *controlLayout = new QHBoxLayout(controlGroup);

    startButton = new QPushButton("▶ Uruchom kamerę", this);
    startButton->setStyleSheet(
        "QPushButton { background-color: #4CAF50; color: white; padding: 10px 20px; "
        "border: none; border-radius: 5px; font-weight: bold; }"
        "QPushButton:hover { background-color: #45a049; }"
        "QPushButton:disabled { background-color: #cccccc; }"
        );

    stopButton = new QPushButton("⏹ Zatrzymaj kamerę", this);
    stopButton->setStyleSheet(
        "QPushButton { background-color: #f44336; color: white; padding: 10px 20px; "
        "border: none; border-radius: 5px; font-weight: bold; }"
        "QPushButton:hover { background-color: #da190b; }"
        "QPushButton:disabled { background-color: #cccccc; }"
        );

    controlLayout->addStretch();
    controlLayout->addWidget(startButton);
    controlLayout->addWidget(stopButton);
    controlLayout->addStretch();

    mainLayout->addWidget(controlGroup);

    // === Status ===
    QGroupBox *statusGroup = new QGroupBox("Status", this);
    QVBoxLayout *statusLayout = new QVBoxLayout(statusGroup);

    statusLabel = new QLabel("Gotowy", this);
    statusLabel->setAlignment(Qt::AlignCenter);
    statusLabel->setStyleSheet(
        "QLabel { padding: 15px; background-color: #e8f5e9; "
        "border-radius: 5px; font-size: 14px; }"
        );

    statusLayout->addWidget(statusLabel);
    mainLayout->addWidget(statusGroup);

    // Stretch na końcu
    mainLayout->addStretch();

    // Połączenia sygnałów
    connect(refreshButton, &QPushButton::clicked, this, &MainWindow::refreshCameraList);
    connect(startButton, &QPushButton::clicked, this, &MainWindow::startCamera);
    connect(stopButton, &QPushButton::clicked, this, &MainWindow::stopCamera);
    connect(cameraComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow::onCameraSelectionChanged);

    // Ustawienia okna
    setWindowTitle("Camera Viewer - Qt6");
    setMinimumSize(500, 350);
    resize(550, 400);
}

void MainWindow::refreshCameraList()
{
    cameraComboBox->clear();
    availableCameras = QMediaDevices::videoInputs();

    if (availableCameras.isEmpty()) {
        cameraComboBox->addItem("Brak dostępnych kamer");
        cameraInfoLabel->setText("Nie znaleziono żadnych kamer USB. "
                                 "Podłącz kamerę i kliknij 'Odśwież'.");
        statusLabel->setText("⚠️ Brak kamer");
        statusLabel->setStyleSheet(
            "QLabel { padding: 15px; background-color: #fff3e0; "
            "border-radius: 5px; font-size: 14px; }"
            );
    } else {
        for (const QCameraDevice &cameraDevice : availableCameras) {
            QString displayName = cameraDevice.description();
            if (displayName.isEmpty()) {
                displayName = cameraDevice.id();
            }
            cameraComboBox->addItem(displayName);
        }

        statusLabel->setText(QString("✓ Znaleziono %1 kamer(ę/y)").arg(availableCameras.size()));
        statusLabel->setStyleSheet(
            "QLabel { padding: 15px; background-color: #e8f5e9; "
            "border-radius: 5px; font-size: 14px; }"
            );

        onCameraSelectionChanged(0);
    }

    updateButtonStates();
}

void MainWindow::onCameraSelectionChanged(int index)
{
    if (index < 0 || index >= availableCameras.size()) {
        cameraInfoLabel->setText("Wybierz kamerę z listy");
        return;
    }

    const QCameraDevice &device = availableCameras.at(index);

    QString info;
    info += QString("<b>ID:</b> %1<br>").arg(QString(device.id()));
    info += QString("<b>Opis:</b> %1<br>").arg(device.description());
    info += QString("<b>Pozycja:</b> %1<br>").arg(
        device.position() == QCameraDevice::FrontFace ? "Przednia" :
            device.position() == QCameraDevice::BackFace ? "Tylna" : "Nieokreślona"
        );

    // Wyświetl dostępne rozdzielczości
    QList<QCameraFormat> formats = device.videoFormats();
    if (!formats.isEmpty()) {
        QSet<QString> resolutions;
        for (const QCameraFormat &format : formats) {
            QSize res = format.resolution();
            resolutions.insert(QString("%1x%2").arg(res.width()).arg(res.height()));
        }
        QStringList resList = resolutions.values();
        std::sort(resList.begin(), resList.end(), [](const QString &a, const QString &b) {
            return a.split('x')[0].toInt() > b.split('x')[0].toInt();
        });
        info += QString("<b>Rozdzielczości:</b> %1").arg(resList.mid(0, 5).join(", "));
        if (resList.size() > 5) info += "...";
    }

    cameraInfoLabel->setText(info);
}

void MainWindow::startCamera()
{
    int index = cameraComboBox->currentIndex();

    if (index < 0 || index >= availableCameras.size()) {
        QMessageBox::warning(this, "Błąd", "Nie wybrano kamery!");
        return;
    }

    // Zatrzymaj poprzednią kamerę jeśli działa
    stopCamera();

    const QCameraDevice &cameraDevice = availableCameras.at(index);

    // Utwórz nowe okno wideo
    videoWindow = new VideoWindow(cameraDevice, this);

    connect(videoWindow, &VideoWindow::closed, this, &MainWindow::onVideoWindowClosed);
    connect(videoWindow, &VideoWindow::cameraError, this, &MainWindow::onCameraError);

    videoWindow->show();

    if (videoWindow->startCamera()) {
        isCameraRunning = true;
        statusLabel->setText(QString("🎥 Kamera aktywna: %1").arg(cameraDevice.description()));
        statusLabel->setStyleSheet(
            "QLabel { padding: 15px; background-color: #e3f2fd; "
            "border-radius: 5px; font-size: 14px; }"
            );
    } else {
        statusLabel->setText("❌ Błąd uruchamiania kamery");
        statusLabel->setStyleSheet(
            "QLabel { padding: 15px; background-color: #ffebee; "
            "border-radius: 5px; font-size: 14px; }"
            );
    }

    updateButtonStates();
}

void MainWindow::stopCamera()
{
    if (videoWindow) {
        videoWindow->stopCamera();
        videoWindow->close();
        videoWindow->deleteLater();
        videoWindow = nullptr;
    }

    isCameraRunning = false;
    statusLabel->setText("⏹ Kamera zatrzymana");
    statusLabel->setStyleSheet(
        "QLabel { padding: 15px; background-color: #e8f5e9; "
        "border-radius: 5px; font-size: 14px; }"
        );

    updateButtonStates();
}

void MainWindow::onCameraError(QCamera::Error error, const QString &errorString)
{
    Q_UNUSED(error);

    statusLabel->setText(QString("❌ Błąd: %1").arg(errorString));
    statusLabel->setStyleSheet(
        "QLabel { padding: 15px; background-color: #ffebee; "
        "border-radius: 5px; font-size: 14px; }"
        );

    QMessageBox::critical(this, "Błąd kamery", errorString);
}

void MainWindow::onVideoWindowClosed()
{
    isCameraRunning = false;
    videoWindow = nullptr;

    statusLabel->setText("Okno wideo zamknięte");
    statusLabel->setStyleSheet(
        "QLabel { padding: 15px; background-color: #e8f5e9; "
        "border-radius: 5px; font-size: 14px; }"
        );

    updateButtonStates();
}

void MainWindow::updateButtonStates()
{
    bool hasCameras = !availableCameras.isEmpty();

    startButton->setEnabled(hasCameras && !isCameraRunning);
    stopButton->setEnabled(isCameraRunning);
    cameraComboBox->setEnabled(hasCameras && !isCameraRunning);
}
