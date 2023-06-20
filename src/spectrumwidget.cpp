#include "spectrumwidget.h"

#include "recordmanager.h"

#include <cmath>
#include <QPainter>

SpectrumWidget::SpectrumWidget() {
    setFixedHeight(SPECTRUM_HEIGHT);

    for (int i = 0; i < SPECTRUM_BARS; i++) {
        bars[i] = 3;
    }

    this->setMinimumWidth(SPECTRUM_BARS);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    timer = new QTimer(this);
    timer->setInterval(1000 / 60);
    timer->start();

    connect(RecordManager::getInstance(), &RecordManager::fftProcessed, this, &SpectrumWidget::setData);
    connect(timer, &QTimer::timeout, [=]() {
        if (RecordManager::getInstance()->isRecording()) {
            float fft[SPECTRUM_BARS];
            BASS_ChannelGetData(RecordManager::getInstance()->getRec(), fft, BASS_DATA_FFT1024);
            setData(fft);

            repaint();
        }
    });
}

void SpectrumWidget::setData(float *data)
{
    for (int i = 0; i < SPECTRUM_BARS; i++) {
        bars[i] = sqrt(data[i]) * 3 * SPECTRUM_HEIGHT - 4;
        bars[i] = fmin(SPECTRUM_HEIGHT, bars[i]);
        bars[i] = fmax(3, bars[i]);
    }
}

void SpectrumWidget::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    int barWidth = width() / SPECTRUM_BARS;
    int barPadding = (width() - (barWidth * SPECTRUM_BARS)) / 2;

    for (int i = 0; i < SPECTRUM_BARS; i++) {
        painter.fillRect(barPadding + i * barWidth, (SPECTRUM_HEIGHT - bars[i]) / 2, barWidth, bars[i], Qt::black);
    }
}

void SpectrumWidget::resizeEvent(QResizeEvent *event)
{
    update();
}
