#include "image_of_slider_crank_linkage.h"
#include "parts.h"
#include <QTimer>
#include <QDebug>

Image_of_slider_crank_linkage::Image_of_slider_crank_linkage(QWidget *parent) : QGraphicsView(parent)
{
    scene = new Scene();
    this->setScene(scene);

    image = new Picture;
    scene->addItem(image);

    QRectF rect = image->getRectF();
    this->resize(rect.width(), rect.height());
    this->setMinimumSize(rect.width(), rect.height());
    this->setRenderHint(QPainter::Antialiasing);    // Устанавливаем сглаживание
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // Отключаем скроллбар по вертикали
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // Отключаем скроллбар по горизонтали
    scene->setSceneRect(rect.x(), rect.y(), rect.width(), rect.height());   // Устанавливаем размеры графической сцены
    QRect Rect(-150, -150, 300, 300);
    scene->addRect(Rect);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Image_of_slider_crank_linkage::_changes);
    connect(timer, &QTimer::timeout, scene, &Scene::advance);
    timer->start(1000/30);
}

void Image_of_slider_crank_linkage::setImageO1A(double x, double y)
{
    image->setO1A(x, y);
}

void Image_of_slider_crank_linkage::setImageAB(double x, double y)
{
    image->setAB(x, y);
}

void Image_of_slider_crank_linkage::setImagefi1(double angle)
{
    image->setfi1(angle);
}

void Image_of_slider_crank_linkage::setImagefi2(double angle)
{
    image->setfi2(angle);
}

void Image_of_slider_crank_linkage::setImageal(double angle)
{
    image->setal(angle);
}

void Image_of_slider_crank_linkage::setImageRectF(double x, double y, double width, double height)
{
    image->setRectF(x, y, width, height);
}

double Image_of_slider_crank_linkage::getImageO1A()
{
    return image->getO1A();
}

double Image_of_slider_crank_linkage::getImageAB()
{
    return image->getAB();
}

double Image_of_slider_crank_linkage::getImagefi1()
{
    return image->getfi1();
}

double Image_of_slider_crank_linkage::getImagefi2()
{
    return image->getfi2();
}

double Image_of_slider_crank_linkage::getImageal()
{
    return image->getal();
}

QRectF Image_of_slider_crank_linkage::getImageRectF()
{
    return image->getRectF();
}

void Image_of_slider_crank_linkage::_changes()
{
    qDebug() << "Were here" << Qt::endl;
    update();
}

//void Image_of_slider_crank_linkage::_change_fi1(double fi)
//{
//    image->fi1 = fi;
//    image->_fi1_changed();
//}

//void Image_of_slider_crank_linkage::_change_fi2(double fi)
//{
//    image->fi2 = fi;
//    image->_fi2_changed();
//}

//void Image_of_slider_crank_linkage::_fi_changed()
//{
//    image->fi1++;


//    qDebug() << "fi1 = " << image->fi1 << ", fi2 = " << image->fi2 << Qt::endl;
//}
