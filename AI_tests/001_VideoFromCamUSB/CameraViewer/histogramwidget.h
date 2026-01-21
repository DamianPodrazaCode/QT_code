#ifndef HISTOGRAMWIDGET_H
#define HISTOGRAMWIDGET_H

#include <QWidget>
#include <QVector>
#include <QImage>

class HistogramWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HistogramWidget(QWidget *parent = nullptr);

    void updateHistogram(const QImage &image);
    void setShowRGB(bool show) { m_showRGB = show; update(); }
    void setShowLuminance(bool show) { m_showLuminance = show; update(); }

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QVector<int> m_red;
    QVector<int> m_green;
    QVector<int> m_blue;
    QVector<int> m_luminance;

    bool m_showRGB = true;
    bool m_showLuminance = true;
};

#endif // HISTOGRAMWIDGET_H
