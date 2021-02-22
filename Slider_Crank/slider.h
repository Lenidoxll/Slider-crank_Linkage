#ifndef SLIDER_H
#define SLIDER_H

#include <QGraphicsObject>
#include <QObject>
#include <QPainter>

class Slider : public QGraphicsObject
{
    Q_OBJECT
public:
    Slider();
private:
    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

#endif // SLIDER_H
