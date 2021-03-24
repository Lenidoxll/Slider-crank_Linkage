#ifndef MECHANISM_2_H
#define MECHANISM_2_H

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

class Mechanism_2 : public QGraphicsView
{
    Q_OBJECT
public:
    Mechanism_2(QFont _font, double l1, double l2, double l3,
                double _xa, double _ya, double _xb, double _yb, double _xo2, double _yo2,
                double _xc = 0, double _yc = 0, double _xc2 = 0, double _yc2 = 0,
                double fi1 = 0, double fi2 = 0, double fi3 = 0,                         //отсутствие углов считается осознанным приравниванием их к нулю
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
    void setSpeedForPointO2(double _vxo2 = 0, double _vyo2 = 0, double _vo2 = 0);
    void setAccelForPointO2(double _axo2 = 0, double _ayo2 = 0, double _ao2 = 0);
    void setLengthO1A(double _l1 = 0);
    void setLengthAB(double _l2 = 0);
    void setLengthBO2(double _l3 = 0);
    void setRamka(double _xmin = 0, double _ymin = 0, double _xmax = 0, double _ymax = 0);
    void setPointO2(double _xo2, double _yo2);
    void setPointC(double _xc2, double _yc2);
    void setAngularSpeeds(double _om1, double _om2, double _om3);
    void setAngularAccels(double _ep1, double _ep2, double _ep3);
    void setOrientation(Constants::orientation_l _k) { k = _k; }
    void change_position(double _xa, double _ya, double _xb, double _yb, double _xc, double _yc,
                         double _fi1g, double _fi2g, double _fi3g, double _xo1 = 0, double _yo1 = 0);
    void change_rect();
    void incorrect_datas();
    void changeSpeedStatusO1(Constants::SpeedStatus status);
    void changeSpeedStatusA(Constants::SpeedStatus status);
    void changeSpeedStatusB(Constants::SpeedStatus status);
    void changeSpeedStatusC(Constants::SpeedStatus status);
    void changeSpeedStatusO2(Constants::SpeedStatus status);
    void changeAccelStatusO1(Constants::AccelStatus status);
    void changeAccelStatusA(Constants::AccelStatus status);
    void changeAccelStatusB(Constants::AccelStatus status);
    void changeAccelStatusC(Constants::AccelStatus status);
    void changeAccelStatusO2(Constants::AccelStatus status);
    Constants::SpeedStatus getCurrentSpeedStatusO1();
    Constants::SpeedStatus getCurrentSpeedStatusA();
    Constants::SpeedStatus getCurrentSpeedStatusB();
    Constants::SpeedStatus getCurrentSpeedStatusC();
    Constants::SpeedStatus getCurrentSpeedStatusO2();
    Constants::AccelStatus getCurrentAccelStatusO1();
    Constants::AccelStatus getCurrentAccelStatusA();
    Constants::AccelStatus getCurrentAccelStatusB();
    Constants::AccelStatus getCurrentAccelStatusC();
    Constants::AccelStatus getCurrentAccelStatusO2();
    Constants::Status_life getStatusLife();
    double getLengthO1A();
    double getLengthAB();
    double getLengthBO2();
    double getfi1() { return fi1g; }
    double getXc2();
    double getYc2();
    double getVxo1();
    double getVyo1();
    double getAxo1();
    double getAyo1();
    double getXO1() {return xo1;}
    double getYO1() {return yo1;}
    double getXA() {return xa;}
    double getYA() {return ya;}
    double getXB() {return xb;}
    double getYB() {return yb;}
    double getXC() {return xc;}
    double getYC() {return yc;}
    double getXO2() {return xo2;}
    double getYO2() {return yo2;}
    double getOm1() {return om1;}
    double getEp1() {return ep1;}
    double getVO1x();
    double getVO1y();
    double getAO1x();
    double getAO1y();
    QColor* getColorO1();
    QColor* getColorA();
    QColor* getColorB();
    QColor* getColorC();
    QColor* getColorO2();
    Constants::orientation_l getOrientation() { return k;}

    Scene *scene;
    QTimer *timer;

private:    
    Hinge *O1, *O2;
    FixedHinge *A, *B;
    Crank *O1A, *BO2;
    Arrow *Ox, *Oy;
    Point *pointO1, *pointA, *pointB, *pointC, *pointO2;
    Polygon *ABC;
    Text *textO1, *textA, *textB, *textC, *textO2, *textX, *textY;
    double fi1g, fi2g, fi3g;
    double om1, om2, om3;
    double ep1, ep2, ep3;
    double xmax, xmin, ymax, ymin;
    double xo1, yo1, xa, ya, xb, yb, xo2, yo2, xc, yc;
    RectScene *rect;
    Constants::Status_life statusLife = Constants::alive;
    Constants::orientation_l k = Constants::left;

    void scaling_window(double l1, double l2, double l3);
    void control_Rect();

    double scale;

public slots:
    void _stop_timer();
    void _start_timer();
};

#endif // MECHANISM_2_H
