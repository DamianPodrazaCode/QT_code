#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H

#include <QImage>
#include <QObject>

struct ImageEffects {
    // Podstawowe regulacje
    int brightness = 0;      // -100 do 100
    int contrast = 0;        // -100 do 100
    int saturation = 0;      // -100 do 100
    int hue = 0;             // -180 do 180
    int sharpness = 0;       // 0 do 100
    int gamma = 100;         // 10 do 300 (100 = 1.0)
    int temperature = 0;     // -100 do 100 (ciepłe/zimne)
    int tint = 0;            // -100 do 100 (zielony/magenta)
    int shadows = 0;         // -100 do 100
    int highlights = 0;      // -100 do 100
    int clarity = 0;         // 0 do 100
    int vibrance = 0;        // -100 do 100
    int exposure = 0;        // -100 do 100
    int blacks = 0;          // -100 do 100
    int whites = 0;          // -100 do 100

    // Redukcja szumu
    int noiseReduction = 0;  // 0 do 100

    // Efekty
    bool grayscale = false;
    bool negative = false;
    bool sepia = false;
    bool mirrorH = false;
    bool mirrorV = false;
    int rotation = 0;        // 0, 90, 180, 270
    int blur = 0;            // 0 do 20
    int vignette = 0;        // 0 do 100
    int grain = 0;           // 0 do 100

    // Korekcja obiektywu
    int distortion = 0;      // -100 do 100
    int chromatic = 0;       // 0 do 100 (redukcja aberracji)

    // Ramka/Zoom
    int digitalZoom = 100;   // 100 do 400 (procent)
    int panX = 0;            // -100 do 100
    int panY = 0;            // -100 do 100

    void reset() {
        *this = ImageEffects();
    }
};

class ImageProcessor : public QObject
{
    Q_OBJECT

public:
    explicit ImageProcessor(QObject *parent = nullptr);

    QImage process(const QImage &input);

    void setEffects(const ImageEffects &effects);
    ImageEffects effects() const { return m_effects; }

    // Histogram
    static void calculateHistogram(const QImage &image,
                                   QVector<int> &red,
                                   QVector<int> &green,
                                   QVector<int> &blue,
                                   QVector<int> &luminance);

private:
    QImage applyBrightnessContrast(const QImage &input);
    QImage applySaturationHue(const QImage &input);
    QImage applyGamma(const QImage &input);
    QImage applyTemperatureTint(const QImage &input);
    QImage applyShadowsHighlights(const QImage &input);
    QImage applyExposure(const QImage &input);
    QImage applySharpness(const QImage &input);
    QImage applyBlur(const QImage &input);
    QImage applyGrayscale(const QImage &input);
    QImage applyNegative(const QImage &input);
    QImage applySepia(const QImage &input);
    QImage applyMirror(const QImage &input);
    QImage applyRotation(const QImage &input);
    QImage applyVignette(const QImage &input);
    QImage applyGrain(const QImage &input);
    QImage applyDigitalZoom(const QImage &input);
    QImage applyNoiseReduction(const QImage &input);
    QImage applyClarity(const QImage &input);
    QImage applyVibrance(const QImage &input);

    ImageEffects m_effects;
};

#endif // IMAGEPROCESSOR_H
