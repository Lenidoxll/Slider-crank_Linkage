#ifndef FIXEDHINGE_H
#define FIXEDHINGE_H

#include <QGraphicsObject>
#include <QObject>
#include <QPainter>

class FixedHinge : public QGraphicsObject
{
    Q_OBJECT
public:
    explicit FixedHinge();
private:
    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

#endif // FIXEDHINGE_H
