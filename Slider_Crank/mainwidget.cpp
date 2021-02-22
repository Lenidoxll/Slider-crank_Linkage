#include "mainwidget.h"
#include <QDebug>

MainWidget::MainWidget(QWidget *parent) : QGraphicsView(parent)
{
    scene = new Scene();
    this->setScene(scene);
    this->resize(1200, 1000);
    this->setMinimumSize(600, 500);
//    this->setFixedSize(600,600);
    this->setRenderHint(QPainter::Antialiasing);    // Устанавливаем сглаживание
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // Отключаем скроллбар по вертикали
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // Отключаем скроллбар по горизонтали
    scene->setSceneRect(0, 0, 1200, 1000);   // Устанавливаем размеры графической сцены
    QRect rect(150, 150, 300, 300);
    QRect mainrect(0, 0, 1200, 1000);
    scene->addRect(rect);
    scene->addRect(mainrect);

//    QPoint A(300, 300), B(400, 200), C(500, 300);
    A = QPoint(300, 300);
    B = QPoint(400, 200);
    x_B = B.x();
    C = QPoint(500, 300);
    stB = left;
    stC = right;
    hinge = new Hinge(); //неподвижный шарнир
    hinge->setPos(A);
    scene->addItem(hinge);
    scene->crank1 = new Crank(A, B); //кривошип
    scene->crank1->setPos(A);
    scene->addItem(scene->crank1);
    fhinge = new FixedHinge(); //шарнир
    fhinge->setPos(B);
    scene->addItem(fhinge);
    crank2 = new Crank(B, C); //шатун
    crank2->setPos(B);
    scene->addItem(crank2);
    slider = new Slider(); //ползун
    slider->setPos(C);
    scene->addItem(slider);
    point = new Point(A, B, 100);
    scene->addItem(point);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(moveC()));
    connect(timer, SIGNAL(timeout()), this, SLOT(moveB()));
    connect(timer, SIGNAL(timeout()), scene, SLOT(advance()));
    timer->start(1000/30);
}

void MainWidget::_edit_hight(const QString& hstr)
{
    //поднимаем точку B
    B.setY(A.y()-hstr.toInt());
    //двигаем кривошип и шатун
    scene->crank1->setB(B);
    crank2->setA(B);
    crank2->setPos(B);
    fhinge->setPos(B);
}

void MainWidget::_stop_timer()
{
    timer->stop();
}

void MainWidget::_start_timer()
{
    timer->start(1000/30);
}

void MainWidget::moveB()
{
    //двигаем точку В по х
    if (stB == left) {
        if (B.x() > 300)
            B.setX(B.x()-2);
        else {
            B.setX(B.x()+2);
            stB = right;
        }
    } else {
        if (B.x() < 500)
            B.setX(B.x()+2);
        else {
            B.setX(B.x()-2);
            stB = left;
        }
    }
    //двигаем кривошип и шатун
    scene->crank1->setB(B);
    crank2->setA(B);
    crank2->setPos(B);
    fhinge->setPos(B);
    point->setB(B);
    x_B = B.x();
}

void MainWidget::moveC()
{
    //двигаем точку C по х
    if (stC == left) {
        if (C.x() > 400)
            C.setX(C.x()-2);
        else {
            C.setX(C.x()+2);
            stC = right;
        }
    } else {
        if (C.x() < 600)
            C.setX(C.x()+2);
        else {
            C.setX(C.x()-2);
            stC = left;
        }
    }
    //двигаем кривошип и шатун
    crank2->setB(C);
    slider->setPos(C);
}
