#ifndef PLOT_H
#define PLOT_H

#include <QWidget>
#include "qcustomplot.h"

class Plot : public QWidget
{
    Q_OBJECT

public:
    Plot(QWidget *parent = nullptr);
    QCustomPlot* customPlot;
    QVector <double> key_B, value_B;
public slots:
    void slot_xBChanged();
    void resizeEvent(QResizeEvent* event);

};
#endif // PLOT_H
