#include "hinge.h"
#include <QPainter>

Hinge::Hinge() : QGraphicsObject() {}

QRectF Hinge::boundingRect() const
{
    return QRectF(-100, -100, 200, 200);
}

void Hinge::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setBrush(Qt::NoBrush);
    painter->setPen(QPen(Qt::black, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter->rotate(60.0);
    painter->drawLine(0, 0, 60, 0);
    painter->translate(60, 0);
    painter->rotate(120.0);
    painter->drawLine(0, 0, 60, 0);
    painter->drawLine(-10, 0, 70, 0);
    painter->setPen(Qt::NoPen);
    painter->setBrush(QBrush(Qt::black, Qt::BDiagPattern));
    painter->drawRect(-10, 0, 80, -25);
    painter->setBrush(Qt::NoBrush);
    painter->setPen(QPen(Qt::black, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter->translate(60, 0);
    painter->rotate(120.0);
    painter->drawLine(0, 0, 60, 0);
    painter->translate(60, 0);
    painter->rotate(60.0);
    painter->drawEllipse(-40, -40, 80, 80);
    painter->drawEllipse(-25, -25, 50, 50);
    painter->setPen(QPen(Qt::blue, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter->drawLine(0, 0, 0, 200);
    painter->setPen(QPen(Qt::yellow, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter->drawLine(0, 0, 200, 0);

//    QPolygon polygon;
//    polygon << QPoint(0,-30) << QPoint(24, 30) << QPoint(-24, 30);
//    painter->setBrush(Qt::NoBrush);
//    painter->setPen(QPen(Qt::black, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
//    painter->drawPolygon(polygon);
//    painter->drawEllipse(-40, -40, 80, 80);
//    painter->drawEllipse(-25, -25, 50, 50);
}

