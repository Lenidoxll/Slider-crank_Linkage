#include "crank.h"
#include <QDebug>

Crank::Crank(QPoint a, QPoint b) : QGraphicsObject()
{
//    setFlag(QGraphicsItem::ItemIsSelectable);
//    setSelected(false);
    A = a;
    B = b;
}

Crank::Crank(int x1, int y1, int x2, int y2) : QGraphicsObject()
{
//    setFlag(QGraphicsItem::ItemIsSelectable);
//    setSelected(false);
    A.setX(x1);
    A.setY(y1);
    B.setX(x2);
    B.setY(y2);
}

void Crank::setA(QPoint a)
{
    A = a;
}

void Crank::setB(QPoint b)
{
    B = b;
}

bool Crank::isBelonging(QPointF point)
{
    //добавить проверку возможности вычисления (по у)
    if (A.x() != B.x())
    {
        double good_left_part = (point.y() - B.y()) / (A.y() - B.y());
        double good_right_part = (point.x() - B.x()) / (A.x() - B.x());
        if (abs(good_left_part - good_right_part) < 0.3)
        {
            qDebug() << "Good A.x=" << A.x() << "A.y=" << A.y() << "B.x=" << B.x() << "B.y=" << B.y() << ", good_left_part=" << good_left_part << ", good_right_part=" << good_right_part << ", point.x=" << point.x() << ", point.y=" << point.y();
            return true;
        }
        else
        {
            qDebug() << " Bad A.x=" << A.x() << "A.y=" << A.y() << "B.x=" << B.x() << "B.y=" << B.y() << ", good_left_part=" << good_left_part << ", good_right_part=" << good_right_part << ", point.x=" << point.x() << ", point.y=" << point.y();
            return false;
        }
    } else {
        if (point.x() >= A.x() and point.x() <= A.x())
        {
            qDebug() << "A.x=" << A.x() << ", point.x=" << point.x();
            return true;
        }
        else
        {
            qDebug() << "A.x=" << A.x() << ", point.x=" << point.x();
            return false;
        }
    }
}

//void Crank::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
//{

//}

QRectF Crank::boundingRect() const
{
    return QRectF(-250, -250, 500, 500);
}

void Crank::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setBrush(Qt::NoBrush);
    if (belong)
        painter->setPen(QPen(Qt::red, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    else
        painter->setPen(QPen(Qt::black, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter->translate(-A);
    painter->drawLine(A, B);
    painter->translate(A);
    painter->setPen(QPen(Qt::red, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter->drawLine(0, 0, 0, 200);
    painter->setPen(QPen(Qt::green, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter->drawLine(0, 0, 200, 0);
}

