#ifndef CRANK_H
#define CRANK_H

#include <QGraphicsObject>
#include <QObject>
#include <QPainter>

class Crank : public QGraphicsObject
{
    Q_OBJECT
public:
    explicit Crank(QPoint a = QPoint(0, 0), QPoint b = QPoint(0, 0));
    explicit Crank(int x1, int y1, int x2, int y2);
    void setA(QPoint a = QPoint(0, 0));
    void setB(QPoint b = QPoint(0, 0));

    bool isBelonging(QPointF point);
    bool belong = false;

//    void hoverMoveEvent(QGraphicsSceneHoverEvent* event) override;
//    void hoverLeaveEvent(QGraphicsSceneHoverEvent* event) override;

private:
    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    QPoint A, B;
};

#endif // CRANK_H
