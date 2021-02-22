#include "plot.h"
#include <QTimer>
#include <QDebug>

Plot::Plot(QWidget *parent)
    : QWidget(parent)
{
    this->resize(1200, 1000);
    this->setMinimumSize(600, 500);
    customPlot = new QCustomPlot(this);
    customPlot->setGeometry(0, 0, this->width(), this->height());
    customPlot->setInteraction(QCP::iRangeZoom, true);
    customPlot->setInteraction(QCP::iRangeDrag, true);
    customPlot->axisRect()->setRangeZoom(Qt::Horizontal);
    customPlot->axisRect()->setRangeDrag(Qt::Horizontal);
    customPlot->xAxis->setLabel("time(ms)");
    customPlot->yAxis->setLabel("coordinate x of point B");
    customPlot->xAxis->setTickLabelFont(QFont(QFont().family(), 8));
    customPlot->yAxis->setTickLabelFont(QFont(QFont().family(), 8));

    customPlot->xAxis->setRange(0, 10000);
    customPlot->yAxis->setRange(250, 550);
    customPlot->replot();

    key_B.append(0);
    value_B.append(300);
}

void Plot::slot_xBChanged()
{
    customPlot->clearGraphs();
    customPlot->addGraph();
    customPlot->graph(0)->setPen(QPen(Qt::blue)); // line color blue for first graph
    customPlot->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20)));
    customPlot->graph(0)->setData(key_B, value_B);
    customPlot->replot();
}

void Plot::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
    customPlot->setGeometry(0, 0, this->width(), this->height());
}
