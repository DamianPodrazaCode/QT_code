#include "histogramwidget.h"
#include "imageprocessor.h"
#include <QPainter>
#include <QPainterPath>

HistogramWidget::HistogramWidget(QWidget *parent)
    : QWidget(parent)
{
    m_red.resize(256);
    m_green.resize(256);
    m_blue.resize(256);
    m_luminance.resize(256);

    setMinimumSize(256, 100);
    setMaximumHeight(150);
}

void HistogramWidget::updateHistogram(const QImage &image)
{
    ImageProcessor::calculateHistogram(image, m_red, m_green, m_blue, m_luminance);
    update();
}

void HistogramWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Tło
    painter.fillRect(rect(), QColor(30, 30, 30));

    // Znajdź maksimum
    int maxVal = 1;
    for (int i = 0; i < 256; ++i) {
        if (m_showRGB) {
            maxVal = qMax(maxVal, m_red[i]);
            maxVal = qMax(maxVal, m_green[i]);
            maxVal = qMax(maxVal, m_blue[i]);
        }
        if (m_showLuminance) {
            maxVal = qMax(maxVal, m_luminance[i]);
        }
    }

    float scaleX = width() / 256.0f;
    float scaleY = (height() - 10) / float(maxVal);

    auto drawChannel = [&](const QVector<int> &data, const QColor &color) {
        QPainterPath path;
        path.moveTo(0, height());

        for (int i = 0; i < 256; ++i) {
            float x = i * scaleX;
            float y = height() - data[i] * scaleY;
            path.lineTo(x, y);
        }

        path.lineTo(width(), height());
        path.closeSubpath();

        QColor fillColor = color;
        fillColor.setAlpha(80);
        painter.fillPath(path, fillColor);

        painter.setPen(QPen(color, 1));
        painter.drawPath(path);
    };

    if (m_showRGB) {
        drawChannel(m_blue, QColor(50, 50, 255));
        drawChannel(m_green, QColor(50, 255, 50));
        drawChannel(m_red, QColor(255, 50, 50));
    }

    if (m_showLuminance) {
        drawChannel(m_luminance, QColor(200, 200, 200));
    }

    // Ramka
    painter.setPen(QPen(QColor(80, 80, 80), 1));
    painter.drawRect(rect().adjusted(0, 0, -1, -1));
}
