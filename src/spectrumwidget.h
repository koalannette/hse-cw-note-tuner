#ifndef SPECTRUMWIDGET_H
#define SPECTRUMWIDGET_H

#include <QWidget>
#include <QTimer>

#include "constants.h"

class SpectrumWidget : public QWidget
{
    Q_OBJECT

public:
    SpectrumWidget();
    void setData(float* data);

    void paintEvent(QPaintEvent* event) override;
    void resizeEvent(QResizeEvent* event) override;

private:
    QTimer* timer;
    int bars[SPECTRUM_BARS];
};

#endif // SPECTRUMWIDGET_H
