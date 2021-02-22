#ifndef HINGE_H
#define HINGE_H

#include <QGraphicsObject>
#include <QObject>
#include <QTimer>

class Hinge : public QGraphicsObject
{
    Q_OBJECT
public:
    explicit Hinge();
private:
    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

#endif // HINGE_H
