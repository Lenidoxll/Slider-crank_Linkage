#include "mechanism_1.h"
#include "parts.h"

#include <QtMath>
#include <QTimer>
#include <QDebug>

Mechanism_1::Mechanism_1(QFont _font, double l1, double l2,
                         double _xa, double _ya, double _xb, double _yb, double _xl, double _yl,
                         double _xc, double _yc, double _xc2, double _yc2,
                         double fi1, double fi2, double al,
                         double _xmin, double _ymin, double _xmax, double _ymax, double _xo1, double _yo1,
                         QWidget *parent) : QGraphicsView(parent)
{
    scene = new Scene();
    this->setScene(scene);

    this->setRenderHint(QPainter::Antialiasing);    // Устанавливаем сглаживание
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // Отключаем скроллбар по вертикали
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // Отключаем скроллбар по горизонтали

    scaling_window(l1, l2);

    fi1g = -fi1;
    fi2g = -fi2;
    alg = -al;

    xo1 = _xo1*scale;
    yo1 = -_yo1*scale;
    xa = _xa*scale;
    ya = -_ya*scale;
    xb = _xb*scale;
    yb = -_yb*scale;
    xl = _xl*scale;
    yl = -_yl*scale;
    xc = _xc*scale;
    yc = -_yc*scale;

    xmin = _xmin*scale;
    ymin = _ymin*scale;
    xmax = _xmax*scale;
    ymax = _ymax*scale;

    Ox = new Arrow(30);
    scene->addItem(Ox);

    textX = new Text(_font, QString("x"));
    textX->setPos(xo1 + Ox->getl() - 3 * 0.5 / scale * textX->getHorizontalAdvance(), yo1 + 2 / scale * textX->getHeight());
    textX->setScale(3/scale);
    scene->addItem(textX);

    Oy = new Arrow(30);
    Oy->setRotation(-90);
    scene->addItem(Oy);

    textY = new Text(_font, QString("y"));
    textY->setPos(xo1 - 6 / scale * textY->getHorizontalAdvance(), yo1 - Oy->getl() + 3 * 0.5 / scale * textY->getHeight());
    textY->setScale(3/scale);
    scene->addItem(textY);

    O1 = new Hinge(); //неподвижный шарнир
    O1->setPos(xo1, yo1);
    scene->addItem(O1);

    O1A = new Crank(l1*scale); //кривошип
    O1A->setPos(xo1, yo1);
    O1A->setRotation(fi1g);
    scene->addItem(O1A);

    pointO1 = new Point();
    pointO1->setPos(xo1, yo1);
    scene->addItem(pointO1);

    A = new FixedHinge(); //шарнир
    A->setPos(xa, ya);
    scene->addItem(A);


    B = new Slider(); //ползун
    B->setPos(xb, yb);
    B->setRotation(alg);
    scene->addItem(B);

    L = new FixedHinge();
    L->setPos(xl, yl);
    scene->addItem(L);

    if ( xb < xl and qAbs(xb - xl) > Constants::error) {
        l = new DoshLine(- 50*scale);
        l->setPos(xl, yl);
    } else if (xb > xl and qAbs(xb - xl) > Constants::error) {
        l = new DoshLine(50*scale);
        l->setPos(xl, yl);
    } else {
        l = new DoshLine(50*scale);
        l->setPos(xl - 25 * scale * qCos(alg), yl + 25 * scale * qSin(alg));
    }
    l->setRotation(alg);
    scene->addItem(l);

    pointA = new Point();
    pointA->setPos(xa, ya);
    scene->addItem(pointA);

    pointB = new Point();
    pointB->setPos(xb, yb);
    scene->addItem(pointB);

    ABC = new Polygon(_xc2, _yc2, l2*scale);
    ABC->setPos(xa, ya);
    ABC->setRotation(fi2g);
    scene->addItem(ABC);

    pointC = new Point();
    pointC->setPos(xc, yc);
    scene->addItem(pointC);

    textO1 = new Text(_font, QString("O1"));
    textO1->setPos(xo1 - 3 / scale * textO1->getHorizontalAdvance(), yo1 + 3 / scale * 0.5 * textO1->getHeight());
    textO1->setScale(3/scale);
    scene->addItem(textO1);

    textA = new Text(_font, QString("A"));
    textA->setPos(xa - 3 / scale * textA->getHorizontalAdvance(), ya);
    textA->setScale(3/scale);
    scene->addItem(textA);

    textB = new Text(_font, QString("B"));
    textB->setPos(xb + 3 / scale * textB->getHorizontalAdvance(), yb);
    textB->setScale(3 / scale);
    scene->addItem(textB);

    textC = new Text(_font, QString("C"));
    textC->setPos(xc - 3 / scale * textC->getHorizontalAdvance(), yc);
    textC->setScale(3 / scale);
    scene->addItem(textC);

    textL = new Text(_font, QString("L"));
    textL->setPos(xl + 3 / scale * textL->getHorizontalAdvance(), yl + 1 / scale * textL->getHeight());
    textL->setScale(3/scale);
    scene->addItem(textL);

    qDebug() << "scene->itemsBoundingRect() = " << scene->itemsBoundingRect() << Qt::endl;

    rect = new RectScene(scene->itemsBoundingRect());
    scene->addItem(rect);

    qDebug() << "scene->itemsBoundingRect() = " << scene->itemsBoundingRect() << Qt::endl;
    this->fitInView(scene->itemsBoundingRect(), Qt::KeepAspectRatio);
    setAlignment(Qt::AlignCenter);

    timer = new QTimer(this);
}

void Mechanism_1::setSpeedForPointO1(double _vxo1, double _vyo1, double _vo1)
{
    pointO1->setVx(_vxo1);
    pointO1->setVy(_vyo1);
    pointO1->setV(_vo1);
}

void Mechanism_1::setAccelForPointO1(double _axo1, double _ayo1, double _ao1)
{
    pointO1->setAx(_axo1);
    pointO1->setAy(_ayo1);
    pointO1->setA(_ao1);
}

void Mechanism_1::setSpeedForPointA(double _vxa, double _vya, double _va)
{
    pointA->setVx(_vxa);
    pointA->setVy(_vya);
    pointA->setV(_va);
}

void Mechanism_1::setAccelForPointA(double _axa, double _aya, double _aa)
{
    pointA->setAx(_axa);
    pointA->setAy(_aya);
    pointA->setA(_aa);
}

void Mechanism_1::setSpeedForPointB(double _vxb, double _vyb, double _vb)
{
    pointB->setVx(_vxb);
    pointB->setVy(_vyb);
    pointB->setV(_vb);
}

void Mechanism_1::setAccelForPointB(double _axb, double _ayb, double _ab)
{
    pointB->setAx(_axb);
    pointB->setAy(_ayb);
    pointB->setA(_ab);
}

void Mechanism_1::setSpeedForPointC(double _vxc, double _vyc, double _vc)
{
    pointC->setVx(_vxc);
    pointC->setVy(_vyc);
    pointC->setV(_vc);
}

void Mechanism_1::setAccelForPointC(double _axc, double _ayc, double _ac)
{
    pointC->setAx(_axc);
    pointC->setAy(_ayc);
    pointC->setA(_ac);
}

void Mechanism_1::setLengthO1A(double _l1)
{
    double _l2 = ABC->getl();
    scaling_window(_l1, _l2 / scale);
    O1A->setl(_l1*scale);
}

void Mechanism_1::setLengthAB(double _l2)
{
    double _l1 = O1A->getl();
    scaling_window(_l1 / scale, _l2);
    ABC->setl(_l2*scale);
}

void Mechanism_1::setRamka(double _xmin, double _ymin, double _xmax, double _ymax)
{
    xmin = _xmin*scale;
    ymin = _ymin*scale;
    xmax = _xmax*scale;
    ymax = _ymax*scale;
}

void Mechanism_1::setalg(double _alg)
{
    alg = -_alg;
    B->setRotation(alg);
    l->setRotation(alg);
}

void Mechanism_1::setPointL(double _xl, double _yl)
{
    xl = _xl*scale;
    yl = -_yl*scale;
    L->setPos(xl, yl);
    if ( xb < xl and qAbs(xb - xl) > Constants::error) {
        l->setl(-50*scale);
        l->setPos(xl, yl);
    } else if (xb > xl and qAbs(xb - xl) > Constants::error) {
        l->setl(50 * scale);
        l->setPos(xl, yl);
    } else {
        l->setl(50 * scale);
        l->setPos(xl - 25 * scale * qCos(alg), yl + 25 * scale * qSin(alg));
    }
    textL->setPos(xl + 3 / scale * textL->getHorizontalAdvance(), yl + 1 / scale * textL->getHeight());
    textL->setScale(3 / scale);
}

void Mechanism_1::setPointC(double _xc2, double _yc2)
{
    ABC->setPointC(_xc2*scale, _yc2*scale);
}

void Mechanism_1::change_position(double _xa, double _ya, double _xb, double _yb, double _xc, double _yc,
                                  double _fi1g, double _fi2g,
                                  double _xo1, double _yo1)
{
    xa = _xa*scale;
    ya = - _ya*scale;
    xb = _xb*scale;
    yb = - _yb*scale;
    xo1 = _xo1*scale;
    yo1 = - _yo1*scale;
    xc = _xc*scale;
    yc = -_yc*scale;

    fi1g = - _fi1g;
    fi2g = - _fi2g;

    Ox->setPos(xo1, yo1);
    Oy->setPos(xo1, yo1);
    textX->setPos(xo1 + Ox->getl() - 3 * 0.5 / scale * textX->getHorizontalAdvance(), yo1 + 2 / scale * textX->getHeight());
    textY->setPos(xo1 - 6 / scale * textY->getHorizontalAdvance(), yo1 - Oy->getl() + 3 * 0.5 / scale * textY->getHeight());

    O1->setPos(xo1, yo1);
    pointO1->setPos(xo1, yo1);
    textO1->setPos(xo1 - 3 / scale * textO1->getHorizontalAdvance(), yo1 + 3 / scale * 0.5 / textO1->getHeight());

    O1A->setPos(xo1, yo1);
    O1A->setRotation(fi1g);
    A->setPos(xa, ya);
    pointA->setPos(xa, ya);
    textA->setPos(xa - 3 / scale * textA->getHorizontalAdvance(), ya);

    B->setPos(xb, yb);
    B->setRotation(alg);
    pointB->setPos(xb, yb);
    textB->setPos(xb + 3 / scale * textB->getHorizontalAdvance(), yb);

    ABC->setPos(xa, ya);
    ABC->setRotation(fi2g);
    pointC->setPos(xc, yc);
    textC->setPos(xc - 3 / scale * textC->getHorizontalAdvance(), yc);

    control_Rect();
}

void Mechanism_1::change_rect()
{
    if ( xb < xl and qAbs(xb - xl) > Constants::error) {
        l->setl(-50*scale);
        l->setPos(xl, yl);
    } else if (xb > xl and qAbs(xb - xl) > Constants::error) {
        l->setl(50*scale);
        l->setPos(xl, yl);
    } else {
        l->setl(50*scale);
        l->setPos(xl - 25 * scale * qCos(alg), yl + 25 * scale * qSin(alg));
    }
    scene->removeItem(rect);
    rect->setRect(scene->itemsBoundingRect());
    scene->addItem(rect);
}

void Mechanism_1::changeSpeedStatusO1(Constants::SpeedStatus status)
{
    pointO1->setSpeedStatus(status);
    scene->update();
}

void Mechanism_1::changeSpeedStatusA(Constants::SpeedStatus status)
{
    pointA->setSpeedStatus(status);
    scene->update();
}

void Mechanism_1::changeSpeedStatusB(Constants::SpeedStatus status)
{
    pointB->setSpeedStatus(status);    
    scene->update();
}

void Mechanism_1::changeSpeedStatusC(Constants::SpeedStatus status)
{
    pointC->setSpeedStatus(status);
    scene->update();
}

void Mechanism_1::changeAccelStatusO1(Constants::AccelStatus status)
{
    pointO1->setAccelStatus(status);
    scene->update();
}

void Mechanism_1::changeAccelStatusA(Constants::AccelStatus status)
{
    pointA->setAccelStatus(status);
    scene->update();
}

void Mechanism_1::changeAccelStatusB(Constants::AccelStatus status)
{
    pointB->setAccelStatus(status);
    scene->update();
}

void Mechanism_1::changeAccelStatusC(Constants::AccelStatus status)
{
    pointC->setAccelStatus(status);
    scene->update();
}

Constants::SpeedStatus Mechanism_1::getCurrentSpeedStatusO1()
{
    return pointO1->getSpeedStatus();
}

Constants::SpeedStatus Mechanism_1::getCurrentSpeedStatusA()
{
    return pointA->getSpeedStatus();
}

Constants::SpeedStatus Mechanism_1::getCurrentSpeedStatusB()
{
    return pointB->getSpeedStatus();
}

Constants::SpeedStatus Mechanism_1::getCurrentSpeedStatusC()
{
    return pointC->getSpeedStatus();
}

Constants::AccelStatus Mechanism_1::getCurrentAccelStatusO1()
{
    return pointO1->getAccelStatus();
}

Constants::AccelStatus Mechanism_1::getCurrentAccelStatusA()
{
    return pointA->getAccelStatus();
}

Constants::AccelStatus Mechanism_1::getCurrentAccelStatusB()
{
    return pointB->getAccelStatus();
}

Constants::AccelStatus Mechanism_1::getCurrentAccelStatusC()
{
    return pointC->getAccelStatus();
}

double Mechanism_1::getLengthO1A()
{
    return O1A->getl() / scale;
}

double Mechanism_1::getLengthAB()
{
    return ABC->getl() / scale;
}

double Mechanism_1::getXc2()
{
    return ABC->getXc2() / scale;
}

double Mechanism_1::getYc2()
{
    return ABC->getYc2() / scale;
}

double Mechanism_1::getVxo1()
{
    return pointO1->getVx();
}

double Mechanism_1::getVyo1()
{
    return pointO1->getVy();
}

double Mechanism_1::getAxo1()
{
    return pointO1->getAx();
}

double Mechanism_1::getAyo1()
{
    return pointO1->getAy();
}

QColor *Mechanism_1::getColorO1()
{
    QColor* colors = new QColor[6];
    colors[0] = pointO1->getColorVx();
    colors[1] = pointO1->getColorVy();
    colors[2] = pointO1->getColorV();
    colors[3] = pointO1->getColorAx();
    colors[4] = pointO1->getColorAy();
    colors[5] = pointO1->getColorA();

    return colors;
}

QColor *Mechanism_1::getColorA()
{
    QColor* colors = new QColor[6];
    colors[0] = pointA->getColorVx();
    colors[1] = pointA->getColorVy();
    colors[2] = pointA->getColorV();
    colors[3] = pointA->getColorAx();
    colors[4] = pointA->getColorAy();
    colors[5] = pointA->getColorA();

    return colors;
}

QColor *Mechanism_1::getColorB()
{
    QColor* colors = new QColor[6];
    colors[0] = pointB->getColorVx();
    colors[1] = pointB->getColorVy();
    colors[2] = pointB->getColorV();
    colors[3] = pointB->getColorAx();
    colors[4] = pointB->getColorAy();
    colors[5] = pointB->getColorA();

    return colors;
}

QColor *Mechanism_1::getColorC()
{
    QColor* colors = new QColor[6];
    colors[0] = pointC->getColorVx();
    colors[1] = pointC->getColorVy();
    colors[2] = pointC->getColorV();
    colors[3] = pointC->getColorAx();
    colors[4] = pointC->getColorAy();
    colors[5] = pointC->getColorA();

    return colors;
}

void Mechanism_1::scaling_window(double _l1, double _l2)
{
    double min;
    (_l1 >= _l2) ? min = _l2 : min = _l1;
    qDebug() << "min = " << min << Qt::endl;
    scale = 240*0.2 / min;
}

void Mechanism_1::control_Rect()
{
    QRectF currentRect = scene->itemsBoundingRect();
    if (currentRect.x() < rect->getRectX())
        rect->setRectX(currentRect.x());
    if (currentRect.y() < rect->getRectY())
        rect->setRectY(currentRect.y());
    if (currentRect.width() > rect->getRectWidth())
        rect->setRectWidth(currentRect.width());
    if (currentRect.height() > rect->getRectHeight())
        rect->setRectHeight(currentRect.height());
    this->fitInView(scene->itemsBoundingRect(), Qt::KeepAspectRatio);
}

void Mechanism_1::_stop_timer()
{
    timer->stop();
}

void Mechanism_1::_start_timer()
{
    timer->start(1000 / 45);
}
