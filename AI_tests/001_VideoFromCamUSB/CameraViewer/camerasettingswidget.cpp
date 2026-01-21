#include "camerasettingswidget.h"
#include <QScrollArea>

// === SliderControl ===

SliderControl::SliderControl(const QString &name, int min, int max, int defaultVal,
                             const QString &suffix, QWidget *parent)
    : QWidget(parent)
    , m_default(defaultVal)
    , m_suffix(suffix)
{
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 2, 0, 2);
    layout->setSpacing(8);

    QLabel *nameLabel = new QLabel(name, this);
    nameLabel->setFixedWidth(90);
    nameLabel->setStyleSheet("font-size: 11px;");

    m_slider = new QSlider(Qt::Horizontal, this);
    m_slider->setRange(min, max);
    m_slider->setValue(defaultVal);
    m_slider->setFixedHeight(18);

    m_valueLabel = new QLabel(QString::number(defaultVal) + suffix, this);
    m_valueLabel->setFixedWidth(45);
    m_valueLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    m_valueLabel->setStyleSheet("font-size: 10px; color: #aaa;");

    QPushButton *resetBtn = new QPushButton("↺", this);
    resetBtn->setFixedSize(20, 20);
    resetBtn->setToolTip("Reset");
    resetBtn->setStyleSheet("font-size: 12px; padding: 0;");

    layout->addWidget(nameLabel);
    layout->addWidget(m_slider, 1);
    layout->addWidget(m_valueLabel);
    layout->addWidget(resetBtn);

    connect(m_slider, &QSlider::valueChanged, this, [this](int val) {
        m_valueLabel->setText(QString::number(val) + m_suffix);
        emit valueChanged(val);
    });

    connect(resetBtn, &QPushButton::clicked, this, &SliderControl::reset);
}

// === CameraSettingsWidget ===

CameraSettingsWidget::CameraSettingsWidget(QWidget *parent)
    : QWidget(parent)
{
    setupUI();
    connectSliders();
}

void CameraSettingsWidget::setupUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(5, 5, 5, 5);
    mainLayout->setSpacing(5);

    m_tabWidget = new QTabWidget(this);
    m_tabWidget->setStyleSheet(
        "QTabWidget::pane { border: 1px solid #555; }"
        "QTabBar::tab { padding: 6px 12px; }"
        "QTabBar::tab:selected { background: #4a4a4a; }"
        );

    // Zakładka: Podstawowe
    QWidget *basicTab = new QWidget();
    QVBoxLayout *basicLayout = new QVBoxLayout(basicTab);
    basicLayout->addWidget(createBasicGroup());
    basicLayout->addStretch();
    m_tabWidget->addTab(basicTab, "🔆 Tonacja");

    // Zakładka: Kolor
    QWidget *colorTab = new QWidget();
    QVBoxLayout *colorLayout = new QVBoxLayout(colorTab);
    colorLayout->addWidget(createColorGroup());
    colorLayout->addStretch();
    m_tabWidget->addTab(colorTab, "🎨 Kolor");

    // Zakładka: Szczegóły
    QWidget *detailTab = new QWidget();
    QVBoxLayout *detailLayout = new QVBoxLayout(detailTab);
    detailLayout->addWidget(createDetailGroup());
    detailLayout->addStretch();
    m_tabWidget->addTab(detailTab, "🔍 Szczegóły");

    // Zakładka: Efekty
    QWidget *effectsTab = new QWidget();
    QVBoxLayout *effectsLayout = new QVBoxLayout(effectsTab);
    effectsLayout->addWidget(createEffectsGroup());
    effectsLayout->addStretch();
    m_tabWidget->addTab(effectsTab, "✨ Efekty");

    // Zakładka: Transformacja
    QWidget *transformTab = new QWidget();
    QVBoxLayout *transformLayout = new QVBoxLayout(transformTab);
    transformLayout->addWidget(createTransformGroup());
    transformLayout->addStretch();
    m_tabWidget->addTab(transformTab, "🔄 Transformacja");

    // Zakładka: Histogram
    m_tabWidget->addTab(createHistogramTab(), "📊 Histogram");

    mainLayout->addWidget(m_tabWidget, 1);

    // Przyciski na dole
    mainLayout->addWidget(createPresetsGroup());

    setMinimumWidth(320);
    setMaximumWidth(400);
}

QGroupBox* CameraSettingsWidget::createBasicGroup()
{
    QGroupBox *group = new QGroupBox("Regulacja tonalna");
    QVBoxLayout *layout = new QVBoxLayout(group);
    layout->setSpacing(4);

    m_exposure = new SliderControl("Ekspozycja", -100, 100, 0, "", this);
    m_brightness = new SliderControl("Jasność", -100, 100, 0, "", this);
    m_contrast = new SliderControl("Kontrast", -100, 100, 0, "", this);
    m_gamma = new SliderControl("Gamma", 10, 300, 100, "", this);
    m_highlights = new SliderControl("Światła", -100, 100, 0, "", this);
    m_shadows = new SliderControl("Cienie", -100, 100, 0, "", this);
    m_whites = new SliderControl("Biele", -100, 100, 0, "", this);
    m_blacks = new SliderControl("Czarne", -100, 100, 0, "", this);

    layout->addWidget(m_exposure);
    layout->addWidget(m_brightness);
    layout->addWidget(m_contrast);
    layout->addWidget(m_gamma);
    layout->addWidget(m_highlights);
    layout->addWidget(m_shadows);
    layout->addWidget(m_whites);
    layout->addWidget(m_blacks);

    return group;
}

QGroupBox* CameraSettingsWidget::createColorGroup()
{
    QGroupBox *group = new QGroupBox("Regulacja koloru");
    QVBoxLayout *layout = new QVBoxLayout(group);
    layout->setSpacing(4);

    m_saturation = new SliderControl("Nasycenie", -100, 100, 0, "", this);
    m_vibrance = new SliderControl("Żywość", -100, 100, 0, "", this);
    m_hue = new SliderControl("Odcień", -180, 180, 0, "°", this);
    m_temperature = new SliderControl("Temperatura", -100, 100, 0, "", this);
    m_tint = new SliderControl("Tinta", -100, 100, 0, "", this);

    layout->addWidget(m_saturation);
    layout->addWidget(m_vibrance);
    layout->addWidget(m_hue);

    layout->addSpacing(10);
    QLabel *wbLabel = new QLabel("Balans bieli:");
    wbLabel->setStyleSheet("font-weight: bold; color: #aaa;");
    layout->addWidget(wbLabel);

    layout->addWidget(m_temperature);
    layout->addWidget(m_tint);

    return group;
}

QGroupBox* CameraSettingsWidget::createDetailGroup()
{
    QGroupBox *group = new QGroupBox("Szczegóły i ostrość");
    QVBoxLayout *layout = new QVBoxLayout(group);
    layout->setSpacing(4);

    m_sharpness = new SliderControl("Ostrość", 0, 100, 0, "", this);
    m_clarity = new SliderControl("Klarowność", 0, 100, 0, "", this);
    m_noiseReduction = new SliderControl("Redukcja szumu", 0, 100, 0, "", this);
    m_blur = new SliderControl("Rozmycie", 0, 20, 0, "px", this);

    layout->addWidget(m_sharpness);
    layout->addWidget(m_clarity);
    layout->addWidget(m_noiseReduction);
    layout->addWidget(m_blur);

    // Info
    QLabel *infoLabel = new QLabel(
        "💡 Ostrość i rozmycie są wzajemnie wykluczające.\n"
        "Redukcja szumu może spowalniać obraz."
        );
    infoLabel->setStyleSheet("color: #888; font-size: 10px; padding: 10px;");
    infoLabel->setWordWrap(true);
    layout->addWidget(infoLabel);

    return group;
}

QGroupBox* CameraSettingsWidget::createEffectsGroup()
{
    QGroupBox *group = new QGroupBox("Efekty specjalne");
    QVBoxLayout *layout = new QVBoxLayout(group);
    layout->setSpacing(4);

    // Checkboxy
    QHBoxLayout *checksLayout = new QHBoxLayout();
    m_grayscale = new QCheckBox("Skala szarości", this);
    m_negative = new QCheckBox("Negatyw", this);
    m_sepia = new QCheckBox("Sepia", this);

    checksLayout->addWidget(m_grayscale);
    checksLayout->addWidget(m_negative);
    checksLayout->addWidget(m_sepia);
    layout->addLayout(checksLayout);

    layout->addSpacing(10);

    m_vignette = new SliderControl("Winieta", 0, 100, 0, "%", this);
    m_grain = new SliderControl("Ziarno", 0, 100, 0, "%", this);

    layout->addWidget(m_vignette);
    layout->addWidget(m_grain);

    return group;
}

QGroupBox* CameraSettingsWidget::createTransformGroup()
{
    QGroupBox *group = new QGroupBox("Transformacje");
    QVBoxLayout *layout = new QVBoxLayout(group);
    layout->setSpacing(8);

    // Odbicia
    QHBoxLayout *mirrorLayout = new QHBoxLayout();
    m_mirrorH = new QCheckBox("Odbij poziomo", this);
    m_mirrorV = new QCheckBox("Odbij pionowo", this);
    mirrorLayout->addWidget(m_mirrorH);
    mirrorLayout->addWidget(m_mirrorV);
    layout->addLayout(mirrorLayout);

    // Rotacja
    QHBoxLayout *rotLayout = new QHBoxLayout();
    rotLayout->addWidget(new QLabel("Rotacja:", this));
    m_rotation = new QComboBox(this);
    m_rotation->addItem("0°", 0);
    m_rotation->addItem("90°", 90);
    m_rotation->addItem("180°", 180);
    m_rotation->addItem("270°", 270);
    rotLayout->addWidget(m_rotation);
    rotLayout->addStretch();
    layout->addLayout(rotLayout);

    layout->addSpacing(10);
    QLabel *zoomLabel = new QLabel("Cyfrowy zoom i przesunięcie:");
    zoomLabel->setStyleSheet("font-weight: bold; color: #aaa;");
    layout->addWidget(zoomLabel);

    m_digitalZoom = new SliderControl("Zoom", 100, 400, 100, "%", this);
    m_panX = new SliderControl("Przesunięcie X", -100, 100, 0, "", this);
    m_panY = new SliderControl("Przesunięcie Y", -100, 100, 0, "", this);

    layout->addWidget(m_digitalZoom);
    layout->addWidget(m_panX);
    layout->addWidget(m_panY);

    return group;
}

QWidget* CameraSettingsWidget::createHistogramTab()
{
    QWidget *widget = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(widget);

    m_histogram = new HistogramWidget(this);
    layout->addWidget(m_histogram);

    QHBoxLayout *optLayout = new QHBoxLayout();
    m_showRGB = new QCheckBox("Pokaż RGB", this);
    m_showRGB->setChecked(true);
    m_showLuminance = new QCheckBox("Pokaż luminancję", this);
    m_showLuminance->setChecked(true);

    optLayout->addWidget(m_showRGB);
    optLayout->addWidget(m_showLuminance);
    optLayout->addStretch();
    layout->addLayout(optLayout);

    connect(m_showRGB, &QCheckBox::toggled, m_histogram, &HistogramWidget::setShowRGB);
    connect(m_showLuminance, &QCheckBox::toggled, m_histogram, &HistogramWidget::setShowLuminance);

    // Info o histogramie
    QLabel *infoLabel = new QLabel(
        "Histogram pokazuje rozkład jasności pikseli.\n"
        "• Czerwony - kanał R\n"
        "• Zielony - kanał G\n"
        "• Niebieski - kanał B\n"
        "• Szary - luminancja (jasność)"
        );
    infoLabel->setStyleSheet("color: #888; font-size: 10px; padding: 10px;");
    layout->addWidget(infoLabel);

    layout->addStretch();

    return widget;
}

QGroupBox* CameraSettingsWidget::createPresetsGroup()
{
    QGroupBox *group = new QGroupBox("Presety i akcje");
    QVBoxLayout *layout = new QVBoxLayout(group);

    // Presety
    QHBoxLayout *presetLayout = new QHBoxLayout();

    QPushButton *presetNormal = new QPushButton("Normalny", this);
    QPushButton *presetVivid = new QPushButton("Żywy", this);
    QPushButton *presetBW = new QPushButton("B&W", this);
    QPushButton *presetVintage = new QPushButton("Vintage", this);
    QPushButton *presetCold = new QPushButton("Zimny", this);
    QPushButton *presetWarm = new QPushButton("Ciepły", this);

    presetLayout->addWidget(presetNormal);
    presetLayout->addWidget(presetVivid);
    presetLayout->addWidget(presetBW);
    presetLayout->addWidget(presetVintage);
    presetLayout->addWidget(presetCold);
    presetLayout->addWidget(presetWarm);

    layout->addLayout(presetLayout);

    // Reset
    QHBoxLayout *resetLayout = new QHBoxLayout();
    QPushButton *resetBtn = new QPushButton("🔄 Reset wszystkiego", this);
    resetBtn->setStyleSheet(
        "QPushButton { background-color: #c0392b; padding: 8px; font-weight: bold; }"
        "QPushButton:hover { background-color: #e74c3c; }"
        );
    resetLayout->addStretch();
    resetLayout->addWidget(resetBtn);
    resetLayout->addStretch();
    layout->addLayout(resetLayout);

    // Połączenia presetów
    connect(presetNormal, &QPushButton::clicked, this, &CameraSettingsWidget::resetAll);

    connect(presetVivid, &QPushButton::clicked, this, [this]() {
        resetAll();
        m_saturation->setValue(40);
        m_contrast->setValue(20);
        m_vibrance->setValue(30);
    });

    connect(presetBW, &QPushButton::clicked, this, [this]() {
        resetAll();
        m_grayscale->setChecked(true);
        m_contrast->setValue(15);
    });

    connect(presetVintage, &QPushButton::clicked, this, [this]() {
        resetAll();
        m_sepia->setChecked(true);
        m_vignette->setValue(40);
        m_contrast->setValue(-10);
        m_grain->setValue(20);
    });

    connect(presetCold, &QPushButton::clicked, this, [this]() {
        resetAll();
        m_temperature->setValue(-50);
        m_saturation->setValue(10);
    });

    connect(presetWarm, &QPushButton::clicked, this, [this]() {
        resetAll();
        m_temperature->setValue(50);
        m_saturation->setValue(15);
    });

    connect(resetBtn, &QPushButton::clicked, this, &CameraSettingsWidget::resetAll);

    return group;
}

void CameraSettingsWidget::connectSliders()
{
    auto connectSlider = [this](SliderControl *ctrl) {
        connect(ctrl, &SliderControl::valueChanged, this, &CameraSettingsWidget::emitSettingsChanged);
    };

    connectSlider(m_brightness);
    connectSlider(m_contrast);
    connectSlider(m_exposure);
    connectSlider(m_gamma);
    connectSlider(m_shadows);
    connectSlider(m_highlights);
    connectSlider(m_blacks);
    connectSlider(m_whites);
    connectSlider(m_saturation);
    connectSlider(m_vibrance);
    connectSlider(m_hue);
    connectSlider(m_temperature);
    connectSlider(m_tint);
    connectSlider(m_sharpness);
    connectSlider(m_clarity);
    connectSlider(m_noiseReduction);
    connectSlider(m_blur);
    connectSlider(m_vignette);
    connectSlider(m_grain);
    connectSlider(m_digitalZoom);
    connectSlider(m_panX);
    connectSlider(m_panY);

    connect(m_grayscale, &QCheckBox::toggled, this, &CameraSettingsWidget::emitSettingsChanged);
    connect(m_negative, &QCheckBox::toggled, this, &CameraSettingsWidget::emitSettingsChanged);
    connect(m_sepia, &QCheckBox::toggled, this, &CameraSettingsWidget::emitSettingsChanged);
    connect(m_mirrorH, &QCheckBox::toggled, this, &CameraSettingsWidget::emitSettingsChanged);
    connect(m_mirrorV, &QCheckBox::toggled, this, &CameraSettingsWidget::emitSettingsChanged);
    connect(m_rotation, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &CameraSettingsWidget::emitSettingsChanged);
}

void CameraSettingsWidget::emitSettingsChanged()
{
    emit settingsChanged();
}

ImageEffects CameraSettingsWidget::getEffects() const
{
    ImageEffects effects;

    effects.brightness = m_brightness->value();
    effects.contrast = m_contrast->value();
    effects.exposure = m_exposure->value();
    effects.gamma = m_gamma->value();
    effects.shadows = m_shadows->value();
    effects.highlights = m_highlights->value();
    effects.blacks = m_blacks->value();
    effects.whites = m_whites->value();

    effects.saturation = m_saturation->value();
    effects.vibrance = m_vibrance->value();
    effects.hue = m_hue->value();
    effects.temperature = m_temperature->value();
    effects.tint = m_tint->value();

    effects.sharpness = m_sharpness->value();
    effects.clarity = m_clarity->value();
    effects.noiseReduction = m_noiseReduction->value();
    effects.blur = m_blur->value();

    effects.grayscale = m_grayscale->isChecked();
    effects.negative = m_negative->isChecked();
    effects.sepia = m_sepia->isChecked();
    effects.vignette = m_vignette->value();
    effects.grain = m_grain->value();

    effects.mirrorH = m_mirrorH->isChecked();
    effects.mirrorV = m_mirrorV->isChecked();
    effects.rotation = m_rotation->currentData().toInt();
    effects.digitalZoom = m_digitalZoom->value();
    effects.panX = m_panX->value();
    effects.panY = m_panY->value();

    return effects;
}

void CameraSettingsWidget::setEffects(const ImageEffects &effects)
{
    m_brightness->setValue(effects.brightness);
    m_contrast->setValue(effects.contrast);
    m_exposure->setValue(effects.exposure);
    m_gamma->setValue(effects.gamma);
    m_shadows->setValue(effects.shadows);
    m_highlights->setValue(effects.highlights);
    m_blacks->setValue(effects.blacks);
    m_whites->setValue(effects.whites);

    m_saturation->setValue(effects.saturation);
    m_vibrance->setValue(effects.vibrance);
    m_hue->setValue(effects.hue);
    m_temperature->setValue(effects.temperature);
    m_tint->setValue(effects.tint);

    m_sharpness->setValue(effects.sharpness);
    m_clarity->setValue(effects.clarity);
    m_noiseReduction->setValue(effects.noiseReduction);
    m_blur->setValue(effects.blur);

    m_grayscale->setChecked(effects.grayscale);
    m_negative->setChecked(effects.negative);
    m_sepia->setChecked(effects.sepia);
    m_vignette->setValue(effects.vignette);
    m_grain->setValue(effects.grain);

    m_mirrorH->setChecked(effects.mirrorH);
    m_mirrorV->setChecked(effects.mirrorV);
    m_digitalZoom->setValue(effects.digitalZoom);
    m_panX->setValue(effects.panX);
    m_panY->setValue(effects.panY);

    int rotIndex = m_rotation->findData(effects.rotation);
    if (rotIndex >= 0) m_rotation->setCurrentIndex(rotIndex);
}

void CameraSettingsWidget::resetAll()
{
    ImageEffects defaults;
    setEffects(defaults);
    emit settingsChanged();
}

void CameraSettingsWidget::updateHistogram(const QImage &image)
{
    m_histogram->updateHistogram(image);
}
