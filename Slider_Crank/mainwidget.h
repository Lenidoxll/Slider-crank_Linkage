#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGridLayout>
#include <QTimer>
#include "scene.h"
#include "hinge.h"
#include "crank.h"
#include "fixedhinge.h"
#include "slider.h"
#include "point.h"

class MainWidget : public QGraphicsView
{
    Q_OBJECT
public:
    explicit MainWidget(QWidget *parent = nullptr);   

public:
    Scene* scene;
    QTimer* timer;
    int x_B;
private:
    QPoint A, B, C;
    Hinge* hinge;
//    Crank* crank1;
    FixedHinge* fhinge;
    Crank* crank2;
    Slider* slider;
    Point* point;
    enum Status {left, right};
    Status stB;
    Status stC;

public slots:
    void _edit_hight(const QString &hstr);
    void _stop_timer();
    void _start_timer();
private slots:
    void moveB();
    void moveC();
};

#endif // MAINWIDGET_H
