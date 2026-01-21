#include "imageprocessor.h"
#include <QtMath>
#include <QRandomGenerator>
#include <algorithm>

ImageProcessor::ImageProcessor(QObject *parent)
    : QObject(parent)
{
}

void ImageProcessor::setEffects(const ImageEffects &effects)
{
    m_effects = effects;
}

QImage ImageProcessor::process(const QImage &input)
{
    if (input.isNull()) return input;

    QImage result = input.convertToFormat(QImage::Format_RGB32);

    // Kolejność przetwarzania ma znaczenie!

    // 1. Transformacje geometryczne
    if (m_effects.rotation != 0) {
        result = applyRotation(result);
    }
    if (m_effects.mirrorH || m_effects.mirrorV) {
        result = applyMirror(result);
    }
    if (m_effects.digitalZoom != 100) {
        result = applyDigitalZoom(result);
    }

    // 2. Korekcja ekspozycji i tonalna
    if (m_effects.exposure != 0) {
        result = applyExposure(result);
    }
    if (m_effects.brightness != 0 || m_effects.contrast != 0) {
        result = applyBrightnessContrast(result);
    }
    if (m_effects.shadows != 0 || m_effects.highlights != 0 ||
        m_effects.blacks != 0 || m_effects.whites != 0) {
        result = applyShadowsHighlights(result);
    }
    if (m_effects.gamma != 100) {
        result = applyGamma(result);
    }

    // 3. Korekcja kolorów
    if (m_effects.temperature != 0 || m_effects.tint != 0) {
        result = applyTemperatureTint(result);
    }
    if (m_effects.saturation != 0 || m_effects.hue != 0) {
        result = applySaturationHue(result);
    }
    if (m_effects.vibrance != 0) {
        result = applyVibrance(result);
    }

    // 4. Szczegóły
    if (m_effects.clarity != 0) {
        result = applyClarity(result);
    }
    if (m_effects.noiseReduction > 0) {
        result = applyNoiseReduction(result);
    }
    if (m_effects.sharpness > 0) {
        result = applySharpness(result);
    }
    if (m_effects.blur > 0) {
        result = applyBlur(result);
    }

    // 5. Efekty specjalne
    if (m_effects.grayscale) {
        result = applyGrayscale(result);
    }
    if (m_effects.sepia) {
        result = applySepia(result);
    }
    if (m_effects.negative) {
        result = applyNegative(result);
    }
    if (m_effects.vignette > 0) {
        result = applyVignette(result);
    }
    if (m_effects.grain > 0) {
        result = applyGrain(result);
    }

    return result;
}

QImage ImageProcessor::applyBrightnessContrast(const QImage &input)
{
    QImage result = input;

    float brightness = m_effects.brightness / 100.0f;
    float contrast = (m_effects.contrast + 100) / 100.0f;
    contrast *= contrast; // Nieliniowa krzywa

    for (int y = 0; y < result.height(); ++y) {
        QRgb *line = reinterpret_cast<QRgb*>(result.scanLine(y));
        for (int x = 0; x < result.width(); ++x) {
            int r = qRed(line[x]);
            int g = qGreen(line[x]);
            int b = qBlue(line[x]);

            // Brightness
            r = qBound(0, r + int(brightness * 255), 255);
            g = qBound(0, g + int(brightness * 255), 255);
            b = qBound(0, b + int(brightness * 255), 255);

            // Contrast
            r = qBound(0, int((r - 128) * contrast + 128), 255);
            g = qBound(0, int((g - 128) * contrast + 128), 255);
            b = qBound(0, int((b - 128) * contrast + 128), 255);

            line[x] = qRgb(r, g, b);
        }
    }

    return result;
}

QImage ImageProcessor::applySaturationHue(const QImage &input)
{
    QImage result = input;

    float satFactor = (m_effects.saturation + 100) / 100.0f;
    float hueShift = m_effects.hue;

    for (int y = 0; y < result.height(); ++y) {
        QRgb *line = reinterpret_cast<QRgb*>(result.scanLine(y));
        for (int x = 0; x < result.width(); ++x) {
            QColor color(line[x]);

            int h, s, l;
            color.getHsl(&h, &s, &l);

            // Hue shift
            h = (h + int(hueShift) + 360) % 360;

            // Saturation
            s = qBound(0, int(s * satFactor), 255);

            color.setHsl(h, s, l);
            line[x] = color.rgb();
        }
    }

    return result;
}

QImage ImageProcessor::applyGamma(const QImage &input)
{
    QImage result = input;

    float gamma = m_effects.gamma / 100.0f;
    float invGamma = 1.0f / gamma;

    // Lookup table dla szybkości
    uchar lut[256];
    for (int i = 0; i < 256; ++i) {
        lut[i] = qBound(0, int(255 * qPow(i / 255.0f, invGamma)), 255);
    }

    for (int y = 0; y < result.height(); ++y) {
        QRgb *line = reinterpret_cast<QRgb*>(result.scanLine(y));
        for (int x = 0; x < result.width(); ++x) {
            int r = lut[qRed(line[x])];
            int g = lut[qGreen(line[x])];
            int b = lut[qBlue(line[x])];
            line[x] = qRgb(r, g, b);
        }
    }

    return result;
}

QImage ImageProcessor::applyTemperatureTint(const QImage &input)
{
    QImage result = input;

    float temp = m_effects.temperature / 100.0f;
    float tint = m_effects.tint / 100.0f;

    for (int y = 0; y < result.height(); ++y) {
        QRgb *line = reinterpret_cast<QRgb*>(result.scanLine(y));
        for (int x = 0; x < result.width(); ++x) {
            int r = qRed(line[x]);
            int g = qGreen(line[x]);
            int b = qBlue(line[x]);

            // Temperature: + = ciepły (więcej czerwonego/żółtego)
            r = qBound(0, r + int(temp * 30), 255);
            b = qBound(0, b - int(temp * 30), 255);

            // Tint: + = magenta, - = zielony
            g = qBound(0, g - int(tint * 30), 255);
            r = qBound(0, r + int(tint * 15), 255);
            b = qBound(0, b + int(tint * 15), 255);

            line[x] = qRgb(r, g, b);
        }
    }

    return result;
}

QImage ImageProcessor::applyShadowsHighlights(const QImage &input)
{
    QImage result = input;

    float shadows = m_effects.shadows / 100.0f;
    float highlights = m_effects.highlights / 100.0f;
    float blacks = m_effects.blacks / 100.0f;
    float whites = m_effects.whites / 100.0f;

    for (int y = 0; y < result.height(); ++y) {
        QRgb *line = reinterpret_cast<QRgb*>(result.scanLine(y));
        for (int x = 0; x < result.width(); ++x) {
            int r = qRed(line[x]);
            int g = qGreen(line[x]);
            int b = qBlue(line[x]);

            float luminance = (r * 0.299f + g * 0.587f + b * 0.114f) / 255.0f;

            float shadowWeight = 1.0f - luminance;
            shadowWeight = shadowWeight * shadowWeight;

            float highlightWeight = luminance;
            highlightWeight = highlightWeight * highlightWeight;

            float shadowAdjust = shadows * shadowWeight * 50;
            float highlightAdjust = highlights * highlightWeight * 50;
            float blackAdjust = blacks * (1.0f - luminance) * 30;
            float whiteAdjust = whites * luminance * 30;

            float adjust = shadowAdjust + highlightAdjust + blackAdjust + whiteAdjust;

            r = qBound(0, r + int(adjust), 255);
            g = qBound(0, g + int(adjust), 255);
            b = qBound(0, b + int(adjust), 255);

            line[x] = qRgb(r, g, b);
        }
    }

    return result;
}

QImage ImageProcessor::applyExposure(const QImage &input)
{
    QImage result = input;

    float exposure = qPow(2.0f, m_effects.exposure / 50.0f);

    for (int y = 0; y < result.height(); ++y) {
        QRgb *line = reinterpret_cast<QRgb*>(result.scanLine(y));
        for (int x = 0; x < result.width(); ++x) {
            int r = qBound(0, int(qRed(line[x]) * exposure), 255);
            int g = qBound(0, int(qGreen(line[x]) * exposure), 255);
            int b = qBound(0, int(qBlue(line[x]) * exposure), 255);
            line[x] = qRgb(r, g, b);
        }
    }

    return result;
}

QImage ImageProcessor::applySharpness(const QImage &input)
{
    if (m_effects.sharpness == 0) return input;

    QImage result = input;
    float strength = m_effects.sharpness / 100.0f * 2.0f;

    // Kernel wyostrzający
    for (int y = 1; y < result.height() - 1; ++y) {
        for (int x = 1; x < result.width() - 1; ++x) {
            QRgb center = input.pixel(x, y);
            QRgb top = input.pixel(x, y - 1);
            QRgb bottom = input.pixel(x, y + 1);
            QRgb left = input.pixel(x - 1, y);
            QRgb right = input.pixel(x + 1, y);

            int r = qRed(center) + strength * (4 * qRed(center) - qRed(top) - qRed(bottom) - qRed(left) - qRed(right));
            int g = qGreen(center) + strength * (4 * qGreen(center) - qGreen(top) - qGreen(bottom) - qGreen(left) - qGreen(right));
            int b = qBlue(center) + strength * (4 * qBlue(center) - qBlue(top) - qBlue(bottom) - qBlue(left) - qBlue(right));

            result.setPixel(x, y, qRgb(qBound(0, r, 255), qBound(0, g, 255), qBound(0, b, 255)));
        }
    }

    return result;
}

QImage ImageProcessor::applyBlur(const QImage &input)
{
    if (m_effects.blur == 0) return input;

    QImage result = input;
    int radius = m_effects.blur;

    // Box blur prosty
    for (int y = radius; y < result.height() - radius; ++y) {
        for (int x = radius; x < result.width() - radius; ++x) {
            int sumR = 0, sumG = 0, sumB = 0;
            int count = 0;

            for (int dy = -radius; dy <= radius; ++dy) {
                for (int dx = -radius; dx <= radius; ++dx) {
                    QRgb pixel = input.pixel(x + dx, y + dy);
                    sumR += qRed(pixel);
                    sumG += qGreen(pixel);
                    sumB += qBlue(pixel);
                    count++;
                }
            }

            result.setPixel(x, y, qRgb(sumR / count, sumG / count, sumB / count));
        }
    }

    return result;
}

QImage ImageProcessor::applyGrayscale(const QImage &input)
{
    QImage result = input;

    for (int y = 0; y < result.height(); ++y) {
        QRgb *line = reinterpret_cast<QRgb*>(result.scanLine(y));
        for (int x = 0; x < result.width(); ++x) {
            int gray = qGray(line[x]);
            line[x] = qRgb(gray, gray, gray);
        }
    }

    return result;
}

QImage ImageProcessor::applyNegative(const QImage &input)
{
    QImage result = input;
    result.invertPixels(QImage::InvertRgb);
    return result;
}

QImage ImageProcessor::applySepia(const QImage &input)
{
    QImage result = input;

    for (int y = 0; y < result.height(); ++y) {
        QRgb *line = reinterpret_cast<QRgb*>(result.scanLine(y));
        for (int x = 0; x < result.width(); ++x) {
            int r = qRed(line[x]);
            int g = qGreen(line[x]);
            int b = qBlue(line[x]);

            int newR = qBound(0, int(r * 0.393 + g * 0.769 + b * 0.189), 255);
            int newG = qBound(0, int(r * 0.349 + g * 0.686 + b * 0.168), 255);
            int newB = qBound(0, int(r * 0.272 + g * 0.534 + b * 0.131), 255);

            line[x] = qRgb(newR, newG, newB);
        }
    }

    return result;
}

QImage ImageProcessor::applyMirror(const QImage &input)
{
    return input.mirrored(m_effects.mirrorH, m_effects.mirrorV);
}

QImage ImageProcessor::applyRotation(const QImage &input)
{
    if (m_effects.rotation == 0) return input;

    QTransform transform;
    transform.rotate(m_effects.rotation);
    return input.transformed(transform, Qt::SmoothTransformation);
}

QImage ImageProcessor::applyVignette(const QImage &input)
{
    if (m_effects.vignette == 0) return input;

    QImage result = input;

    float strength = m_effects.vignette / 100.0f;
    float centerX = result.width() / 2.0f;
    float centerY = result.height() / 2.0f;
    float maxDist = qSqrt(centerX * centerX + centerY * centerY);

    for (int y = 0; y < result.height(); ++y) {
        QRgb *line = reinterpret_cast<QRgb*>(result.scanLine(y));
        for (int x = 0; x < result.width(); ++x) {
            float dx = x - centerX;
            float dy = y - centerY;
            float dist = qSqrt(dx * dx + dy * dy) / maxDist;

            float vignette = 1.0f - dist * dist * strength;
            vignette = qMax(0.0f, vignette);

            int r = qBound(0, int(qRed(line[x]) * vignette), 255);
            int g = qBound(0, int(qGreen(line[x]) * vignette), 255);
            int b = qBound(0, int(qBlue(line[x]) * vignette), 255);

            line[x] = qRgb(r, g, b);
        }
    }

    return result;
}

QImage ImageProcessor::applyGrain(const QImage &input)
{
    if (m_effects.grain == 0) return input;

    QImage result = input;
    float strength = m_effects.grain / 100.0f * 50;

    for (int y = 0; y < result.height(); ++y) {
        QRgb *line = reinterpret_cast<QRgb*>(result.scanLine(y));
        for (int x = 0; x < result.width(); ++x) {
            int noise = int((QRandomGenerator::global()->generateDouble() - 0.5) * 2 * strength);

            int r = qBound(0, qRed(line[x]) + noise, 255);
            int g = qBound(0, qGreen(line[x]) + noise, 255);
            int b = qBound(0, qBlue(line[x]) + noise, 255);

            line[x] = qRgb(r, g, b);
        }
    }

    return result;
}

QImage ImageProcessor::applyDigitalZoom(const QImage &input)
{
    if (m_effects.digitalZoom == 100 && m_effects.panX == 0 && m_effects.panY == 0) {
        return input;
    }

    float zoom = m_effects.digitalZoom / 100.0f;

    int newW = int(input.width() / zoom);
    int newH = int(input.height() / zoom);

    int offsetX = (input.width() - newW) / 2 + int(m_effects.panX * newW / 200.0f);
    int offsetY = (input.height() - newH) / 2 + int(m_effects.panY * newH / 200.0f);

    offsetX = qBound(0, offsetX, input.width() - newW);
    offsetY = qBound(0, offsetY, input.height() - newH);

    QRect cropRect(offsetX, offsetY, newW, newH);
    QImage cropped = input.copy(cropRect);

    return cropped.scaled(input.size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
}

QImage ImageProcessor::applyNoiseReduction(const QImage &input)
{
    if (m_effects.noiseReduction == 0) return input;

    // Prosty median filter
    QImage result = input;
    int strength = 1 + m_effects.noiseReduction / 50;

    for (int y = strength; y < result.height() - strength; ++y) {
        for (int x = strength; x < result.width() - strength; ++x) {
            QVector<int> reds, greens, blues;

            for (int dy = -strength; dy <= strength; ++dy) {
                for (int dx = -strength; dx <= strength; ++dx) {
                    QRgb pixel = input.pixel(x + dx, y + dy);
                    reds.append(qRed(pixel));
                    greens.append(qGreen(pixel));
                    blues.append(qBlue(pixel));
                }
            }

            std::sort(reds.begin(), reds.end());
            std::sort(greens.begin(), greens.end());
            std::sort(blues.begin(), blues.end());

            int mid = reds.size() / 2;
            result.setPixel(x, y, qRgb(reds[mid], greens[mid], blues[mid]));
        }
    }

    return result;
}

QImage ImageProcessor::applyClarity(const QImage &input)
{
    if (m_effects.clarity == 0) return input;

    // Clarity = local contrast enhancement
    QImage blurred = input;

    // Najpierw blur
    int radius = 5;
    for (int y = radius; y < blurred.height() - radius; ++y) {
        for (int x = radius; x < blurred.width() - radius; ++x) {
            int sumR = 0, sumG = 0, sumB = 0;
            int count = 0;

            for (int dy = -radius; dy <= radius; dy += 2) {
                for (int dx = -radius; dx <= radius; dx += 2) {
                    QRgb pixel = input.pixel(x + dx, y + dy);
                    sumR += qRed(pixel);
                    sumG += qGreen(pixel);
                    sumB += qBlue(pixel);
                    count++;
                }
            }

            blurred.setPixel(x, y, qRgb(sumR / count, sumG / count, sumB / count));
        }
    }

    // Blend z unsharp mask
    QImage result = input;
    float strength = m_effects.clarity / 100.0f;

    for (int y = 0; y < result.height(); ++y) {
        QRgb *line = reinterpret_cast<QRgb*>(result.scanLine(y));
        for (int x = 0; x < result.width(); ++x) {
            QRgb orig = input.pixel(x, y);
            QRgb blur = blurred.pixel(x, y);

            int r = qBound(0, int(qRed(orig) + strength * (qRed(orig) - qRed(blur))), 255);
            int g = qBound(0, int(qGreen(orig) + strength * (qGreen(orig) - qGreen(blur))), 255);
            int b = qBound(0, int(qBlue(orig) + strength * (qBlue(orig) - qBlue(blur))), 255);

            line[x] = qRgb(r, g, b);
        }
    }

    return result;
}

QImage ImageProcessor::applyVibrance(const QImage &input)
{
    if (m_effects.vibrance == 0) return input;

    QImage result = input;
    float strength = m_effects.vibrance / 100.0f;

    for (int y = 0; y < result.height(); ++y) {
        QRgb *line = reinterpret_cast<QRgb*>(result.scanLine(y));
        for (int x = 0; x < result.width(); ++x) {
            int r = qRed(line[x]);
            int g = qGreen(line[x]);
            int b = qBlue(line[x]);

            int maxVal = qMax(r, qMax(g, b));
            int minVal = qMin(r, qMin(g, b));
            float saturation = (maxVal == 0) ? 0 : (maxVal - minVal) / float(maxVal);

            // Mniej nasycone kolory dostają więcej boost
            float boost = 1.0f + strength * (1.0f - saturation);

            QColor color(r, g, b);
            int h, s, l;
            color.getHsl(&h, &s, &l);
            s = qBound(0, int(s * boost), 255);
            color.setHsl(h, s, l);

            line[x] = color.rgb();
        }
    }

    return result;
}

void ImageProcessor::calculateHistogram(const QImage &image,
                                        QVector<int> &red,
                                        QVector<int> &green,
                                        QVector<int> &blue,
                                        QVector<int> &luminance)
{
    red.fill(0, 256);
    green.fill(0, 256);
    blue.fill(0, 256);
    luminance.fill(0, 256);

    for (int y = 0; y < image.height(); ++y) {
        for (int x = 0; x < image.width(); ++x) {
            QRgb pixel = image.pixel(x, y);
            red[qRed(pixel)]++;
            green[qGreen(pixel)]++;
            blue[qBlue(pixel)]++;
            luminance[qGray(pixel)]++;
        }
    }
}
