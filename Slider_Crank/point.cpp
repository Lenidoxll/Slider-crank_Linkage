#include "point.h"
#include <QPainter>
#include <QDebug>
#include <QtMath>

Point::Point(QPoint a, QPoint b, int distance) : QGraphicsObject()
{
    A = a;
    B = b;
    distance_from_A_to_B = distance;
}

void Point::setA(QPoint a)
{
    A = a;
}

void Point::setB(QPoint b)
{
    B = b;
}

QRectF Point::boundingRect() const
{
    return QRectF(-250, -250, 500, 500);
}

void Point::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    //painter->setBrush(Qt::black);
    painter->translate(A);
    int x = B.x() - A.x();
    int y = B.y() - A.y();
    qreal distane = qSqrt( x*x + y*y);
    qreal rotation = qAsin(y / distane);
    painter->rotate(rotation * 57.2958);
    painter->translate(distance_from_A_to_B, 0);
    painter->setPen(QPen(Qt::yellow, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter->drawLine(0, 0, 0, 200);
    painter->setPen(QPen(Qt::gray, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter->drawLine(0, 0, 200, 0);
    //qDebug() << "x = " << x << ", y = " << y <<", distnce = " << distane << ", roate = " << rotation*57.2958 << Qt::endl;
}
