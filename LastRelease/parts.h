#ifndef PARTS_H
#define PARTS_H

#include <QGraphicsObject>
#include <QGraphicsScene>
#include <QObject>
#include <QPainter>
#include "_constants.h"

QT_BEGIN_NAMESPACE
class Text;
class Image_of_slider_crank_linkage;

QT_END_NAMESPACE

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Неподвижный шарнир~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
class Hinge : public QGraphicsObject
{
    Q_OBJECT
public:
    explicit Hinge();
private:
    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    double scale = 0.2;
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Подвижный шарнир~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
class FixedHinge : public QGraphicsObject
{
    Q_OBJECT
public:
    explicit FixedHinge();
private:
    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    double scale = 0.2;
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Ползун~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
class Slider : public QGraphicsObject
{
    Q_OBJECT
public:
    Slider();
private:
    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    double scale = 0.2;
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Кривошип/шатун~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
class Crank : public QGraphicsObject
{
    Q_OBJECT
public:
    explicit Crank(double L);
    void setl(double L);
    double getl() { return l;}

private:
    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    double l;
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Пунктирная прямая~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
class DoshLine : public QGraphicsObject
{
    Q_OBJECT
public:
    explicit DoshLine(double L);
    void setl(double L);
    inline double getl() { return l; }
private:
    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    double l;
    QRectF rect;
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Стрелка~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
class Arrow : public QGraphicsObject
{
    Q_OBJECT
public:
    explicit Arrow(double L, double Al = 15);
    inline void setl(double L);
    inline void setColor(QColor Color) { color = Color; }
    inline double getl() { return l; }

private:
    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    double l, al;
    QColor color = QColor(Qt::black);
    QRectF rect;
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Точка~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
class Point : public QGraphicsObject
{
    Q_OBJECT
public:
    explicit Point(double _vx = 0, double _vy = 0, double _v = 0, double _ax = 0, double _ay = 0, double _a = 0);
    inline void setVx(double Vx) { vx = Vx; }
    inline void setVy(double Vy) { vy = Vy; }
    inline void setV(double V) { v = V; }
    inline void setAx(double Ax) { ax = Ax; }
    inline void setAy(double Ay) { ay = Ay; }
    inline void setA(double A) { a = A; }

    inline double getVx() { return vx; }
    inline double getVy() { return vy; }
    inline double getV() { return v; }
    inline double getAx() { return ax; }
    inline double getAy() { return ay; }
    inline double getA() { return a; }

    inline QColor getColorVx() { return colorVx; }
    inline QColor getColorVy() { return colorVy; }
    inline QColor getColorV() { return colorV; }
    inline QColor getColorAx() { return colorAx; }
    inline QColor getColorAy() { return colorAy; }
    inline QColor getColorA() { return colorA; }


    void setSpeedStatus(Constants::SpeedStatus status);
    void setAccelStatus(Constants::AccelStatus status) { currentAccelStatus = status; }
    inline Constants::SpeedStatus getSpeedStatus() { return currentSpeedStatus; }
    inline Constants::AccelStatus getAccelStatus() { return currentAccelStatus; }

protected:
    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    double vx, vy, v, ax, ay, a;
    double al;
    Constants::SpeedStatus currentSpeedStatus = Constants::SHOWSPEED;
    Constants::AccelStatus currentAccelStatus = Constants::SHOWACCEL;

    //Arrow *arrowVx, *arrowVy, *arrowV, *arrowAx, *arrowAy, *arrowA;
    QColor colorVx = QColor(255, 17, 0);       //возможно, объединит в какую-нибудь единую систему?
    QColor colorVy = QColor(255, 157, 0);
    QColor colorV = QColor(136, 255, 0);
    QColor colorAx = QColor(34, 199, 245);
    QColor colorAy = QColor(0, 115, 255);
    QColor colorA = QColor(102, 0, 255);

    QRectF rect;
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Особая точка~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
class SpecialPoint : public Point
{
    Q_OBJECT
public:
    explicit SpecialPoint(double _xc2 = 0, double _yc2 = 0, double _l2 = 0);
    void setPointC(double _xc2, double _yc2)
    {
        xc2 = _xc2;
        yc2 = -_yc2;
        poly.putPoints(2, 1, xc2, yc2);

        if (xc2 * l >= 0)
            (qAbs(xc2) >= qAbs(l)) ? rect = QRectF(0, 0, xc2, yc2) : rect = QRectF(0, 0, l, yc2);
        else
            (xc2 >= 0) ? rect = QRectF(xc2, 0, -(xc2 + qAbs(l)), yc2) : rect = QRectF(xc2, 0, qAbs(xc2) + l, yc2);
    }
    void setl(double _l) {
        l = _l;
        poly.putPoints(1, 1, _l, 0);

        if (xc2 * l >= 0)
            (qAbs(xc2) >= qAbs(l)) ? rect = QRectF(0, 0, xc2, yc2) : rect = QRectF(0, 0, l, yc2);
        else
            (xc2 >= 0) ? rect = QRectF(xc2, 0, -(xc2 + qAbs(l)), yc2) : rect = QRectF(xc2, 0, qAbs(xc2) + l, yc2);
    }
    void setPolygon(double _xc2, double _yc2, double _l);
    inline double getl() { return l; }
    inline double getXc2() { return xc2; }
    inline double getYc2() { return yc2; }

private:
    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    double xc2, yc2, l;
    QPolygon poly;
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Полигон треугольник~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
class Polygon : public QGraphicsObject
{
    Q_OBJECT
public:
    explicit Polygon(double _xc2 = 0, double _yc2 = 0, double _l2 = 0);
    void setPointC(double _xc2, double _yc2)
    {
        xc2 = _xc2;
        yc2 = -_yc2;
        poly.putPoints(2, 1, xc2, yc2);

        if (xc2 * l >= 0)
            (qAbs(xc2) >= qAbs(l)) ? rect = QRectF(0, 0, xc2, yc2) : rect = QRectF(0, 0, l, yc2);
        else
            (xc2 >= 0) ? rect = QRectF(xc2, 0, -(xc2 + qAbs(l)), yc2) : rect = QRectF(xc2, 0, qAbs(xc2) + l, yc2);
    }
    void setl(double _l) {
        l = _l;
        poly.putPoints(1, 1, _l, 0);

        if (xc2 * l >= 0)
            (qAbs(xc2) >= qAbs(l)) ? rect = QRectF(0, 0, xc2, yc2) : rect = QRectF(0, 0, l, yc2);
        else
            (xc2 >= 0) ? rect = QRectF(xc2, 0, -(xc2 + qAbs(l)), yc2) : rect = QRectF(xc2, 0, qAbs(xc2) + l, yc2);
    }
    void setPolygon(double _xc2, double _yc2, double _l);
    inline double getl() { return l; }
    inline double getXc2() { return xc2; }
    inline double getYc2() { return yc2; }

private:
    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    QRectF rect;
    double xc2, yc2, l;
    QPolygon poly;
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Текст~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
class Text : public QGraphicsObject
{
    Q_OBJECT
public:
    explicit Text(QFont Font, QString Str = nullptr);
    void setText(QString newstr);

    inline QString getText() { return  str; }
    inline int getHorizontalAdvance() { return fm->horizontalAdvance(str); }
    inline int getHeight() { return fm->height(); }

private:
    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    QString str;
    QFont font;
    QFontMetrics *fm;
    double scale = 0.2;
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Размер сцены~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
class RectScene : public QGraphicsObject
{
    Q_OBJECT
public:
    explicit RectScene(double _x, double _y, double _width, double _height);
    explicit RectScene(QRectF currentRect);
    void setRect(double _x, double _y, double _width, double _height);
    void setRect(QRectF currentRect);
    void setRectX(double x);
    void setRectY(double y);
    void setRectWidth(double width);
    void setRectHeight(double Height);
    qreal getRectX();
    qreal getRectY();
    qreal getRectWidth();
    qreal getRectHeight();

private:
    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    QRectF rect;
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Картинка проба~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
class Picture : public QGraphicsObject
{
    Q_OBJECT
public:
    explicit Picture();

    void setO1A(double x, double y);
    void setAB(double x, double y);
    void setfi1(double angle);
    void setfi2(double angle);
    void setal(double angle);
    void setRectF(double x, double y, double width, double height);

    double getO1A();
    double getAB();
    double getfi1();
    double getfi2();
    double getal();
    QRectF getRectF();

private:
    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    QLine O1A, AB;
    QRect A, B, slider;
    double fi1 = 30, fi2 = -40, al = 50;

    QRectF rect;
public slots:
    void _fi1_changed();
    void _fi2_changed();
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Сцена~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Scene(QObject *parent = nullptr);
    ~Scene();
};

#endif // PARTS_H
