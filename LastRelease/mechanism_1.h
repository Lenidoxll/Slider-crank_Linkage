#ifndef MECHANISM_1_H
#define MECHANISM_1_H

#include <QGraphicsView>
#include <QWidget>
#include "_constants.h"

QT_BEGIN_NAMESPACE
class Scene;
class Hinge;
class FixedHinge;
class Slider;
class Crank;
class DoshLine;
class Arrow;
class QLine;
class Text;
class Point;
class Polygon;
class SpecialPoint;
class RectScene;
QT_END_NAMESPACE

class Mechanism_1 : public QGraphicsView
{
    Q_OBJECT
public:
    explicit Mechanism_1(QFont _font, double l1, double l2,
                         double _xa, double _ya, double _xb, double _yb, double _xl, double _yl,
                         double _xc = 0, double _yc = 0, double _xc2 = 0, double _yc2 = 0,
                         double fi1 = 0, double fi2 = 0, double al = 0,                         //отсутствие углов считается осознанным приравниванием их к нулю
                         double _xmin = 0, double _ymin = 0, double _xmax = 0, double _ymax = 0,
                         double _xo1 = 0, double _yo1 = 0,
                         QWidget *parent = nullptr);
    void setSpeedForPointO1(double _vxo1 = 0, double _vyo1 = 0, double _vo1 = 0);
    void setAccelForPointO1(double _axo1 = 0, double _ayo1 = 0, double _ao1 = 0);
    void setSpeedForPointA(double _vxa = 0, double _vya = 0, double _va = 0);
    void setAccelForPointA(double _axa = 0, double _aya = 0, double _aa = 0);
    void setSpeedForPointB(double _vxb = 0, double _vyb = 0, double _vb = 0);
    void setAccelForPointB(double _axb = 0, double _ayb = 0, double _ab = 0);
    void setSpeedForPointC(double _vxc = 0, double _vyc = 0, double _vc = 0);
    void setAccelForPointC(double _axc = 0, double _ayc = 0, double _ac = 0);
    void setLengthO1A(double _l1 = 0);
    void setLengthAB(double _l2 = 0);
    void setRamka(double _xmin = 0, double _ymin = 0, double _xmax = 0, double _ymax = 0);
    void setalg(double _alg);
    void setPointL(double _xl, double _yl);
    void setPointC(double _xc2, double _yc2);
    void change_position(double _xa, double _ya, double _xb, double _yb, double _xc, double _yc,
                         double _fi1g, double _fi2g, double _xo1 = 0, double _yo1 = 0);
    void change_rect();
    void changeSpeedStatusO1(Constants::SpeedStatus status);
    void changeSpeedStatusA(Constants::SpeedStatus status);
    void changeSpeedStatusB(Constants::SpeedStatus status);
    void changeSpeedStatusC(Constants::SpeedStatus status);
    void changeAccelStatusO1(Constants::AccelStatus status);
    void changeAccelStatusA(Constants::AccelStatus status);
    void changeAccelStatusB(Constants::AccelStatus status);
    void changeAccelStatusC(Constants::AccelStatus status);
    Constants::SpeedStatus getCurrentSpeedStatusO1();
    Constants::SpeedStatus getCurrentSpeedStatusA();
    Constants::SpeedStatus getCurrentSpeedStatusB();
    Constants::SpeedStatus getCurrentSpeedStatusC();
    Constants::AccelStatus getCurrentAccelStatusO1();
    Constants::AccelStatus getCurrentAccelStatusA();
    Constants::AccelStatus getCurrentAccelStatusB();
    Constants::AccelStatus getCurrentAccelStatusC();

    double getLengthO1A();
    double getLengthAB();
    double getfi1() { return fi1g; }
    double getal() {return alg; }
    double getXc2();
    double getYc2();
    double getVxo1();
    double getVyo1();
    double getAxo1();
    double getAyo1();
    QColor* getColorO1();
    QColor* getColorA();
    QColor* getColorB();
    QColor* getColorC();


    Scene *scene;
    QTimer *timer;

private:
    Hinge* O1;
    FixedHinge *A, *L;
    Slider* B;
    Crank *O1A;
    DoshLine *l;
    Arrow *Ox, *Oy;
    Point *pointO1, *pointA, *pointB, *pointC;
    Polygon *ABC;
    Text *textO1, *textA, *textB, *textC, *textL, *textX, *textY;
    double fi1g, fi2g, alg;
    double xmax, xmin, ymax, ymin;
    double xo1, yo1, xa, ya, xb, yb, xl, yl, xc, yc;
    RectScene *rect;

    void scaling_window(double l1, double l2);
    void control_Rect();
    qreal index;

    double scale; //прости Господи

public slots:
    void _stop_timer();
    void _start_timer();
};

#endif // MECHANISM_1_H


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~МУСОР~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~`//
//    QColor getColorVO1x();
//    QColor getColorVO1y();
//    QColor getColorVO1();
//    QColor getColorAO1x();
//    QColor getColorAO1y();
//    QColor getColorAO1();
//    QColor getColorVAx();
//    QColor getColorVAy();
//    QColor getColorVA1();
//    QColor getColorAAx();
//    QColor getColorAAy();
//    QColor getColorAA1();
//    QColor getColorVBx();
//    QColor getColorVBy();
//    QColor getColorVB1();
//    QColor getColorABx();
//    QColor getColorABy();
//    QColor getColorAB1();
//    QColor getColorVCx();
//    QColor getColorVCy();
//    QColor getColorVC1();
//    QColor getColorACx();
//    QColor getColorACy();
//    QColor getColorAC1();
