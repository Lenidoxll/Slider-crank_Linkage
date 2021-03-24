#include "mechanism_2.h"
#include "parts.h"

#include <QtMath>
#include <QTimer>
#include <QDebug>

Mechanism_2::Mechanism_2(QFont _font, double l1, double l2, double l3,
                         double _xa, double _ya, double _xb, double _yb, double _xo2, double _yo2,
                         double _xc, double _yc, double _xc2, double _yc2,
                         double fi1, double fi2, double fi3,
                         double _xmin, double _ymin, double _xmax, double _ymax,
                         double _xo1, double _yo1, QWidget *parent) : QGraphicsView(parent)
{
    scene = new Scene();
    this->setScene(scene);

    this->setRenderHint(QPainter::Antialiasing);    // Устанавливаем сглаживание
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // Отключаем скроллбар по вертикали
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // Отключаем скроллбар по горизонтали

    scaling_window(l1, l2, l3);

    fi1g = -fi1;
    fi2g = -fi2;
    fi3g = -fi3;

    xo1 = _xo1 * scale;
    yo1 = -_yo1 * scale;
    xa = _xa * scale;
    ya = -_ya * scale;
    xb = _xb * scale;
    yb = -_yb * scale;
    xo2 = _xo2 * scale;
    yo2 = -_yo2 * scale;
    xc = _xc * scale;
    yc = -_yc * scale;

    xmin = _xmin * scale;
    ymin = _ymin * scale;
    xmax = _xmax * scale;
    ymax = _ymax * scale;

    qDebug() << "1. scene->itemsBoundingRect() = " << scene->itemsBoundingRect() << Qt::endl;

    Ox = new Arrow(30);
    scene->addItem(Ox);

    qDebug() << "2. scene->itemsBoundingRect() = " << scene->itemsBoundingRect() << Qt::endl;

    textX = new Text(_font, QString("x"));
    textX->setPos(xo1 + Ox->getl() - 3 * 0.5 / scale * textX->getHorizontalAdvance(), yo1 + 2 / scale * textX->getHeight());
    textX->setScale(3/scale);
    scene->addItem(textX);

    qDebug() << "3. scene->itemsBoundingRect() = " << scene->itemsBoundingRect() << Qt::endl;

    Oy = new Arrow(30);
    Oy->setRotation(-90);
    scene->addItem(Oy);

    qDebug() << "4. scene->itemsBoundingRect() = " << scene->itemsBoundingRect() << Qt::endl;

    textY = new Text(_font, QString("y"));
    textY->setPos(xo1 - 6 / scale * textY->getHorizontalAdvance(), yo1 - Oy->getl() + 3 * 0.5 / scale * textY->getHeight());
    textY->setScale(3/scale);
    scene->addItem(textY);

    qDebug() << "5. scene->itemsBoundingRect() = " << scene->itemsBoundingRect() << Qt::endl;

    O1 = new Hinge();   //неподвижный шарнир O1
    O1->setPos(xo1, yo1);
    scene->addItem(O1);

    qDebug() << "6. scene->itemsBoundingRect() = " << scene->itemsBoundingRect() << Qt::endl;

    O1A = new Crank(l1 * scale);    //звено O1A
    O1A->setPos(xo1, yo1);
    O1A->setRotation(fi1g);
    scene->addItem(O1A);

    qDebug() << "7. scene->itemsBoundingRect() = " << scene->itemsBoundingRect() << Qt::endl;

    pointO1 = new Point();
    pointO1->setPos(xo1, yo1);
    scene->addItem(pointO1);

    qDebug() << "8. scene->itemsBoundingRect() = " << scene->itemsBoundingRect() << Qt::endl;

    A = new FixedHinge();   //шарнир А
    A->setPos(xa, ya);
    scene->addItem(A);

    qDebug() << "9. scene->itemsBoundingRect() = " << scene->itemsBoundingRect() << Qt::endl;


    B = new FixedHinge();    //шарнир В
    B->setPos(xb, yb);
    scene->addItem(B);

    qDebug() << "10. scene->itemsBoundingRect() = " << scene->itemsBoundingRect() << Qt::endl;

    pointA = new Point();
    pointA->setPos(xa, ya);
    scene->addItem(pointA);

    qDebug() << "11. scene->itemsBoundingRect() = " << scene->itemsBoundingRect() << Qt::endl;

    pointB = new Point();
    pointB->setPos(xb, yb);
    scene->addItem(pointB);

    qDebug() << "12. scene->itemsBoundingRect() = " << scene->itemsBoundingRect() << Qt::endl;

    ABC = new Polygon(_xc2 * scale, -_yc2 * scale, l2 * scale);
    ABC->setPos(xa, ya);
    ABC->setRotation(fi2g);
    scene->addItem(ABC);

    qDebug() << "13. scene->itemsBoundingRect() = " << scene->itemsBoundingRect() << Qt::endl;

    O2 = new Hinge();       //неподвижный шарнир O2
    O2->setPos(xo2, yo2);
    scene->addItem(O2);

    qDebug() << "14. scene->itemsBoundingRect() = " << scene->itemsBoundingRect() << Qt::endl;

    BO2 = new Crank(l3 * scale);
    BO2->setPos(xb, yb);
    BO2->setRotation(fi3g);
    scene->addItem(BO2);

    qDebug() << "15. scene->itemsBoundingRect() = " << scene->itemsBoundingRect() << Qt::endl;

    pointO2 = new Point();
    pointO2->setPos(xo2, yo2);
    scene->addItem(pointO2);

    qDebug() << "16. scene->itemsBoundingRect() = " << scene->itemsBoundingRect() << Qt::endl;

    pointC = new Point();
    pointC->setPos(xc, yc);
    scene->addItem(pointC);

    qDebug() << "17. scene->itemsBoundingRect() = " << scene->itemsBoundingRect() << Qt::endl;

    textO1 = new Text(_font, QString("O1"));
    textO1->setPos(xo1 - 3 / scale * textO1->getHorizontalAdvance(), yo1 + 3 / scale * 0.5 * textO1->getHeight());
    textO1->setScale(3/scale);
    scene->addItem(textO1);

    qDebug() << "18. scene->itemsBoundingRect() = " << scene->itemsBoundingRect() << Qt::endl;

    textA = new Text(_font, QString("A"));
    textA->setPos(xa + 3 / scale * textA->getHorizontalAdvance(), ya);
    textA->setScale(3/scale);
    scene->addItem(textA);

    qDebug() << "19. scene->itemsBoundingRect() = " << scene->itemsBoundingRect() << Qt::endl;

    textB = new Text(_font, QString("B"));
    textB->setPos(xb + 3 / scale * textB->getHorizontalAdvance(), yb);
    textB->setScale(3/scale);
    scene->addItem(textB);

    qDebug() << "20. scene->itemsBoundingRect() = " << scene->itemsBoundingRect() << Qt::endl;

    textC = new Text(_font, QString("C"));
    textC->setPos(xc - 3 / scale * textC->getHorizontalAdvance(), yc);
    textC->setScale(3/scale);
    scene->addItem(textC);

    qDebug() << "21. scene->itemsBoundingRect() = " << scene->itemsBoundingRect() << Qt::endl;

    textO2 = new Text(_font, QString("O2"));
    textO2->setPos(xo2 - 3 / scale * textO2->getHorizontalAdvance(), yo2 + 3 / scale * 0.5 * textO2->getHeight());
    textO2->setScale(3/scale);
    scene->addItem(textO2);

    qDebug() << "scene->itemsBoundingRect() = " << scene->itemsBoundingRect() << Qt::endl;

    rect = new RectScene(scene->itemsBoundingRect());
    scene->addItem(rect);

    qDebug() << "scene->itemsBoundingRect() = " << scene->itemsBoundingRect() << Qt::endl;
    this->fitInView(scene->itemsBoundingRect(), Qt::KeepAspectRatio);
    setAlignment(Qt::AlignCenter);

    timer = new QTimer(this);
}

void Mechanism_2::setSpeedForPointO1(double _vxo1, double _vyo1, double _vo1)
{
    pointO1->setVx(_vxo1);
    pointO1->setVy(_vyo1);
    pointO1->setV(_vo1);
}

void Mechanism_2::setAccelForPointO1(double _axo1, double _ayo1, double _ao1)
{
    pointO1->setAx(_axo1);
    pointO1->setAy(_ayo1);
    pointO1->setA(_ao1);
}

void Mechanism_2::setSpeedForPointA(double _vxa, double _vya, double _va)
{
    pointA->setVx(_vxa);
    pointA->setVy(_vya);
    pointA->setV(_va);
}

void Mechanism_2::setAccelForPointA(double _axa, double _aya, double _aa)
{
    pointA->setAx(_axa);
    pointA->setAy(_aya);
    pointA->setA(_aa);
}

void Mechanism_2::setSpeedForPointB(double _vxb, double _vyb, double _vb)
{
    pointB->setVx(_vxb);
    pointB->setVy(_vyb);
    pointB->setV(_vb);
}

void Mechanism_2::setAccelForPointB(double _axb, double _ayb, double _ab)
{
    pointB->setAx(_axb);
    pointB->setAy(_ayb);
    pointB->setA(_ab);
}

void Mechanism_2::setSpeedForPointC(double _vxc, double _vyc, double _vc)
{
    pointC->setVx(_vxc);
    pointC->setVy(_vyc);
    pointC->setV(_vc);
}

void Mechanism_2::setAccelForPointC(double _axc, double _ayc, double _ac)
{
    pointC->setAx(_axc);
    pointC->setAy(_ayc);
    pointC->setA(_ac);
}

void Mechanism_2::setSpeedForPointO2(double _vxo2, double _vyo2, double _vo2)
{
    pointO2->setVx(_vxo2);
    pointO2->setVy(_vyo2);
    pointO2->setV(_vo2);
}

void Mechanism_2::setAccelForPointO2(double _axo2, double _ayo2, double _ao2)
{
    pointO2->setAx(_axo2);
    pointO2->setAy(_ayo2);
    pointO2->setA(_ao2);
}

void Mechanism_2::setLengthO1A(double _l1)
{
    double _l3 = BO2->getl() / scale;
    double _l2 = ABC->getl() / scale;
    scaling_window(_l1, _l2, _l3);
    O1A->setl(_l1*scale);
    BO2->setl(_l3 * scale);
    ABC->setl(_l2*scale);
    qDebug() << "1. scale = " << scale <<Qt::endl;
}

void Mechanism_2::setLengthAB(double _l2)
{
    double _l1 = O1A->getl() / scale;
    double _l3 = BO2->getl() / scale;
    scaling_window(_l1, _l2, _l3);
    O1A->setl(_l1*scale);
    BO2->setl(_l3 * scale);
    ABC->setl(_l2*scale);
    qDebug() << "2. scale = " << scale <<Qt::endl;
}

void Mechanism_2::setLengthBO2(double _l3)
{
    double _l1 = O1A->getl() / scale;
    double _l2 = ABC->getl() / scale;
    scaling_window(_l1, _l2, _l3);
    O1A->setl(_l1*scale);
    BO2->setl(_l3 * scale);
    ABC->setl(_l2*scale);
    qDebug() << "3. scale = " << scale <<Qt::endl;
}

void Mechanism_2::setRamka(double _xmin, double _ymin, double _xmax, double _ymax)
{
    xmin = _xmin*scale;
    ymin = _ymin*scale;
    xmax = _xmax*scale;
    ymax = _ymax*scale;
}

void Mechanism_2::setPointO2(double _xo2, double _yo2)
{
    xo2 = _xo2*scale;
    yo2 = -_yo2*scale;
    pointO2->setPos(xo2, yo2);
    O2->setPos(xo2, yo2);
    textO2->setPos(xo2 - 3 / scale * textO2->getHorizontalAdvance(), yo2 + 3 / scale * 0.5 * textO2->getHeight());

}

void Mechanism_2::setPointC(double _xc2, double _yc2)
{
    ABC->setPointC(_xc2*scale, _yc2*scale);
}

void Mechanism_2::setAngularSpeeds(double _om1, double _om2, double _om3)
{
    om1 = _om1;
    om2 = _om2;
    om3 = _om3;
}

void Mechanism_2::setAngularAccels(double _ep1, double _ep2, double _ep3)
{
    ep1 = _ep1;
    ep2 = _ep2;
    ep3 = _ep3;
}

void Mechanism_2::change_position(double _xa, double _ya, double _xb, double _yb,
                                  double _xc, double _yc, double _fi1g, double _fi2g, double _fi3g,
                                  double _xo1, double _yo1)
{
    if (statusLife == Constants::dead) {
        scene->addItem(Ox);
        scene->addItem(textX);
        scene->addItem(Oy);
        scene->addItem(textY);
        scene->addItem(O1);
        scene->addItem(O1A);
        scene->addItem(pointO1);
        scene->addItem(A);
        scene->addItem(B);
        scene->addItem(pointA);
        scene->addItem(pointB);
        scene->addItem(ABC);
        scene->addItem(O2);
        scene->addItem(BO2);
        scene->addItem(pointO2);
        scene->addItem(pointC);
        scene->addItem(textO1);
        scene->addItem(textA);
        scene->addItem(textB);
        scene->addItem(textC);
        scene->addItem(textO2);
        statusLife = Constants::alive;
    }

    xa = _xa*scale;
    qDebug() << "_xa = " << _xa << ", xa = " << xa << Qt::endl;
    ya = - _ya*scale;
    qDebug() << "_ya = " << _ya << ", ya = " << ya << Qt::endl;
    xb = _xb*scale;
    qDebug() << "_xb = " << _xb << ", xb = " << xb << Qt::endl;
    yb = - _yb*scale;
    qDebug() << "_yb = " << _yb << ", yb = " << yb << Qt::endl;
    xo1 = _xo1*scale;
    qDebug() << "_xo1 = " << _xo1 << ", xo1 = " << xo1 << Qt::endl;
    yo1 = - _yo1*scale;
    qDebug() << "_yo1 = " << _yo1 << ", yo1 = " << yo1 << Qt::endl;
    xc = _xc*scale;
    qDebug() << "_xc = " << _xc << ", xc = " << xc << Qt::endl;
    yc = -_yc*scale;
    qDebug() << "_yc = " << _yc << ", yc = " << yc << Qt::endl;

    fi1g = - _fi1g;
    fi2g = - _fi2g;
    fi3g = - _fi3g;

    Ox->setPos(xo1, yo1);
    Oy->setPos(xo1, yo1);
    textX->setPos(xo1 + Ox->getl() - 3 * 0.5 / scale * textX->getHorizontalAdvance(), yo1 + 2 / scale * textX->getHeight());
    textY->setPos(xo1 - 6 / scale * textY->getHorizontalAdvance(), yo1 - Oy->getl() + 3 * 0.5 / scale * textY->getHeight());

    O1->setPos(xo1, yo1);
    pointO1->setPos(xo1, yo1);
    textO1->setPos(xo1 - 3 / scale * textO1->getHorizontalAdvance(), yo1 + 3 / scale * 0.5 * textO1->getHeight());

    O1A->setPos(xo1, yo1);
    O1A->setRotation(fi1g);
    A->setPos(xa, ya);
    pointA->setPos(xa, ya);
    textA->setPos(xa - 3 / scale * textA->getHorizontalAdvance(), ya);

    B->setPos(xb, yb);
    pointB->setPos(xb, yb);
    textB->setPos(xb + 3 / scale * textB->getHorizontalAdvance(), yb);

    ABC->setPos(xa, ya);
    ABC->setRotation(fi2g);
    pointC->setPos(xc, yc);
    textC->setPos(xc - 3 / scale * textC->getHorizontalAdvance(), yc);

    BO2->setPos(xb, yb);
    BO2->setRotation(fi3g);

    control_Rect();
}

void Mechanism_2::change_rect()
{
    scene->removeItem(rect);
    rect->setRect(scene->itemsBoundingRect());
    scene->addItem(rect);
}

void Mechanism_2::incorrect_datas()
{
    if (statusLife == Constants::alive) {
        scene->removeItem(O1);
        scene->removeItem(O2);
        scene->removeItem(A);
        scene->removeItem(B);
        scene->removeItem(O1A);
        scene->removeItem(BO2);
        scene->removeItem(Ox);
        scene->removeItem(Oy);
        scene->removeItem(pointO1);
        scene->removeItem(pointA);
        scene->removeItem(pointB);
        scene->removeItem(pointC);
        scene->removeItem(pointO2);
        scene->removeItem(ABC);
        scene->removeItem(textX);
        scene->removeItem(textY);
        scene->removeItem(textO1);
        scene->removeItem(textA);
        scene->removeItem(textB);
        scene->removeItem(textC);
        scene->removeItem(textO2);
        rect->setRect(0, 0, 0, 0);
        statusLife = Constants::dead;
    }
}

void Mechanism_2::changeSpeedStatusO1(Constants::SpeedStatus status)
{
    pointO1->setSpeedStatus(status);
    scene->update();
}

void Mechanism_2::changeSpeedStatusA(Constants::SpeedStatus status)
{
    pointA->setSpeedStatus(status);
    scene->update();
}

void Mechanism_2::changeSpeedStatusB(Constants::SpeedStatus status)
{
    pointB->setSpeedStatus(status);
    scene->update();
}

void Mechanism_2::changeSpeedStatusC(Constants::SpeedStatus status)
{
    pointC->setSpeedStatus(status);
    scene->update();
}

void Mechanism_2::changeSpeedStatusO2(Constants::SpeedStatus status)
{
    pointO2->setSpeedStatus(status);
    scene->update();
}

void Mechanism_2::changeAccelStatusO1(Constants::AccelStatus status)
{
    pointO1->setAccelStatus(status);
    scene->update();
}

void Mechanism_2::changeAccelStatusA(Constants::AccelStatus status)
{
    pointA->setAccelStatus(status);
    scene->update();
}

void Mechanism_2::changeAccelStatusB(Constants::AccelStatus status)
{
    pointB->setAccelStatus(status);
    scene->update();
}

void Mechanism_2::changeAccelStatusC(Constants::AccelStatus status)
{
    pointC->setAccelStatus(status);
    scene->update();
}

void Mechanism_2::changeAccelStatusO2(Constants::AccelStatus status)
{
    pointO2->setAccelStatus(status);
    scene->update();
}

Constants::SpeedStatus Mechanism_2::getCurrentSpeedStatusO1()
{
    return pointO1->getSpeedStatus();
}

Constants::SpeedStatus Mechanism_2::getCurrentSpeedStatusA()
{
    return pointA->getSpeedStatus();
}

Constants::SpeedStatus Mechanism_2::getCurrentSpeedStatusB()
{
    return pointB->getSpeedStatus();
}

Constants::SpeedStatus Mechanism_2::getCurrentSpeedStatusC()
{
    return pointC->getSpeedStatus();
}

Constants::SpeedStatus Mechanism_2::getCurrentSpeedStatusO2()
{
    return pointO2->getSpeedStatus();
}

Constants::AccelStatus Mechanism_2::getCurrentAccelStatusO1()
{
    return pointO1->getAccelStatus();
}

Constants::AccelStatus Mechanism_2::getCurrentAccelStatusA()
{
    return pointA->getAccelStatus();
}

Constants::AccelStatus Mechanism_2::getCurrentAccelStatusB()
{
    return pointB->getAccelStatus();
}

Constants::AccelStatus Mechanism_2::getCurrentAccelStatusC()
{
    return pointC->getAccelStatus();
}

Constants::AccelStatus Mechanism_2::getCurrentAccelStatusO2()
{
    return pointO2->getAccelStatus();
}

Constants::Status_life Mechanism_2::getStatusLife()
{
    return statusLife;
}

double Mechanism_2::getLengthO1A()
{
    return O1A->getl() / scale;
}

double Mechanism_2::getLengthAB()
{
    return ABC->getl() / scale;
}

double Mechanism_2::getLengthBO2()
{
    return BO2->getl() / scale;
}

double Mechanism_2::getXc2()
{
    return ABC->getXc2() / scale;
}

double Mechanism_2::getYc2()
{
    return ABC->getYc2() / scale;
}

double Mechanism_2::getVxo1()
{
    return pointO1->getVx();
}

double Mechanism_2::getVyo1()
{
    return pointO1->getVy();
}

double Mechanism_2::getAxo1()
{
    return pointO1->getAx();
}

double Mechanism_2::getAyo1()
{
    return pointO1->getAy();
}

double Mechanism_2::getVO1x()
{
    return pointO1->getVx();
}

double Mechanism_2::getVO1y()
{
    return pointO1->getVy();
}

double Mechanism_2::getAO1x()
{
    return pointO1->getAx();
}

double Mechanism_2::getAO1y()
{
    return pointO1->getAy();
}

QColor *Mechanism_2::getColorO1()
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

QColor *Mechanism_2::getColorA()
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

QColor *Mechanism_2::getColorB()
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

QColor *Mechanism_2::getColorC()
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

QColor *Mechanism_2::getColorO2()
{
    QColor* colors = new QColor[6];
    colors[0] = pointO2->getColorVx();
    colors[1] = pointO2->getColorVy();
    colors[2] = pointO2->getColorV();
    colors[3] = pointO2->getColorAx();
    colors[4] = pointO2->getColorAy();
    colors[5] = pointO2->getColorA();

    return colors;
}

void Mechanism_2::scaling_window(double _l1, double _l2, double _l3)
{
    double min = _l1;
    double arr[3];
    arr[0] = _l1;
    arr[1] = _l2;
    arr[2] = _l3;
    for (int i = 0; i < 3; i++) {
        if ( i == 0 )
            min = arr[i];
        else {
            if (arr[i] < min)
                min = arr[i];
        }
    }

    qDebug() << "min = " << min << Qt::endl;
    if (qAbs(min) < Constants::error)
        scale = 0;
    else
        scale = 240*0.2 / min;
}

void Mechanism_2::control_Rect()
{
    qDebug() << "now  scene->itemsBoundingRect() = " << scene->itemsBoundingRect() << Qt::endl;
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
    qDebug() << " and now scene->itemsBoundingRect() = " << scene->itemsBoundingRect() << Qt::endl;
}

void Mechanism_2::_stop_timer()
{
    timer->stop();
}

void Mechanism_2::_start_timer()
{
    timer->start(1000 / 45);
}
