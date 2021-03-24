#ifndef IMAGE_OF_SLIDER_CRANK_LINKAGE_H
#define IMAGE_OF_SLIDER_CRANK_LINKAGE_H

#include <QGraphicsView>
#include <QWidget>

QT_BEGIN_NAMESPACE
class Scene;
class Picture;
class Slider_crank_linkage;
QT_END_NAMESPACE

class Image_of_slider_crank_linkage : public QGraphicsView
{
    Q_OBJECT
public:
    explicit Image_of_slider_crank_linkage(QWidget *parent = nullptr);

    Scene* scene;
    QTimer* timer;
private:
    Picture* image;
public:
    void setImageO1A(double x, double y);
    void setImageAB(double x, double y);
    void setImagefi1(double angle);
    void setImagefi2(double angle);
    void setImageal(double angle);
    void setImageRectF(double x, double y, double width, double height);

    double getImageO1A();
    double getImageAB();
    double getImagefi1();
    double getImagefi2();
    double getImageal();
    QRectF getImageRectF();
public slots:
    void _changes();

    //friend Slider_crank_linkage;
};

#endif // IMAGE_OF_SLIDER_CRANK_LINKAGE_H
