#include "slider_crank_linkage.h"
#include "value.h"
#include "image_of_slider_crank_linkage.h"
#include "parts.h"
#include "mechanism_1.h"
#include "plot.h"

#include <QtMath>
#include <QDebug>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QVector>
#include <QGridLayout>
#include <QFont>
#include <QComboBox>
#include <QTimer>
#include <QGuiApplication>
#include <QToolButton>
#include <QPushButton>
#include <QScreen>

using namespace Constants;

Slider_crank_linkage::Slider_crank_linkage(QWidget *parent)
    : QWidget(parent)
{
    //задаем размеры
//    QPoint center = ((QGuiApplication::primaryScreen())->geometry()).center();
//    this->setGeometry(center.x()/3, center.y()/3,
//                      ((QGuiApplication::primaryScreen())->geometry()).width()/2,
//                      ((QGuiApplication::primaryScreen())->geometry()).height()/2);

    font = QFont("Purisa", 11);

    initial_value();                //задаем начальные значения
    create_values();                //создаем окошки входных и выходных данных
    calculate = new QPushButton(tr("Посчитать"));
    calculate->setFont(font);

    QVBoxLayout* vboxleft = new QVBoxLayout;
    vboxleft->addWidget(inv);
    vboxleft->addWidget(calculate);

    hbox = new QHBoxLayout(this);
    hbox->addLayout(vboxleft);           //первая колонка (входные значения)
    hbox->addStretch();
    hbox->addWidget(outv);          //вторая колонка (выходные значения)

    Calculation();                  //вычисляем выходные данные
    change_output_values();         //отображаем выходные данные
    create_mechanism();             //создаем картинку

    pause_or_play = new QToolButton;        //создаем кнопку pause or play
    pause_or_play->setIcon(play);
    pause_or_play->setIconSize(QSize(50, 50));

    QHBoxLayout* hboxright1 = new QHBoxLayout();    //hbox для того, чтобы прижать кнопку pause or play
    hboxright1->addWidget(SAstatus);
    hboxright1->addStretch();
    hboxright1->addWidget(pause_or_play);

    create_plot();
    QHBoxLayout* hboxright2 = new QHBoxLayout();
    hboxright2->addWidget(mechanism);
    hboxright2->addWidget(plot);

    mechanism_or_graphic = new QPushButton(tr("График"));
    mechanism_or_graphic->setFont(font);
    QHBoxLayout* hboxright3 = new QHBoxLayout();
    hboxright3->addWidget(mechanism_or_graphic);
    hboxright3->addStretch();

    vbox = new QVBoxLayout();       //третья колонка (картинка/график и кнопочки)
    vbox->addLayout(hboxright1);
    vbox->addLayout(hboxright2);
    vbox->addLayout(hboxright3);

    hbox->addStretch();
    hbox->addLayout(vbox);
    setLayout(hbox);

    _slot_off();

    connect(inv->fi1g_value->lineEdit, &QLineEdit::textChanged, this, &Slider_crank_linkage::_fi1g_changed);
    connect(inv->alg_value->lineEdit, &QLineEdit::textChanged, this, &Slider_crank_linkage::_alg_changed);
    connect(inv->l1_value->lineEdit, &QLineEdit::textChanged, this, &Slider_crank_linkage::_l1_changed);
    connect(inv->l2_value->lineEdit, &QLineEdit::textChanged, this, &Slider_crank_linkage::_l2_changed);
    connect(inv->xl_value->lineEdit, &QLineEdit::textChanged, this, &Slider_crank_linkage::_xl_changed);
    connect(inv->yl_value->lineEdit, &QLineEdit::textChanged, this, &Slider_crank_linkage::_yl_changed);
    connect(inv->xc2_value->lineEdit, &QLineEdit::textChanged, this, &Slider_crank_linkage::_xc2_changed);
    connect(inv->yc2_value->lineEdit, &QLineEdit::textChanged, this, &Slider_crank_linkage::_yc2_changed);
    connect(inv->om1_value->lineEdit, &QLineEdit::textChanged, this, &Slider_crank_linkage::_om1_changed);
    connect(inv->ep1_value->lineEdit, &QLineEdit::textChanged, this, &Slider_crank_linkage::_ep1_changed);
    connect(inv->xo1_value->lineEdit, &QLineEdit::textChanged, this, &Slider_crank_linkage::_xo1_changed);
    connect(inv->yo1_value->lineEdit, &QLineEdit::textChanged, this, &Slider_crank_linkage::_yo1_changed);
    connect(inv->vo1x_value->lineEdit, &QLineEdit::textChanged, this, &Slider_crank_linkage::_vo1x_changed);
    connect(inv->vo1y_value->lineEdit, &QLineEdit::textChanged, this, &Slider_crank_linkage::_vo1y_changed);
    connect(inv->ao1x_value->lineEdit, &QLineEdit::textChanged, this, &Slider_crank_linkage::_ao1x_changed);
    connect(inv->ao1y_value->lineEdit, &QLineEdit::textChanged, this, &Slider_crank_linkage::_ao1y_changed);
    connect(inv->k_comboBox, &QComboBox::currentTextChanged, this, &Slider_crank_linkage::_k_changed);
    connect(calculate, &QPushButton::clicked, this, &Slider_crank_linkage::_correct_calculation);
    connect(SAstatus->vo1, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Slider_crank_linkage::_status_vo1_changed);
    connect(SAstatus->ao1, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Slider_crank_linkage::_status_ao1_changed);
    connect(SAstatus->va, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Slider_crank_linkage::_status_va_changed);
    connect(SAstatus->aa, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Slider_crank_linkage::_status_aa_changed);
    connect(SAstatus->vb, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Slider_crank_linkage::_status_vb_changed);
    connect(SAstatus->ab, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Slider_crank_linkage::_status_ab_changed);
    connect(SAstatus->vc, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Slider_crank_linkage::_status_vc_changed);
    connect(SAstatus->ac, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Slider_crank_linkage::_status_ac_changed);
    connect(pause_or_play, &QToolButton::clicked, this, &Slider_crank_linkage::_slot_pause_or_play);
    connect(mechanism_or_graphic, &QPushButton::clicked, this, &Slider_crank_linkage::_slot_mechanism_or_graphic);
    connect(mechanism->timer, &QTimer::timeout, this, &Slider_crank_linkage::_auto_rotate_mechanism);
}

void Slider_crank_linkage::initial_value()
{
    fi1g = 70.0;
    l1 = 12;
    l2 = 46;
    l3 = 0;
    alg = 70.0;
    xl = 30;
    yl = 10;
    k = orientation_l::right;
    xc2 = 30.666;
    yc2 = 0;
    om1 = 2;
    ep1 = 0;
    xo1 = 0;
    yo1 = 0;
    vo1x = 0;
    vo1y = 0;
    ao1x = 0;
    ao1y = 0;
}

void Slider_crank_linkage::create_values()
{
    inv = new InputValues();
    outv = new OutputValues();
    SAstatus = new SpeedAccelStatus();

    inv->setFont(font);
    outv->setFont(font);
    SAstatus->setFont(font);
}

void Slider_crank_linkage::create_mechanism()
{
    mechanism = new Mechanism_1(font, l1, l2, xa, ya, xb, yb, xl, yl, xc, yc, xc2, yc2, fi1g, fi2g, alg, xmin, ymin, xmax, ymax, xo1, yo1);
    mechanism->setSpeedForPointC(vcx, vcy, vc);
    mechanism->setAccelForPointC(acx, acy, ac);
    mechanism->changeAccelStatusO1(Constants::SHOWNOTHINGACCEL);
    mechanism->changeSpeedStatusO1(Constants::SHOWNOTHINGSPEED);
    mechanism->changeAccelStatusB(Constants::SHOWNOTHINGACCEL);
    mechanism->changeSpeedStatusB(Constants::SHOWNOTHINGSPEED);
    mechanism->changeAccelStatusA(Constants::SHOWNOTHINGACCEL);
    mechanism->changeSpeedStatusA(Constants::SHOWNOTHINGSPEED);
    mechanism->changeAccelStatusC(Constants::SHOWA);
    mechanism->changeSpeedStatusC(Constants::SHOWV);
}

void Slider_crank_linkage::create_plot()
{
    plot = new Plot;
    plot->customPlot->setFont(font);
    plot->setColorO1(mechanism->getColorO1());
    plot->setColorA(mechanism->getColorA());
    plot->setColorB(mechanism->getColorB());
    plot->setColorC(mechanism->getColorC());
    plot->changedSpeedStatusO1(mechanism->getCurrentSpeedStatusO1());
    plot->changedSpeedStatusA(mechanism->getCurrentSpeedStatusA());
    plot->changedSpeedStatusB(mechanism->getCurrentSpeedStatusB());
    plot->changedSpeedStatusC(mechanism->getCurrentSpeedStatusC());
    plot->changedAccelStatusO1(mechanism->getCurrentAccelStatusO1());
    plot->changedAccelStatusA(mechanism->getCurrentAccelStatusA());
    plot->changedAccelStatusB(mechanism->getCurrentAccelStatusB());
    plot->changedAccelStatusC(mechanism->getCurrentAccelStatusC());

    plot->hide();
}

void Slider_crank_linkage::change_output_values()
{
    outv->_fiO1g_change(fi1g);
    outv->_fiABg_change(fi2g);
    outv->_omO1_change(om1);
    outv->_omAB_change(om2);
    outv->_epO1_change(ep1);
    outv->_epAB_change(ep2);
    outv->_xO1_change(xo1);
    outv->_yO1_change(yo1);
    outv->_xA_change(xa);
    outv->_yA_change(ya);
    outv->_xB_change(xb);
    outv->_yB_change(yb);
    outv->_xC_change(xc);
    outv->_yC_change(yc);
    outv->_vxO1_change(vo1x);
    outv->_vyO1_change(vo1y);
    outv->_vO1_change(vo1);
    outv->_vxA_change(vax);
    outv->_vyA_change(vay);
    outv->_vA_change(va);
    outv->_vxB_change(vbx);
    outv->_vyB_change(vby);
    outv->_vB_change(vb);
    outv->_vxC_change(vcx);
    outv->_vyC_change(vcy);
    outv->_vC_change(vc);
    outv->_axO1_change(ao1x);
    outv->_ayO1_change(ao1y);
    outv->_aO1_change(ao1);
    outv->_axA_change(aax);
    outv->_ayA_change(aay);
    outv->_aA_change(aa);
    outv->_axB_change(abx);
    outv->_ayB_change(aby);
    outv->_aB_change(ab);
    outv->_axC_change(acx);
    outv->_ayC_change(acy);
    outv->_aC_change(ac);
}

void Slider_crank_linkage::change_mechanism()
{
    mechanism->change_position(xa, ya, xb, yb, xc, yc, fi1g, fi2g, xo1, yo1);
    mechanism->setLengthO1A(l1);
    mechanism->setLengthAB(l2);
    mechanism->setalg(alg);
    mechanism->setPointL(xl, yl);
    mechanism->setPointC(xc2, yc2);
    mechanism->setRamka(xmin, ymin, xmax, ymax);
    mechanism->setSpeedForPointO1(vo1x, vo1y, vo1);
    mechanism->setAccelForPointO1(ao1x, ao1y, ao1);
    mechanism->setSpeedForPointA(vax, vay, va);
    mechanism->setSpeedForPointB(vbx, vby, vb);
    mechanism->setSpeedForPointC(vcx, vcy, vc);
    mechanism->setAccelForPointA(aax, aay, aa);
    mechanism->setAccelForPointB(abx, aby, ab);
    mechanism->setAccelForPointC(acx, acy, ac);
    mechanism->change_rect();
}

void Slider_crank_linkage::change_plot()
{
    plot->_restart(fi1g, vo1x, vo1y, vo1, ao1x, ao1y, ao1,
                   vax, vay, va, aax, aay, aa,
                   vbx, vby, vb, abx, aby, ab,
                   vcx, vcy, vc, acx, acy, ac);
}

void Slider_crank_linkage::_correct_calculation()
{
    Calculation();
    qDebug() << "ind = " << ind << Qt::endl;
    if (ind == 0) {
        change_output_values();
        change_mechanism();
        change_plot();
    } else if (ind == 1) {
        QMessageBox::warning(this, tr("Error"), QString(tr("Error's type is first.")), QMessageBox::Ok);
    } else if (ind == 2) {
        QMessageBox::warning(this, tr("Error"), QString(tr("Error's type is second.")), QMessageBox::Ok);
    }
}

void Slider_crank_linkage::_fi1g_changed(const QString &text)
{
    fi1g = text.toDouble();
}

void Slider_crank_linkage::_alg_changed(const QString &text)
{
    alg = text.toDouble();
}

void Slider_crank_linkage::_l1_changed(const QString &text)
{
    l1 = text.toDouble();
}

void Slider_crank_linkage::_l2_changed(const QString &text)
{
    l2 = text.toDouble();
}

void Slider_crank_linkage::_xl_changed(const QString &text)
{
    xl = text.toDouble();
}

void Slider_crank_linkage::_yl_changed(const QString &text)
{
    yl = text.toDouble();
}

void Slider_crank_linkage::_xc2_changed(const QString &text)
{
    xc2 = text.toDouble();
}

void Slider_crank_linkage::_yc2_changed(const QString &text)
{
    yc2 = text.toDouble();
}

void Slider_crank_linkage::_om1_changed(const QString &text)
{
    om1 = text.toDouble();
}

void Slider_crank_linkage::_ep1_changed(const QString &text)
{
    ep1 = text.toDouble();
}

void Slider_crank_linkage::_xo1_changed(const QString &text)
{
    xo1 = text.toDouble();
}

void Slider_crank_linkage::_yo1_changed(const QString &text)
{
    yo1 = text.toDouble();
}

void Slider_crank_linkage::_vo1x_changed(const QString &text)
{
    vo1x = text.toDouble();
}

void Slider_crank_linkage::_vo1y_changed(const QString &text)
{
    vo1y = text.toDouble();
}

void Slider_crank_linkage::_ao1x_changed(const QString &text)
{
    ao1x = text.toDouble();
}

void Slider_crank_linkage::_ao1y_changed(const QString &text)
{
    ao1y = text.toDouble();
}

void Slider_crank_linkage::_k_changed(const QString &text)
{
    if (text == QString("right"))
        k = orientation_l::right;
    else
        k = orientation_l::left;
}

void Slider_crank_linkage::_status_vo1_changed(const int index)
{
    if (index == 0) {
        mechanism->changeSpeedStatusO1(Constants::SHOWV);
        plot->changedSpeedStatusO1(Constants::SHOWV);
    } else if (index == 1) {
        mechanism->changeSpeedStatusO1(Constants::SHOWVX);
        plot->changedSpeedStatusO1(Constants::SHOWVX);
    } else if (index == 2) {
        mechanism->changeSpeedStatusO1(Constants::SHOWVY);
        plot->changedSpeedStatusO1(Constants::SHOWVY);
    } else if (index == 3) {
        mechanism->changeSpeedStatusO1(Constants::SHOWVXV);
        plot->changedSpeedStatusO1(Constants::SHOWVXV);
    } else if (index == 4) {
        mechanism->changeSpeedStatusO1(Constants::SHOWVYV);
        plot->changedSpeedStatusO1(Constants::SHOWVYV);
    } else if (index == 5) {
        mechanism->changeSpeedStatusO1(Constants::SHOWVXY);
        plot->changedSpeedStatusO1(Constants::SHOWVXY);
    } else if (index == 6) {
        mechanism->changeSpeedStatusO1(Constants::SHOWSPEED);
        plot->changedSpeedStatusO1(Constants::SHOWSPEED);
    } else {
        mechanism->changeSpeedStatusO1(Constants::SHOWNOTHINGSPEED);
        plot->changedSpeedStatusO1(Constants::SHOWNOTHINGSPEED);
    }
}

void Slider_crank_linkage::_status_ao1_changed(const int index)
{
    if (index == 0) {
        mechanism->changeAccelStatusO1(Constants::SHOWA);
        plot->changedAccelStatusO1(Constants::SHOWA);
    } else if (index == 1) {
        mechanism->changeAccelStatusO1(Constants::SHOWAX);
        plot->changedAccelStatusO1(Constants::SHOWAX);
    } else if (index == 2) {
        mechanism->changeAccelStatusO1(Constants::SHOWAY);
        plot->changedAccelStatusO1(Constants::SHOWAY);
    } else if (index == 3) {
        mechanism->changeAccelStatusO1(Constants::SHOWAXA);
        plot->changedAccelStatusO1(Constants::SHOWAXA);
    } else if (index == 4) {
        mechanism->changeAccelStatusO1(Constants::SHOWAYA);
        plot->changedAccelStatusO1(Constants::SHOWAYA);
    } else if (index == 5) {
        mechanism->changeAccelStatusO1(Constants::SHOWAXY);
        plot->changedAccelStatusO1(Constants::SHOWAXY);
    } else if (index == 6) {
        mechanism->changeAccelStatusO1(Constants::SHOWACCEL);
        plot->changedAccelStatusO1(Constants::SHOWACCEL);
    } else {
        mechanism->changeAccelStatusO1(Constants::SHOWNOTHINGACCEL);
        plot->changedAccelStatusO1(Constants::SHOWNOTHINGACCEL);
    }
}

void Slider_crank_linkage::_status_va_changed(const int index)
{
    if (index == 0) {
        mechanism->changeSpeedStatusA(Constants::SHOWV);
        plot->changedSpeedStatusA(Constants::SHOWV);
    } else if (index == 1) {
        mechanism->changeSpeedStatusA(Constants::SHOWVX);
        plot->changedSpeedStatusA(Constants::SHOWVX);
    } else if (index == 2) {
        mechanism->changeSpeedStatusA(Constants::SHOWVY);
        plot->changedSpeedStatusA(Constants::SHOWVY);
    } else if (index == 3) {
        mechanism->changeSpeedStatusA(Constants::SHOWVXV);
        plot->changedSpeedStatusA(Constants::SHOWVXV);
    } else if (index == 4) {
        mechanism->changeSpeedStatusA(Constants::SHOWVYV);
        plot->changedSpeedStatusA(Constants::SHOWVYV);
    } else if (index == 5) {
        mechanism->changeSpeedStatusA(Constants::SHOWVXY);
        plot->changedSpeedStatusA(Constants::SHOWVXY);
    } else if (index == 6) {
        mechanism->changeSpeedStatusA(Constants::SHOWSPEED);
        plot->changedSpeedStatusA(Constants::SHOWSPEED);
    } else {
        mechanism->changeSpeedStatusA(Constants::SHOWNOTHINGSPEED);
        plot->changedSpeedStatusA(Constants::SHOWNOTHINGSPEED);
    }
}

void Slider_crank_linkage::_status_aa_changed(const int index)
{
    if (index == 0) {
        mechanism->changeAccelStatusA(Constants::SHOWA);
        plot->changedAccelStatusA(Constants::SHOWA);
    } else if (index == 1) {
        mechanism->changeAccelStatusA(Constants::SHOWAX);
        plot->changedAccelStatusA(Constants::SHOWAX);
    } else if (index == 2) {
        mechanism->changeAccelStatusA(Constants::SHOWAY);
        plot->changedAccelStatusA(Constants::SHOWAY);
    } else if (index == 3) {
        mechanism->changeAccelStatusA(Constants::SHOWAXA);
        plot->changedAccelStatusA(Constants::SHOWAXA);
    } else if (index == 4) {
        mechanism->changeAccelStatusA(Constants::SHOWAYA);
        plot->changedAccelStatusA(Constants::SHOWAYA);
    } else if (index == 5) {
        mechanism->changeAccelStatusA(Constants::SHOWAXY);
        plot->changedAccelStatusA(Constants::SHOWAXY);
    } else if (index == 6) {
        mechanism->changeAccelStatusA(Constants::SHOWACCEL);
        plot->changedAccelStatusA(Constants::SHOWACCEL);
    } else {
        mechanism->changeAccelStatusA(Constants::SHOWNOTHINGACCEL);
        plot->changedAccelStatusA(Constants::SHOWNOTHINGACCEL);
    }
}

void Slider_crank_linkage::_status_vb_changed(const int index)
{
    if (index == 0) {
        mechanism->changeSpeedStatusB(Constants::SHOWV);
        plot->changedSpeedStatusB(Constants::SHOWV);
    } else if (index == 1) {
        mechanism->changeSpeedStatusB(Constants::SHOWVX);
        plot->changedSpeedStatusB(Constants::SHOWVX);
    } else if (index == 2) {
        mechanism->changeSpeedStatusB(Constants::SHOWVY);
        plot->changedSpeedStatusB(Constants::SHOWVY);
    } else if (index == 3) {
        mechanism->changeSpeedStatusB(Constants::SHOWVXV);
        plot->changedSpeedStatusB(Constants::SHOWVXV);
    } else if (index == 4) {
        mechanism->changeSpeedStatusB(Constants::SHOWVYV);
        plot->changedSpeedStatusB(Constants::SHOWVYV);
    } else if (index == 5) {
        mechanism->changeSpeedStatusB(Constants::SHOWVXY);
        plot->changedSpeedStatusB(Constants::SHOWVXY);
    } else if (index == 6) {
        mechanism->changeSpeedStatusB(Constants::SHOWSPEED);
        plot->changedSpeedStatusB(Constants::SHOWSPEED);
    } else {
        mechanism->changeSpeedStatusB(Constants::SHOWNOTHINGSPEED);
        plot->changedSpeedStatusB(Constants::SHOWNOTHINGSPEED);
    }
}

void Slider_crank_linkage::_status_ab_changed(const int index)
{
    if (index == 0) {
        mechanism->changeAccelStatusB(Constants::SHOWA);
        plot->changedAccelStatusB(Constants::SHOWA);
    } else if (index == 1) {
        mechanism->changeAccelStatusB(Constants::SHOWAX);
        plot->changedAccelStatusB(Constants::SHOWAX);
    } else if (index == 2) {
        mechanism->changeAccelStatusB(Constants::SHOWAY);
        plot->changedAccelStatusB(Constants::SHOWAY);
    } else if (index == 3) {
        mechanism->changeAccelStatusB(Constants::SHOWAXA);
        plot->changedAccelStatusB(Constants::SHOWAXA);
    } else if (index == 4) {
        mechanism->changeAccelStatusB(Constants::SHOWAYA);
        plot->changedAccelStatusB(Constants::SHOWAYA);
    } else if (index == 5) {
        mechanism->changeAccelStatusB(Constants::SHOWAXY);
        plot->changedAccelStatusB(Constants::SHOWAXY);
    } else if (index == 6) {
        mechanism->changeAccelStatusB(Constants::SHOWACCEL);
        plot->changedAccelStatusB(Constants::SHOWACCEL);
    } else {
        mechanism->changeAccelStatusB(Constants::SHOWNOTHINGACCEL);
        plot->changedAccelStatusB(Constants::SHOWNOTHINGACCEL);
    }
}

void Slider_crank_linkage::_status_vc_changed(const int index)
{
    if (index == 0) {
        mechanism->changeSpeedStatusC(Constants::SHOWV);
        plot->changedSpeedStatusC(Constants::SHOWV);
    } else if (index == 1) {
        mechanism->changeSpeedStatusC(Constants::SHOWVX);
        plot->changedSpeedStatusC(Constants::SHOWVX);
    } else if (index == 2) {
        mechanism->changeSpeedStatusC(Constants::SHOWVY);
        plot->changedSpeedStatusC(Constants::SHOWVY);
    } else if (index == 3) {
        mechanism->changeSpeedStatusC(Constants::SHOWVXV);
        plot->changedSpeedStatusC(Constants::SHOWVXV);
    } else if (index == 4) {
        mechanism->changeSpeedStatusC(Constants::SHOWVYV);
        plot->changedSpeedStatusC(Constants::SHOWVYV);
    } else if (index == 5) {
        mechanism->changeSpeedStatusC(Constants::SHOWVXY);
        plot->changedSpeedStatusC(Constants::SHOWVXY);
    } else if (index == 6) {
        mechanism->changeSpeedStatusC(Constants::SHOWSPEED);
        plot->changedSpeedStatusC(Constants::SHOWSPEED);
    } else {
        mechanism->changeSpeedStatusC(Constants::SHOWNOTHINGSPEED);
        plot->changedSpeedStatusC(Constants::SHOWNOTHINGSPEED);
    }
}

void Slider_crank_linkage::_status_ac_changed(const int index)
{
    if (index == 0) {
        mechanism->changeAccelStatusC(Constants::SHOWA);
        plot->changedAccelStatusC(Constants::SHOWA);
    } else if (index == 1) {
        mechanism->changeAccelStatusC(Constants::SHOWAX);
        plot->changedAccelStatusC(Constants::SHOWAX);
    } else if (index == 2) {
        mechanism->changeAccelStatusC(Constants::SHOWAY);
        plot->changedAccelStatusC(Constants::SHOWAY);
    } else if (index == 3) {
        mechanism->changeAccelStatusC(Constants::SHOWAXA);
        plot->changedAccelStatusC(Constants::SHOWAXA);
    } else if (index == 4) {
        mechanism->changeAccelStatusC(Constants::SHOWAYA);
        plot->changedAccelStatusC(Constants::SHOWAYA);
    } else if (index == 5) {
        mechanism->changeAccelStatusC(Constants::SHOWAXY);
        plot->changedAccelStatusC(Constants::SHOWAXY);
    } else if (index == 6) {
        mechanism->changeAccelStatusC(Constants::SHOWACCEL);
        plot->changedAccelStatusC(Constants::SHOWACCEL);
    } else {
        mechanism->changeAccelStatusC(Constants::SHOWNOTHINGACCEL);
        plot->changedAccelStatusC(Constants::SHOWNOTHINGACCEL);
    }
}

void Slider_crank_linkage::_auto_rotate_mechanism()
{
    double _fi1g = - mechanism->getfi1();
    double _alg = - mechanism->getal();
    double _l1 = mechanism->getLengthO1A();
    double _l2 = mechanism->getLengthAB();
    double _vo1x = mechanism->getVxo1();
    double _vo1y = mechanism->getVyo1();
    double _ao1x = mechanism->getAxo1();
    double _ao1y = mechanism->getAyo1();
    double _xc2 = mechanism->getXc2();
    double _yc2 = mechanism->getYc2();

    double _fi1, _al, _fi2, _fi2g;
    double _xa, _ya, _xb, _yb, _xc, _yc;
    double _vax, _vay, _va, _vcx, _vcy, _vc, _vbx, _vby, _vb;
    double _aax, _aay, _aa, _acx, _acy, _ac, _abx, _aby, _ab;
    double _om2, _ep2;
    double _xmax, _xmin, _ymax, _ymin, _xmid, _ymid, _arat;
    types _ind = type_first;
    _fi1g++;


    _fi1 = from_degrees_to_radians(_fi1g);
    _al = from_degrees_to_radians(_alg);
    coord0(xo1, yo1, _l1, 0, _fi1, _xa, _ya);                       //получаем xa и ya
    coord1(_xa, _ya, _l2, _al, xl, yl, k, _fi2, _ind);                //получаем fi2 и ind
    _fi2g = from_radians_to_degrees(_fi2);
    if (_ind > 0) return;
    coord0(_xa, _ya, mechanism->getXc2(), - mechanism->getYc2(), _fi2, _xc, _yc);       //получаем xc и yc
    coord0(_xa, _ya, _l2, 0, _fi2, _xb, _yb);                         //получаем xb и yb

    speed0(_vo1x, _vo1y, om1, _l1, 0, _fi1, _vax, _vay, _va);          //получаем vax, vay, va
    speed1(_vax, _vay, _l2, _al, _fi2, _om2, _ind);                    //получаем om2, ind
    if (_ind > 0) return;
    speed0(_vax, _vay, _om2, _xc2, _yc2, _fi2, _vcx, _vcy, _vc);         //получаем vcx, vcy, vc
    speed0(_vax, _vay, _om2, _l2, 0, _fi2, _vbx, _vby, _vb);            //получаем vbx, vby, vb
    accel0(_ao1x, _ao1y, om1, ep1, _l1, 0, _fi1, _aax, _aay, _aa);     //получаем aax, aay, aa
    accel1(_aax, _aay, _l2, _al, _fi2, _om2, _ep2, _ind);               //получаем ep2, ind
    if (_ind > 0) return;
    accel0(_aax, _aay, _om2, _ep2, _xc2, _yc2, _fi2, _acx, _acy, _ac);    //получаем acx, acy, ac
    accel0(_aax, _aay, _om2, _ep2, _l2, 0, _fi2, _abx, _aby, _ab);       //получаем abx, aby, ab
    Ramka1(xo1, yo1, xl, yl, _l1, _l2, _al, _xc2, _yc2,
      k, _xmax, _xmin, _ymax, _ymin, _xmid, _ymid, _arat);             //получаем xmax, xmin, ymax, ymin, xmid, ymid, arat

    mechanism->change_position(_xa, _ya, _xb, _yb, _xc, _yc, _fi1g, _fi2g, xo1, yo1);
    mechanism->setSpeedForPointA(_vax, _vay, _va);
    mechanism->setSpeedForPointB(_vbx, _vby, _vb);
    mechanism->setSpeedForPointC(_vcx, _vcy, _vc);
    mechanism->setAccelForPointA(_aax, _aay, _aa);
    mechanism->setAccelForPointB(_abx, _aby, _ab);
    mechanism->setAccelForPointC(_acx, _acy, _ac);

    double _vo1 = sqrt(vo1x*vo1x + vo1y*vo1y);                          //получаем vo1
    double _ao1 = sqrt(ao1x*ao1x + ao1y*ao1y);                          //получаем ao1

    plot->_add_points(_fi1g, _vo1x, _vo1y, _vo1, _ao1x, _ao1y, _ao1,
                      _vax, _vay, _va, _aax, _aay, _aa,
                      _vbx, _vby, _vb, _abx, _aby, _ab,
                      _vcx, _vcy, _vc, _acx, _acy, _ac);
}

void Slider_crank_linkage::_slot_pause_or_play()
{
    if (current_stats_pause_or_play == PLAY) {
        current_stats_pause_or_play = PAUSE;
        pause_or_play->setIcon(play);
        mechanism->_stop_timer();
    } else {
        current_stats_pause_or_play = PLAY;
        pause_or_play->setIcon(pause);
        mechanism->_start_timer();
    }
}

void Slider_crank_linkage::_slot_mechanism_or_graphic()
{
    if (current_stats_mechanism_or_graphic == Constants::MECHANISM) {
        current_stats_mechanism_or_graphic = Constants::GRAPHIC;
        mechanism_or_graphic->setText(tr("Рисунок"));
        mechanism->hide();
        plot->show();
    } else {
        current_stats_mechanism_or_graphic = Constants::MECHANISM;
        mechanism_or_graphic->setText(tr("График"));
        plot->hide();
        mechanism->show();
    }
}

void Slider_crank_linkage::_slot_on()
{
    current_status_on_or_off = Constants::on;
    mechanism->setMinimumSize(600, 100);
    plot->setMinimumSize(600, 100);
}

void Slider_crank_linkage::_slot_off()
{
    current_status_on_or_off = Constants::off;
    mechanism->setMinimumSize(10, 10);
    plot->setMinimumSize(10, 10);
}

void Slider_crank_linkage::coord1(double xa, double ya, double l, double al,
                                  double xl, double yl, orientation_l k,
                                  double& fi,
                                  types& ind)
{
    double sal, xd, kap, om;
    ind = type_first;
    sal = qSin(al);
    if (qAbs(sal) <= error) {
        om = (yl - ya) / l;
        if (qAbs(om) > 1) {
            ind = type_second;
            return;
        }
        if (k == right)
            fi = M_PI -  arcsin(om);
        if (k == left)
            fi =  arcsin(om);
        return;
    }
    xd = xl + (ya - yl)*qCos(al)/sal;
    kap = (xd - xa) * sal / l;
    if (qAbs(kap) > 1) {
        ind = type_second;
        return;
    }
    if (k == right)
        fi = -M_PI + al +  arcsin(kap);
    if (k == left)
        fi = al -  arcsin(kap);
    return;
}

void Slider_crank_linkage::speed1(double vax, double vay, double l,
                                  double al, double fi,
                                  double& om, types& ind)
{
    double caf, vxy;
    ind = type_first;
    caf = qCos(al - fi);
    vxy = vax * qSin(al) - vay * qCos(al);
    if (qAbs(caf) < error) {
        if (qAbs(vxy) < error)
            ind = type_third;
        else
            ind = type_second;
        return;
    }
    om = vxy / (l * caf);
    return;
}

void Slider_crank_linkage::accel1(double aax, double aay, double l,
                                  double al, double fi, double om,
                                  double& ep, types& ind)
{
    double caf, axy;
    ind = type_first;
    caf = qCos(al - fi);
    axy = aax * qSin(al) - aay * qCos(al)
            - om * om * l * qSin(al - fi);
    if (qAbs(caf) < error) {
        if (qAbs(axy) < error)
            ind = type_third;
        else
            ind = type_second;
        return;
    }
    ep = axy / (l * caf);
    return;
}

void Slider_crank_linkage::Ramka1(double xo1, double yo1, double xl, double yl,
                                  double l1, double l2, double al,
                                  double xc2, double yc2, orientation_l k,
                                  double& xmax, double& xmin, double& ymax, double& ymin,
                                  double& xmid, double& ymid, double& arat)
{
    double fi1, fi2; //Зачем тут угол fi3 (см оригнал)
    double xa, ya, xb, yb, xc, yc;
    double xmas[5], ymas[5];
    double xbmin, ybmin, xbmax, ybmax, r20, rca, rsa;
    types kk;

    double x1al, y1al, x2al, y2al; //Это что-то временное или постоянное?

    xmin = error;
    ymin = error;
    xmax = -error;
    ymax = -error;

    xbmin = error;
    ybmin = error;
    xbmax = -error;
    ybmax = -error;

    kk = type_second;

    for (int i = 0; i < 8; i++) {
        fi1 = i * M_PI_4;
        coord0(xo1, yo1, l1, 0, fi1, xa, ya);
        coord1(xa, ya, l2, al, xl, yl, k, fi2, this->ind);
        if (this->ind == 0)
            kk = type_first;
        if (!this->ind) {
            coord0(xa, ya, l2, 0, fi2, xb, yb);
            coord0(xa, ya, xc2, yc2, fi2, xc, yc);
            xmas[0] = xo1;
            xmas[1] = xa;
            xmas[2] = xb;
            xmas[3] = xc;
            xmas[4] = xl;
            ymas[0] = yo1;
            ymas[1] = ya;
            ymas[2] = yb;
            ymas[3] = yc;
            ymas[4] = yl;
            for (int j = 1; j < 6; j++) {
                if (xmas[j] < xmin)
                    xmin = xmas[j];
                if (xmas[j] > xmax)
                    xmax = xmas[j];
                if (ymas[j] < ymin)
                    ymin = ymas[j];
                if (ymas[j] > ymax)
                    ymax = ymas[j];
            }
            if (xb < xbmin)
                xbmin = xb;
            if (xb > xbmax)
                xbmax = xb;
            if (yb < ybmin)
                ybmin = yb;
            if (yb > ybmax)
                ybmax = yb;
        }
    }

    if(xl < xbmin) xbmin = xl;
    if(xl > xbmax) xbmax = xl;
    if(yl < ybmin) ybmin = yl;
    if(yl > ybmax) ybmax = yl;
    y1al = ybmax; //Это что-то временное или постоянное?
    y2al = ybmin;
    if(al < M_PI_2) {
       x1al = xbmax;
       x2al = xbmin;
    } else {
       x1al = xbmin;
       x2al = xbmax;
    }
    r20 = qPow(x1al-y1al, 2)+qPow(x2al-y2al, 2);
    r20 = qSqrt(r20)/20;
    rca = r20*qCos(al);
    rsa = r20*qSin(al);
    x1al = x1al + rca;
    x2al = x2al - rca;
    y1al = y1al + rsa;
    y2al = y2al - rsa;

    xmid = (xmin + xmax)/2;
    ymid = (ymin + ymax)/2;
    if (qAbs(xmin - xmax) >= error)
        arat = (ymax - ymin)/(xmax - xmin);
    else {
        qDebug() << "xmin=xmax, arat indefinite" << Qt::endl;
        arat = 100;
    }
    this->ind = kk;
}

void Slider_crank_linkage::Calculation()
{
    fi1 = from_degrees_to_radians(fi1g);
    al = from_degrees_to_radians(alg);
    coord0(xo1, yo1, l1, 0, fi1, xa, ya);                       //получаем xa и ya
    coord1(xa, ya, l2, al, xl, yl, k, fi2, ind);                //получаем fi2 и ind
    fi2g = from_radians_to_degrees(fi2);
    if (ind > 0) return;
    coord0(xa, ya, xc2, yc2, fi2, xc, yc);                      //получаем xc и yc
    coord0(xa, ya, l2, 0, fi2, xb, yb);                         //получаем xb и yb
    speed0(vo1x, vo1y, om1, l1, 0, fi1, vax, vay, va);          //получаем vax, vay, va
    speed1(vax, vay, l2, al, fi2, om2, ind);                    //получаем om2, ind
    if (ind > 0) return;
    speed0(vax, vay, om2, xc2, yc2, fi2, vcx, vcy, vc);         //получаем vcx, vcy, vc
    speed0(vax, vay, om2, l2, 0, fi2, vbx, vby, vb);            //получаем vbx, vby, vb
    accel0(ao1x, ao1y, om1, ep1, l1, 0, fi1, aax, aay, aa);     //получаем aax, aay, aa
    accel1(aax, aay, l2, al, fi2, om2, ep2, ind);               //получаем ep2, ind
    if (ind > 0) return;
    accel0(aax, aay, om2, ep2, xc2, yc2, fi2, acx, acy, ac);    //получаем acx, acy, ac
    accel0(aax, aay, om2, ep2, l2, 0, fi2, abx, aby, ab);       //получаем abx, aby, ab
    Ramka1(xo1, yo1, xl, yl, l1, l2, al, xc2, yc2,
      k, xmax, xmin, ymax, ymin, xmid, ymid, arat);             //получаем xmax, xmin, ymax, ymin, xmid, ymid, arat

    vo1 = sqrt(vo1x*vo1x + vo1y*vo1y);                          //получаем vo1
    ao1 = sqrt(ao1x*ao1x + ao1y*ao1y);                          //получаем ao1

    qDebug() << "***************************************" << Qt::endl;
    qDebug() << "fi1g = " << fi1g << ", fi2g = " << fi2g << Qt::endl;
    qDebug() << "om1 = " << om1 << ", om2 = " << om2 << Qt::endl;
    qDebug() << "ep1 = " << ep1 << ", ep2 = " << ep2 << Qt::endl;
    qDebug() << "***************************************" << Qt::endl;
    qDebug() << "xo1 = " << xo1 << ", yo1 = " << yo1 << Qt::endl;
    qDebug() << "xa = " << xa << ", ya = " << ya << Qt::endl;
    qDebug() << "xb = " << xb << ", yb = " << yb << Qt::endl;
    qDebug() << "xc = " << xc << ", yc = " << yc << Qt::endl;
    qDebug() << "***************************************" << Qt::endl;
    qDebug() << "vo1x = " << vo1x << ", vo1y = " << vo1y << ", vo1 = " << vo1 << Qt::endl;
    qDebug() << "vax = " << vax << ", vay = " << vay << ", va = " << va << Qt::endl;
    qDebug() << "vbx = " << vbx << ", vby = " << vby << ", vb = " << vb << Qt::endl;
    qDebug() << "vcx = " << vcx << ", vcy = " << vcy << ", vc = " << vc << Qt::endl;
    qDebug() << "***************************************" << Qt::endl;
    qDebug() << "ao1x = " << ao1x << ", ao1y = " << ao1y << ", ao1 = " << ao1 << Qt::endl;
    qDebug() << "aax = " << aax << ", aay = " << aay << ", aa = " << aa << Qt::endl;
    qDebug() << "abx = " << abx << ", aby = " << aby << ", ab = " << ab << Qt::endl;
    qDebug() << "acx = " << acx << ", acy = " << acy << ", ac = " << ac << Qt::endl;
    qDebug() << "***************************************" << Qt::endl;
    qDebug() << "xmax = " << xmax << ", xmin = " << xmin
             << ", ymax = " << ymax << ", ymin = " << ymin
             << ", xmid = " << xmid << ", ymid = " << ymid
             << ", arat = " << arat << Qt::endl;
    qDebug() << "***************************************" << Qt::endl;

}




//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~МУСОР~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

//void Slider_crank_linkage::CoordRotat2(double xo1, double yo1, double xo2, double yo2,
//                                       double l1, double l2, double l3,
//                                       double xc2, double yc2, Slider_crank_linkage::orientation_l k, //испавила ух2
//                                       QVector<double>& xapic, QVector<double>& yapic, QVector<double>& xbpic, QVector<double>& ybpic,
//                                       int N,
//                                       bool &boolvalue)
//{
//    double fi, fi2; //в оригнале еще fi3 который не используется. зачем он?
//    double xa, ya, xb, yb, xc, yc;
//    // В оригинале тут есть еще ind. Я добавлять не стала
//    QVec3tor<double> xcpic, ycpic; //где они в оригинале?

//    boolvalue = false;
//    for (int i = 0; i < N; i++) {
//        fi = i*2*M_PI/N;
//        coord0(xo1, yo1, l1, 0, fi, xa, ya);
//        coord2(xa, ya, l2, this->al, this->xl, this->yl, k, fi2, this->ind);
//        if (this->ind > 0) {
//            boolvalue = true;
//            return;
//        }
//        coord0(xa, ya, l2, 0, fi2, xb, yb);
//        coord0(xa, ya, xc2, yc2, fi2, xc, yc);
//        xapic.append(xa);
//        yapic.append(ya);
//        xbpic.append(xb);
//        ybpic.append(yb);
//        xcpic.append(xc);
//        ycpic.append(yc);
//    } //посмотреть оригинал, т к тут непнятные скобочки
//}
