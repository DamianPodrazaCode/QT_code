#ifndef CAMERASETTINGSWIDGET_H
#define CAMERASETTINGSWIDGET_H

#include <QWidget>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSlider>
#include <QLabel>
#include <QCheckBox>
#include <QComboBox>
#include <QPushButton>
#include <QGroupBox>
#include <QSpinBox>
#include <QTabWidget>
#include <QMap>

#include "imageprocessor.h"
#include "histogramwidget.h"

class SliderControl : public QWidget
{
    Q_OBJECT

public:
    SliderControl(const QString &name, int min, int max, int defaultVal,
                  const QString &suffix = "", QWidget *parent = nullptr);

    int value() const { return m_slider->value(); }
    void setValue(int val) { m_slider->setValue(val); }
    void reset() { m_slider->setValue(m_default); }

signals:
    void valueChanged(int value);

private:
    QSlider *m_slider;
    QLabel *m_valueLabel;
    int m_default;
    QString m_suffix;
};

class CameraSettingsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CameraSettingsWidget(QWidget *parent = nullptr);

    ImageEffects getEffects() const;
    void setEffects(const ImageEffects &effects);
    void updateHistogram(const QImage &image);

signals:
    void settingsChanged();
    void resetRequested();
    void presetRequested(const QString &name);

public slots:
    void resetAll();

private:
    void setupUI();
    QGroupBox* createBasicGroup();
    QGroupBox* createColorGroup();
    QGroupBox* createDetailGroup();
    QGroupBox* createEffectsGroup();
    QGroupBox* createTransformGroup();
    QGroupBox* createPresetsGroup();
    QWidget* createHistogramTab();

    void connectSliders();
    void emitSettingsChanged();

    // Kontrolki - Podstawowe
    SliderControl *m_brightness;
    SliderControl *m_contrast;
    SliderControl *m_exposure;
    SliderControl *m_gamma;
    SliderControl *m_shadows;
    SliderControl *m_highlights;
    SliderControl *m_blacks;
    SliderControl *m_whites;

    // Kontrolki - Kolor
    SliderControl *m_saturation;
    SliderControl *m_vibrance;
    SliderControl *m_hue;
    SliderControl *m_temperature;
    SliderControl *m_tint;

    // Kontrolki - Szczegóły
    SliderControl *m_sharpness;
    SliderControl *m_clarity;
    SliderControl *m_noiseReduction;
    SliderControl *m_blur;

    // Kontrolki - Efekty
    QCheckBox *m_grayscale;
    QCheckBox *m_negative;
    QCheckBox *m_sepia;
    SliderControl *m_vignette;
    SliderControl *m_grain;

    // Kontrolki - Transformacja
    QCheckBox *m_mirrorH;
    QCheckBox *m_mirrorV;
    QComboBox *m_rotation;
    SliderControl *m_digitalZoom;
    SliderControl *m_panX;
    SliderControl *m_panY;

    // Histogram
    HistogramWidget *m_histogram;
    QCheckBox *m_showRGB;
    QCheckBox *m_showLuminance;

    QTabWidget *m_tabWidget;
};

#endif // CAMERASETTINGSWIDGET_H
