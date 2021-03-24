#include "parts.h"

#include <QFont>
#include <QDebug>
#include <QtMath>

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Неподвижный шарнир~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
Hinge::Hinge() : QGraphicsObject() {}

QRectF Hinge::boundingRect() const
{
    //return QRectF(-scale*100, -scale*100, scale*200, scale*200);
    return QRectF(-scale*10, -scale*25, scale*80, scale*60 + scale*25 + 0.5*scale*80);
}

void Hinge::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setBrush(Qt::NoBrush);
    painter->setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter->rotate(60.0);
    painter->drawLine(0, 0, scale*60, 0);
    painter->translate(scale*60, 0);
    painter->rotate(120.0);
    painter->drawLine(0, 0, scale*60, 0);
    painter->drawLine(-10*scale, 0, scale*70, 0);
    painter->setPen(Qt::NoPen);
    painter->setBrush(QBrush(Qt::black, Qt::BDiagPattern));
    painter->drawRect(-scale*10, 0, scale*80, -scale*25);
    painter->setBrush(Qt::NoBrush);
    painter->setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter->translate(scale*60, 0);
    painter->rotate(120.0);
    painter->drawLine(0, 0, scale*60, 0);
    painter->translate(scale*60, 0);
    painter->rotate(60.0);
    painter->drawEllipse(-scale*40, -scale*40, scale*80, scale*80);
    painter->drawEllipse(-scale*25, -scale*25, scale*50, scale*50);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Подвижный шарнир~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
FixedHinge::FixedHinge()
{

}

QRectF FixedHinge::boundingRect() const
{
    return QRectF(-scale*25, -scale*25, scale*50, scale*50);
}

void FixedHinge::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setBrush(Qt::NoBrush);
    painter->setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter->drawEllipse(-scale*25, -scale*25, scale*50, scale*50);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Ползун~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
Slider::Slider() { }

QRectF Slider::boundingRect() const
{
    return QRectF(-scale*70, -scale*50, scale*140, scale*100);
}

void Slider::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setBrush(Qt::NoBrush);
    painter->setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter->drawRect(-scale*70, -scale*50, scale*140, scale*100);
    painter->drawEllipse(-scale*25, -scale*25, scale*50, scale*50);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Кривошип/шатун~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
Crank::Crank(double L) : QGraphicsObject()
{
    l = L;
}

void Crank::setl(double L)
{
    l = L;
}

QRectF Crank::boundingRect() const
{
    return QRectF(-3, -2, l+6, 4);
}

void Crank::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setBrush(Qt::NoBrush);
    painter->setPen(QPen(Qt::black, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter->drawLine(0, 0, l, 0);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Пунктирная прямая~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
DoshLine::DoshLine(double L)
{
    l = L;
    rect = QRectF(-3, -2, l+6, 4);
}

void DoshLine::setl(double L)
{
    l = L;
    rect = QRectF(-3, -2, l+6, 4);
}

QRectF DoshLine::boundingRect() const
{
    return rect;
}

void DoshLine::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setBrush(Qt::NoBrush);
    painter->setPen(QPen(Qt::black, 3, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin));
    painter->drawLine(0, 0, l, 0);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Стрелка~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
Arrow::Arrow(double L, double Al)
{
    l = L;
    al = Al;
    rect = QRectF(-l*0.5, -l*0.5, l, l);
}

void Arrow::setl(double L)
{
    l = L;
    rect = QRectF(-l*0.5, -l*0.5, l, l);
}

QRectF Arrow::boundingRect() const
{
    return rect;
}

void Arrow::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setBrush(Qt::NoBrush);
    painter->setPen(QPen(color, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter->drawLine(0, 0, l, 0);
    painter->translate(l, 0);
    painter->rotate(180 - al);
    painter->drawLine(0, 0, l * 0.2, 0);
    painter->rotate(2*al);
    painter->drawLine(0, 0, l * 0.2, 0);
    painter->rotate(180 - al);
    painter->translate(-l, 0);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Точка~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
Point::Point(double _vx, double _vy, double _v, double _ax, double _ay, double _a)
{
    vx = _vx;
    vy = _vy;
    v = _v;
    ax = _ax;
    ay = _ay;
    a = _a;

    al = 30;

    double arr[6];
    arr[0] = vx;
    arr[1] = vy;
    arr[2] = v;
    arr[3] = ax;
    arr[4] = ay;
    arr[5] = a;

    double max;
    for (auto element: arr) {
        if (qAbs(element) > max)
            max = qAbs(element);
    }

    rect = QRectF(-max * 0.5, -max * 0.5, max, max);
}

void Point::setSpeedStatus(Constants::SpeedStatus status)
{
    currentSpeedStatus = status;
}

QRectF Point::boundingRect() const
{
    return rect;
}

void Point::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setBrush(Qt::NoBrush);
    painter->setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter->drawEllipse(-5, -5, 10, 10);       //можно убрать при желании

    if (currentAccelStatus != Constants::SHOWNOTHINGACCEL and currentSpeedStatus != Constants::SHOWNOTHINGSPEED
            and currentAccelStatus != Constants::SHOWA and currentSpeedStatus != Constants::SHOWV)
        painter->translate(2, -2);

    if(currentSpeedStatus == Constants::SHOWSPEED
            or currentSpeedStatus == Constants::SHOWVX
            or currentSpeedStatus == Constants::SHOWVXV
            or currentSpeedStatus == Constants::SHOWVXY) {
        painter->setPen(QPen(colorVx, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));      //Vx
        painter->drawLine(0, 0, vx, 0);
        painter->translate(vx, 0);
        painter->rotate(180 - al);
        painter->drawLine(0, 0, vx * 0.2, 0);
        painter->rotate(2*al);
        painter->drawLine(0, 0, vx * 0.2, 0);
        painter->rotate(180 - al);
        painter->translate(-vx, 0);
    }

    if(currentSpeedStatus == Constants::SHOWSPEED
            or currentSpeedStatus == Constants::SHOWVY
            or currentSpeedStatus == Constants::SHOWVYV
            or currentSpeedStatus == Constants::SHOWVXY) {
        painter->setPen(QPen(colorVy, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));      //Vy
        painter->rotate(-90);
        painter->drawLine(0, 0, vy, 0);
        painter->translate(vy, 0);
        painter->rotate(180 - al);
        painter->drawLine(0, 0, vy * 0.2, 0);
        painter->rotate(2*al);
        painter->drawLine(0, 0, vy * 0.2, 0);
        painter->rotate(180 - al);
        painter->translate(-vy, 0);
        painter->rotate(90);
    }

    if(currentSpeedStatus == Constants::SHOWSPEED
            or currentSpeedStatus == Constants::SHOWV
            or currentSpeedStatus == Constants::SHOWVXV
            or currentSpeedStatus == Constants::SHOWVYV) {
        painter->setPen(QPen(colorV, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));      //V
        painter->rotate(-Constants::from_radians_to_degrees(Constants::arcsin(vy / v)));
        painter->drawLine(0, 0, v, 0);
        painter->translate(v, 0);
        painter->rotate(180 - al);
        painter->drawLine(0, 0, v * 0.2, 0);
        painter->rotate(2*al);
        painter->drawLine(0, 0, v * 0.2, 0);
        painter->rotate(180 - al);
        painter->translate(-v, 0);
        painter->rotate(Constants::from_radians_to_degrees(Constants::arcsin(vy / v)));
    }

    if (currentAccelStatus != Constants::SHOWNOTHINGACCEL and currentSpeedStatus != Constants::SHOWNOTHINGSPEED
            and currentAccelStatus != Constants::SHOWA and currentSpeedStatus != Constants::SHOWV)
        painter->translate(-6, 6);

    if(currentAccelStatus == Constants::SHOWACCEL
            or currentAccelStatus == Constants::SHOWAX
            or currentAccelStatus == Constants::SHOWAXA
            or currentAccelStatus == Constants::SHOWAXY) {
        painter->setPen(QPen(colorAx, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));      //Ax
        painter->drawLine(0, 0, ax, 0);
        painter->translate(ax, 0);
        painter->rotate(180 - al);
        painter->drawLine(0, 0, ax * 0.2, 0);
        painter->rotate(2*al);
        painter->drawLine(0, 0, ax * 0.2, 0);
        painter->rotate(180 - al);
        painter->translate(-ax, 0);
    }

    if(currentAccelStatus == Constants::SHOWACCEL
            or currentAccelStatus == Constants::SHOWAY
            or currentAccelStatus == Constants::SHOWAYA
            or currentAccelStatus == Constants::SHOWAXY) {
        painter->setPen(QPen(colorAy, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));      //Ay
        painter->rotate(-90);
        painter->drawLine(0, 0, ay, 0);
        painter->translate(ay, 0);
        painter->rotate(180 - al);
        painter->drawLine(0, 0, ay * 0.2, 0);
        painter->rotate(2*al);
        painter->drawLine(0, 0, ay * 0.2, 0);
        painter->rotate(180 - al);
        painter->translate(-ay, 0);
        painter->rotate(90);
    }

    if(currentAccelStatus == Constants::SHOWACCEL
            or currentAccelStatus == Constants::SHOWA
            or currentAccelStatus == Constants::SHOWAXA
            or currentAccelStatus == Constants::SHOWAYA) {
        painter->setPen(QPen(colorA, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));      //A
        painter->rotate(-Constants::from_radians_to_degrees(Constants::arcsin(ay / a)));
        painter->drawLine(0, 0, a, 0);
        painter->translate(a, 0);
        painter->rotate(180 - al);
        painter->drawLine(0, 0, a * 0.2, 0);
        painter->rotate(2*al);
        painter->drawLine(0, 0, a * 0.2, 0);
        painter->rotate(180 - al);
        painter->translate(-a, 0);
        painter->rotate(Constants::from_radians_to_degrees(Constants::arcsin(ay / a)));
    }

    if (currentAccelStatus != Constants::SHOWNOTHINGACCEL and currentSpeedStatus != Constants::SHOWNOTHINGSPEED
            and currentAccelStatus != Constants::SHOWA and currentSpeedStatus != Constants::SHOWV)
        painter->translate(2, -2);

}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Особая точка~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
SpecialPoint::SpecialPoint(double _xc2, double _yc2, double _l2)
{
    xc2 = _xc2;
    yc2 = -_yc2;
    l = _l2;

    poly.append(QPoint(0, 0));
    poly.append(QPoint(l, 0));
    poly.append(QPoint(xc2, yc2));


    if (xc2 * l >= 0)
        (qAbs(xc2) >= qAbs(l)) ? rect = QRectF(0, 0, xc2, yc2) : rect = QRectF(0, 0, l, yc2);
    else
        (xc2 >= 0) ? rect = QRectF(xc2, 0, -(xc2 + qAbs(l)), yc2) : rect = QRectF(xc2, 0, qAbs(xc2) + l, yc2);
}

void SpecialPoint::setPolygon(double _xc2, double _yc2, double _l)
{
    poly.putPoints(1, 2, _l, 0, _xc2, - _yc2);
    xc2 = _xc2;
    yc2 = - _yc2;
    l = _l;

    if (xc2 * l >= 0)
        (qAbs(xc2) >= qAbs(l)) ? rect = QRectF(0, 0, xc2, yc2) : rect = QRectF(0, 0, l, yc2);
    else
        (xc2 >= 0) ? rect = QRectF(xc2, 0, -(xc2 + qAbs(l)), yc2) : rect = QRectF(xc2, 0, qAbs(xc2) + l, yc2);
}

QRectF SpecialPoint::boundingRect() const
{
    return rect;
}

void SpecialPoint::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(QBrush(Qt::blue, Qt::BDiagPattern));
    painter->setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter->drawPolygon(poly);
    painter->translate(xc2, yc2);
    Point::paint(painter, option, widget);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Полигон треугольник~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
Polygon::Polygon(double _xc2, double _yc2, double _l2)
{
    xc2 = _xc2;
    yc2 = -_yc2;
    l = _l2;

    poly.append(QPoint(0, 0));
    poly.append(QPoint(l, 0));
    poly.append(QPoint(xc2, yc2));


    if (xc2 * l >= 0)
        (qAbs(xc2) >= qAbs(l)) ? rect = QRectF(0, 0, xc2, yc2) : rect = QRectF(0, 0, l, yc2);
    else
        (xc2 >= 0) ? rect = QRectF(xc2, 0, -(xc2 + qAbs(l)), yc2) : rect = QRectF(xc2, 0, qAbs(xc2) + l, yc2);

    //qDebug() << "Polygon: " << poly << Qt::endl;
}

void Polygon::setPolygon(double _xc2, double _yc2, double _l)
{
    poly.putPoints(1, 2, _l, 0, _xc2, - _yc2);
    xc2 = _xc2;
    yc2 = - _yc2;
    l = _l;

    if (xc2 * l >= 0)
        (qAbs(xc2) >= qAbs(l)) ? rect = QRectF(0, 0, xc2, yc2) : rect = QRectF(0, 0, l, yc2);
    else
        (xc2 >= 0) ? rect = QRectF(xc2, 0, -(xc2 + qAbs(l)), yc2) : rect = QRectF(xc2, 0, qAbs(xc2) + l, yc2);
    //qDebug() << "Polygon: " << poly << Qt::endl;

}

QRectF Polygon::boundingRect() const
{
    return rect;
}

void Polygon::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setBrush(QBrush(Qt::blue, Qt::BDiagPattern));
    painter->setPen(QPen(Qt::red, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    //qDebug() << "Polygon: " << poly << Qt::endl;

    painter->drawPolygon(poly);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Текст~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
Text::Text(QFont Font, QString Str)
{
    font = Font;
    font.setBold(true);
    fm = new QFontMetrics(font);
    str = Str;
}

void Text::setText(QString newstr)
{
    str = newstr;
}

QRectF Text::boundingRect() const
{
    return QRectF(0, 0, fm->horizontalAdvance(str), -fm->height());
}

void Text::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setPen(QPen(Qt::black, fm->height()*scale, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter->setFont(font);
    painter->drawText(0, 0, tr("%1").arg(str));
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Размер сцены~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
RectScene::RectScene(double _x, double _y, double _width, double _height)
{
    rect = QRectF(_x, _y, _width, _height);
}

RectScene::RectScene(QRectF currentRect)
{
    int max = 5;
    (currentRect.width() >= currentRect.height()) ? max += currentRect.width() : max += currentRect.height();
    rect = QRectF((currentRect.width()/2+currentRect.x()) - max/2,
                  (currentRect.height()/2+currentRect.y()) - max/2,
                  max, max);
}

void RectScene::setRect(double _x, double _y, double _width, double _height)
{
    rect = QRectF(_x, _y, _width, _height);
}

void RectScene::setRect(QRectF currentRect)
{
    int max = 5;
    (currentRect.width() >= currentRect.height()) ? max += currentRect.width() : max += currentRect.height();
    rect = QRectF((currentRect.width()/2+currentRect.x()) - max/2,
                  (currentRect.height()/2+currentRect.y()) - max/2,
                  max, max);
}

void RectScene::setRectX(double x)
{
    if (x < rect.x()) {
        rect.setX(x);
        rect.setWidth(rect.width() + x);
    }

}

void RectScene::setRectY(double y)
{
    if (y < rect.y()) {
        rect.setY(y);
        rect.setWidth(rect.height() + y);
    }
}

void RectScene::setRectWidth(double width)
{
    if (rect.width() < width)
        rect.setWidth(width);
}

void RectScene::setRectHeight(double Height)
{
    if (rect.height() < Height)
        rect.setHeight(Height);
}

qreal RectScene::getRectX()
{
    return rect.x();
}

qreal RectScene::getRectY()
{
    return rect.y();
}

qreal RectScene::getRectWidth()
{
    return rect.width();
}

qreal RectScene::getRectHeight()
{
    return rect.height();
}

QRectF RectScene::boundingRect() const
{
    return rect;
}

void RectScene::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(painter);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Сцена~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
Scene::Scene(QObject *parent) : QGraphicsScene(parent) {}
Scene::~Scene() {}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Картинка проба~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
Picture::Picture()
{
    O1A = QLine(0, 0, 100, 0);
    AB = QLine(0, 0, 200, 0);
    A = QRect(-10, -10, 20, 20);
    B = QRect(-10, -10, 20, 20);
    slider = QRect(-30, -20, 60, 40);
    rect = QRectF(-300, -300, 600, 600);
}

void Picture::setO1A(double x, double y)
{
    O1A = QLine(0, 0, x, y);
    update();
}

void Picture::setAB(double x, double y)
{
    AB = QLine(0, 0, x, y);
    update();
}

void Picture::setfi1(double angle)
{
    fi1 = angle;
    update();
}

void Picture::setfi2(double angle)
{
    fi2 = angle;
    update();
}

void Picture::setal(double angle)
{
    al = angle;
    update();
}

void Picture::setRectF(double x, double y, double width, double height)
{
    rect = QRectF(x, y, width, height);
    boundingRect();
    update();
}

double Picture::getO1A()
{
    return qSqrt( qPow((O1A.x1() - O1A.x2()) , 2) + qPow((O1A.y1() - O1A.y2()) , 2));
}

double Picture::getAB()
{
    return qSqrt( qPow((AB.x1() - AB.x2()) , 2) + qPow((AB.y1() - AB.y2()) , 2));
}

double Picture::getfi1()
{
    return fi1;
}

double Picture::getfi2()
{
    return fi2;
}

double Picture::getal()
{
    return al;
}

QRectF Picture::getRectF()
{
    return rect;
}

QRectF Picture::boundingRect() const
{
    return rect;
}

void Picture::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setBrush(Qt::black);
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

    painter->rotate(-fi1);
    painter->drawLine(O1A);
    painter->translate(O1A.x2(), O1A.y2());
    painter->rotate(- fi2 + fi1);
    painter->drawEllipse(A);
    painter->drawLine(AB);
    painter->translate(AB.x2(), AB.y2());
    painter->rotate(- al + fi2);
    painter->drawEllipse(B);
    painter->drawRect(slider);
}

void Picture::_fi1_changed()
{
    update();
}

void Picture::_fi2_changed()
{
    update();
}
