#ifndef POINT_H
#define POINT_H

#include <QGraphicsObject>

class Point : public QGraphicsObject
{
    Q_OBJECT
public:
    explicit Point(QPoint a = QPoint(0, 0), QPoint b = QPoint(0, 0), int distance = 0);
    void setA(QPoint a = QPoint(0, 0));
    void setB(QPoint b = QPoint(0, 0));

    int distance_from_A_to_B;
    QPoint A, B;
private:
    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

#endif // POINT_H
