#include "double_slider_crank_linkage.h"
#include "value.h"
#include "mechanism_2.h"
#include "plot_2.h"

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
#include <QtMath>
#include <QDebug>

Double_slider_crank_linkage::Double_slider_crank_linkage(QWidget *parent) : QWidget(parent)
{
    //задаем размеры
//    QPoint center = ((QGuiApplication::primaryScreen())->geometry()).center();
//    this->setGeometry(center.x()/3, center.y()/3,
//                      ((QGuiApplication::primaryScreen())->geometry()).width()/2,
//                      ((QGuiApplication::primaryScreen())->geometry()).height()/2);

    font = QFont("Purisa", 11);

    initial_value();                //задаем начальные значения
    create_values();                //создаем окошки входных и выходных данных'
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
    create_mechanism();

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

//    connect(inv->fi1g_value->lineEdit, &QLineEdit::textChanged, this, &Double_slider_crank_linkage::_fi1g_changed);
//    connect(inv->l3_value->lineEdit, &QLineEdit::textChanged, this, &Double_slider_crank_linkage::_l3_changed);
//    connect(inv->l1_value->lineEdit, &QLineEdit::textChanged, this, &Double_slider_crank_linkage::_l1_changed);
//    connect(inv->l2_value->lineEdit, &QLineEdit::textChanged, this, &Double_slider_crank_linkage::_l2_changed);
//    connect(inv->xo2_value->lineEdit, &QLineEdit::textChanged, this, &Double_slider_crank_linkage::_xo2_changed);
//    connect(inv->yo2_value->lineEdit, &QLineEdit::textChanged, this, &Double_slider_crank_linkage::_yo2_changed);
//    connect(inv->xc2_value->lineEdit, &QLineEdit::textChanged, this, &Double_slider_crank_linkage::_xc2_changed);
//    connect(inv->yc2_value->lineEdit, &QLineEdit::textChanged, this, &Double_slider_crank_linkage::_yc2_changed);
//    connect(inv->om1_value->lineEdit, &QLineEdit::textChanged, this, &Double_slider_crank_linkage::_om1_changed);
//    connect(inv->ep1_value->lineEdit, &QLineEdit::textChanged, this, &Double_slider_crank_linkage::_ep1_changed);
//    connect(inv->xo1_value->lineEdit, &QLineEdit::textChanged, this, &Double_slider_crank_linkage::_xo1_changed);
//    connect(inv->yo1_value->lineEdit, &QLineEdit::textChanged, this, &Double_slider_crank_linkage::_yo1_changed);
//    connect(inv->vo1x_value->lineEdit, &QLineEdit::textChanged, this, &Double_slider_crank_linkage::_vo1x_changed);
//    connect(inv->vo1y_value->lineEdit, &QLineEdit::textChanged, this, &Double_slider_crank_linkage::_vo1y_changed);
//    connect(inv->ao1x_value->lineEdit, &QLineEdit::textChanged, this, &Double_slider_crank_linkage::_ao1x_changed);
//    connect(inv->ao1y_value->lineEdit, &QLineEdit::textChanged, this, &Double_slider_crank_linkage::_ao1y_changed);
//    connect(inv->k_comboBox, &QComboBox::currentTextChanged, this, &Double_slider_crank_linkage::_k_changed);
    connect(calculate, &QPushButton::clicked, this, &Double_slider_crank_linkage::_correct_calculation);
    connect(SAstatus->vo1, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Double_slider_crank_linkage::_status_vo1_changed);
    connect(SAstatus->ao1, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Double_slider_crank_linkage::_status_ao1_changed);
    connect(SAstatus->va, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Double_slider_crank_linkage::_status_va_changed);
    connect(SAstatus->aa, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Double_slider_crank_linkage::_status_aa_changed);
    connect(SAstatus->vb, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Double_slider_crank_linkage::_status_vb_changed);
    connect(SAstatus->ab, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Double_slider_crank_linkage::_status_ab_changed);
    connect(SAstatus->vc, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Double_slider_crank_linkage::_status_vc_changed);
    connect(SAstatus->ac, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Double_slider_crank_linkage::_status_ac_changed);
    connect(SAstatus->vo2, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Double_slider_crank_linkage::_status_vo2_changed);
    connect(SAstatus->ao2, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Double_slider_crank_linkage::_status_ao2_changed);
    connect(pause_or_play, &QToolButton::clicked, this, &Double_slider_crank_linkage::_slot_pause_or_play);
    connect(mechanism_or_graphic, &QPushButton::clicked, this, &Double_slider_crank_linkage::_slot_mechanism_or_graphic);
    connect(mechanism->timer, &QTimer::timeout, this, &Double_slider_crank_linkage::_auto_rotate_mechanism);
}

void Double_slider_crank_linkage::initial_value()
{
    fi1g = 90;
    l1 = 10;
    l2 = 20;
    l3 = 40;
    xo2 = -30;
    yo2 = -7.1;
    k = Constants::left;
    xc2 = 15;
    yc2 = 0;
    om1 = 2;
    ep1 = 2;
    xo1 = 0;
    yo1 = 0;
    vo1x = 0;
    vo1y = 0;
    ao1x = 0;
    ao1y = 0;
}

void Double_slider_crank_linkage::create_values()
{
    inv = new InputValues2();
    outv = new OutputValues2();
    SAstatus = new SpeedAccelStatus2();

    inv->setFont(font);
    outv->setFont(font);
    SAstatus->setFont(font);
}

void Double_slider_crank_linkage::create_mechanism()
{
    mechanism = new Mechanism_2(font, l1, l2, l3, xa, ya, xb, yb, xo2, yo2,
                                xc, yc, xc2, yc2,
                                fi1g, fi2g, fi3g,
                                xmin, ymin, xmax, ymax, xo1, yo1);
    mechanism->changeAccelStatusO1(Constants::SHOWNOTHINGACCEL);
    mechanism->changeSpeedStatusO1(Constants::SHOWNOTHINGSPEED);
    mechanism->changeAccelStatusB(Constants::SHOWNOTHINGACCEL);
    mechanism->changeSpeedStatusB(Constants::SHOWNOTHINGSPEED);
    mechanism->changeAccelStatusA(Constants::SHOWNOTHINGACCEL);
    mechanism->changeSpeedStatusA(Constants::SHOWNOTHINGSPEED);
    mechanism->changeAccelStatusC(Constants::SHOWA);
    mechanism->changeSpeedStatusC(Constants::SHOWV);
    mechanism->changeAccelStatusO2(Constants::SHOWNOTHINGACCEL);
    mechanism->changeSpeedStatusO2(Constants::SHOWNOTHINGSPEED);
    mechanism->setSpeedForPointC(vcx, vcy, vc);
    mechanism->setAccelForPointC(acx, acy, ac);
}

void Double_slider_crank_linkage::create_plot()
{
    plot = new Plot_2;
    plot->customPlot->setFont(font);
    plot->setColorO1(mechanism->getColorO1());
    plot->setColorA(mechanism->getColorA());
    plot->setColorB(mechanism->getColorB());
    plot->setColorC(mechanism->getColorC());
    plot->setColorO2(mechanism->getColorO2());
    plot->changedSpeedStatusO1(mechanism->getCurrentSpeedStatusO1());
    plot->changedSpeedStatusA(mechanism->getCurrentSpeedStatusA());
    plot->changedSpeedStatusB(mechanism->getCurrentSpeedStatusB());
    plot->changedSpeedStatusC(mechanism->getCurrentSpeedStatusC());
    plot->changedSpeedStatusO2(mechanism->getCurrentSpeedStatusO2());
    plot->changedAccelStatusO1(mechanism->getCurrentAccelStatusO1());
    plot->changedAccelStatusA(mechanism->getCurrentAccelStatusA());
    plot->changedAccelStatusB(mechanism->getCurrentAccelStatusB());
    plot->changedAccelStatusC(mechanism->getCurrentAccelStatusC());
    plot->changedAccelStatusO2(mechanism->getCurrentAccelStatusO2());

    plot->hide();
}

void Double_slider_crank_linkage::change_output_values()
{
    outv->_fiO1Ag_change(fi1g);
    outv->_fiABg_change(fi2g);
    outv->_fiBO2g_change(fi3g);
    outv->_omO1A_change(om1);
    outv->_omAB_change(om2);
    outv->_omBO2_change(om3);
    outv->_epO1A_change(ep1);
    outv->_epAB_change(ep2);
    outv->_epBO2_change(ep3);
    outv->_xO1_change(xo1);
    outv->_yO1_change(yo1);
    outv->_xA_change(xa);
    outv->_yA_change(ya);
    outv->_xB_change(xb);
    outv->_yB_change(yb);
    outv->_xC_change(xc);
    outv->_yC_change(yc);
    outv->_xO2_change(xo2);
    outv->_yO2_change(yo2);
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
    outv->_vxO2_change(vo2x);
    outv->_vyO2_change(vo2y);
    outv->_vO2_change(vo2);
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
    outv->_axO2_change(ao2x);
    outv->_ayO2_change(ao2y);
    outv->_aO2_change(ao2);
}

void Double_slider_crank_linkage::change_mechanism()
{
    mechanism->setLengthO1A(l1);
    mechanism->setLengthAB(l2);
    mechanism->setLengthBO2(l3);
    mechanism->setOrientation(k);
    qDebug() << " fi2g = " << fi2g << ", fi3g = " << fi3g << Qt::endl;
    mechanism->change_position(xa, ya, xb, yb, xc, yc, fi1g, fi2g, fi3g, xo1, yo1);
    mechanism->setPointO2(xo2, yo2);
    mechanism->setPointC(xc2, yc2);
    mechanism->setRamka(xmin, ymin, xmax, ymax);
    mechanism->setSpeedForPointO1(vo1x, vo1y, vo1);
    mechanism->setAccelForPointO1(ao1x, ao1y, ao1);
    mechanism->setSpeedForPointO2(vo2x, vo2y, vo2);
    mechanism->setAccelForPointO2(ao2x, ao2y, ao2);
    mechanism->setSpeedForPointA(vax, vay, va);
    mechanism->setSpeedForPointB(vbx, vby, vb);
    mechanism->setSpeedForPointC(vcx, vcy, vc);
    mechanism->setAccelForPointA(aax, aay, aa);
    mechanism->setAccelForPointB(abx, aby, ab);
    mechanism->setAccelForPointC(acx, acy, ac);
    mechanism->change_rect();
}

void Double_slider_crank_linkage::change_plot()
{
    plot->_restart(fi1g, vo1x, vo1y, vo1, ao1x, ao1y, ao1,
                   vax, vay, va, aax, aay, aa,
                   vbx, vby, vb, abx, aby, ab,
                   vcx, vcy, vc, acx, acy, ac,
                   vo2x, vo2y, vo2, ao2x, ao2y, ao2);
}

void Double_slider_crank_linkage::_correct_calculation()
{
    fi1g = inv->fi1g_value->lineEdit->text().toDouble();
    l1 = inv->l1_value->lineEdit->text().toDouble();
    l2 = inv->l2_value->lineEdit->text().toDouble();
    l3 = inv->l3_value->lineEdit->text().toDouble();
    xo2 = inv->xo2_value->lineEdit->text().toDouble();
    yo2 = inv->yo2_value->lineEdit->text().toDouble();
    if (inv->k_comboBox->currentText() == QString("right"))
        k = Constants::orientation_l::right;
    else
        k = Constants::orientation_l::left;
    xc2 = inv->xc2_value->lineEdit->text().toDouble();
    yc2 = inv->yc2_value->lineEdit->text().toDouble();
    om1 = inv->om1_value->lineEdit->text().toDouble();
    ep1 = inv->ep1_value->lineEdit->text().toDouble();
    xo1 = inv->xo1_value->lineEdit->text().toDouble();
    yo1 = inv->yo1_value->lineEdit->text().toDouble();
    vo1x = inv->vo1x_value->lineEdit->text().toDouble();
    vo1y = inv->vo1y_value->lineEdit->text().toDouble();
    ao1x = inv->ao1x_value->lineEdit->text().toDouble();
    ao1y = inv->ao1y_value->lineEdit->text().toDouble();
    Calculation();
    qDebug() << "ind = " << ind << Qt::endl;
    if (ind == 0) {
        change_output_values();
        change_mechanism();
        change_plot();
    } else if (ind == 1) {
        current_stats_pause_or_play =  Constants::PAUSE;
        pause_or_play->setIcon(play);
        mechanism->_stop_timer();
        QMessageBox::warning(this, tr("Error"), QString(tr("Error's type is first.")), QMessageBox::Ok);
        mechanism->incorrect_datas();
        plot->incorrect_datas();
    } else if (ind == 2) {
        current_stats_pause_or_play =  Constants::PAUSE;
        pause_or_play->setIcon(play);
        mechanism->_stop_timer();
        QMessageBox::warning(this, tr("Error"), QString(tr("Error's type is second.")), QMessageBox::Ok);
        mechanism->incorrect_datas();
        plot->incorrect_datas();
    }
}

//void Double_slider_crank_linkage::_fi1g_changed(const QString &text)
//{
//    fi1g = text.toDouble();
//    if (data == Constants::OLD)
//        data = Constants::NEW;
//}

//void Double_slider_crank_linkage::_l1_changed(const QString &text)
//{
//    l1 = text.toDouble();
//    if (data == Constants::OLD)
//        data = Constants::NEW;
//}

//void Double_slider_crank_linkage::_l2_changed(const QString &text)
//{
//    l2 = text.toDouble();
//    if (data == Constants::OLD)
//        data = Constants::NEW;
//}

//void Double_slider_crank_linkage::_l3_changed(const QString &text)
//{
//    l3 = text.toDouble();
//    if (data == Constants::OLD)
//        data = Constants::NEW;
//}

//void Double_slider_crank_linkage::_xo2_changed(const QString &text)
//{
//    xo2 = text.toDouble();
//    if (data == Constants::OLD)
//        data = Constants::NEW;
//}

//void Double_slider_crank_linkage::_yo2_changed(const QString &text)
//{
//    yo2 = text.toDouble();
//    if (data == Constants::OLD)
//        data = Constants::NEW;
//}

//void Double_slider_crank_linkage::_xc2_changed(const QString &text)
//{
//    xc2 = text.toDouble();
//    if (data == Constants::OLD)
//        data = Constants::NEW;
//}

//void Double_slider_crank_linkage::_yc2_changed(const QString &text)
//{
//    yc2 = text.toDouble();
//    if (data == Constants::OLD)
//        data = Constants::NEW;
//}

//void Double_slider_crank_linkage::_om1_changed(const QString &text)
//{
//    om1 = text.toDouble();
//    if (data == Constants::OLD)
//        data = Constants::NEW;
//}

//void Double_slider_crank_linkage::_ep1_changed(const QString &text)
//{
//    ep1 = text.toDouble();
//    if (data == Constants::OLD)
//        data = Constants::NEW;
//}

//void Double_slider_crank_linkage::_xo1_changed(const QString &text)
//{
//    xo1 = text.toDouble();
//    if (data == Constants::OLD)
//        data = Constants::NEW;
//}

//void Double_slider_crank_linkage::_yo1_changed(const QString &text)
//{
//    yo1 = text.toDouble();
//    if (data == Constants::OLD)
//        data = Constants::NEW;
//}

//void Double_slider_crank_linkage::_vo1x_changed(const QString &text)
//{
//    vo1x = text.toDouble();
//    if (data == Constants::OLD)
//        data = Constants::NEW;
//}

//void Double_slider_crank_linkage::_vo1y_changed(const QString &text)
//{
//    vo1y = text.toDouble();
//    if (data == Constants::OLD)
//        data = Constants::NEW;
//}

//void Double_slider_crank_linkage::_ao1x_changed(const QString &text)
//{
//    ao1x = text.toDouble();
//    if (data == Constants::OLD)
//        data = Constants::NEW;
//}

//void Double_slider_crank_linkage::_ao1y_changed(const QString &text)
//{
//    ao1y = text.toDouble();
//    if (data == Constants::OLD)
//        data = Constants::NEW;
//}

//void Double_slider_crank_linkage::_k_changed(const QString &text)
//{
//    if (text == QString("right"))
//        k = Constants::orientation_l::right;
//    else
//        k = Constants::orientation_l::left;
//    if (data == Constants::OLD)
//        data = Constants::NEW;
//}

void Double_slider_crank_linkage::_status_vo1_changed(const int index)
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

void Double_slider_crank_linkage::_status_ao1_changed(const int index)
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

void Double_slider_crank_linkage::_status_va_changed(const int index)
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

void Double_slider_crank_linkage::_status_aa_changed(const int index)
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

void Double_slider_crank_linkage::_status_vb_changed(const int index)
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

void Double_slider_crank_linkage::_status_ab_changed(const int index)
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

void Double_slider_crank_linkage::_status_vc_changed(const int index)
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

void Double_slider_crank_linkage::_status_ac_changed(const int index)
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

void Double_slider_crank_linkage::_status_vo2_changed(const int index)
{
        if (index == 0) {
            mechanism->changeSpeedStatusO2(Constants::SHOWV);
            plot->changedSpeedStatusO2(Constants::SHOWV);
        } else if (index == 1) {
            mechanism->changeSpeedStatusO2(Constants::SHOWVX);
            plot->changedSpeedStatusO2(Constants::SHOWVX);
        } else if (index == 2) {
            mechanism->changeSpeedStatusO2(Constants::SHOWVY);
            plot->changedSpeedStatusO2(Constants::SHOWVY);
        } else if (index == 3) {
            mechanism->changeSpeedStatusO2(Constants::SHOWVXV);
            plot->changedSpeedStatusO2(Constants::SHOWVXV);
        } else if (index == 4) {
            mechanism->changeSpeedStatusO2(Constants::SHOWVYV);
            plot->changedSpeedStatusO2(Constants::SHOWVYV);
        } else if (index == 5) {
            mechanism->changeSpeedStatusO2(Constants::SHOWVXY);
            plot->changedSpeedStatusO2(Constants::SHOWVXY);
        } else if (index == 6) {
            mechanism->changeSpeedStatusO2(Constants::SHOWSPEED);
            plot->changedSpeedStatusO2(Constants::SHOWSPEED);
        } else {
            mechanism->changeSpeedStatusO2(Constants::SHOWNOTHINGSPEED);
            plot->changedSpeedStatusO2(Constants::SHOWNOTHINGSPEED);
        }
}

void Double_slider_crank_linkage::_status_ao2_changed(const int index)
{
        if (index == 0) {
            mechanism->changeAccelStatusO2(Constants::SHOWA);
            plot->changedAccelStatusO2(Constants::SHOWA);
        } else if (index == 1) {
            mechanism->changeAccelStatusO2(Constants::SHOWAX);
            plot->changedAccelStatusO2(Constants::SHOWAX);
        } else if (index == 2) {
            mechanism->changeAccelStatusO2(Constants::SHOWAY);
            plot->changedAccelStatusO2(Constants::SHOWAY);
        } else if (index == 3) {
            mechanism->changeAccelStatusO2(Constants::SHOWAXA);
            plot->changedAccelStatusO2(Constants::SHOWAXA);
        } else if (index == 4) {
            mechanism->changeAccelStatusO2(Constants::SHOWAYA);
            plot->changedAccelStatusO2(Constants::SHOWAYA);
        } else if (index == 5) {
            mechanism->changeAccelStatusO2(Constants::SHOWAXY);
            plot->changedAccelStatusO2(Constants::SHOWAXY);
        } else if (index == 6) {
            mechanism->changeAccelStatusO2(Constants::SHOWACCEL);
            plot->changedAccelStatusO2(Constants::SHOWACCEL);
        } else {
            mechanism->changeAccelStatusO2(Constants::SHOWNOTHINGACCEL);
            plot->changedAccelStatusO2(Constants::SHOWNOTHINGACCEL);
        }
}

void Double_slider_crank_linkage::_auto_rotate_mechanism()
{
    if (ind == 0) {
        double _fi1g = - mechanism->getfi1();
//        double _l1 = mechanism->getLengthO1A();
//        double _l2 = mechanism->getLengthAB();
//        double _l3 = mechanism->getLengthBO2();
//        double _xo1 = mechanism->getXO1();
//        double _yo1 = - mechanism->getYO1();
//        double _xo2 = mechanism->getXO2();
//        double _yo2 = - mechanism->getYO2();
//        double _xc2 = mechanism->getXc2();
//        double _yc2 = - mechanism->getYc2();
//        double _om1 = mechanism->getOm1();
//        double _ep1 = mechanism->getEp1();
//        double _vo1x = mechanism->getVO1x();
//        double _vo1y = mechanism->getVO1y();
//        double _ao1x = mechanism->getAO1x();
//        double _ao1y = mechanism->getAO1y();

        double _fi1, _fi2, _fi2g, _fi3, _fi3g;
        double _xa, _ya, _xb, _yb, _xc, _yc;
        double _vax, _vay, _va, _vcx, _vcy, _vc, _vbx, _vby, _vb;
        double _aax, _aay, _aa, _acx, _acy, _ac, _abx, _aby, _ab;
        double _om2, _ep2, _om3, _ep3;
        double _xmax, _xmin, _ymax, _ymin, _xmid, _ymid, _arat;
        types _ind = type_first;
        //Constants::orientation_l _k = mechanism->getOrientation();
        _fi1g++;


        _fi1 = Constants::from_degrees_to_radians(_fi1g);
        Constants::coord0(xo1, yo1, l1, 0, _fi1, _xa, _ya);            //получаем xa, ya
        coord2(_xa, _ya, xo2, yo2, l2, l3, k, _fi2, _fi3, _ind);         //получаем fi2, fi3, ind
        _fi2g = Constants::from_radians_to_degrees(_fi2);
        _fi3g = Constants::from_radians_to_degrees(_fi3);
        if (_ind > 0) {
            current_stats_pause_or_play = Constants::PAUSE;
            pause_or_play->setIcon(play);
            mechanism->_stop_timer();
            QMessageBox::warning(this, tr("Error"), QString(tr("An error occurred while modelling")), QMessageBox::Ok); //Произошла ошибка при моделировании
            return;
        }
        Constants::coord0(_xa, _ya, l2, 0, _fi2, _xb, _yb);              //получаем xb, yb
        Constants::coord0(_xa, _ya, xc2, yc2, _fi2, _xc, _yc);           //получаем xc, yc
        Constants::speed0(vo1x, vo1y, om1, l1, 0, _fi1, _vax, _vay, _va);   //получаем vax, vay, va
        double _vo2x = 0;
        double _vo2y = 0;
        speed2(_vax, _vay, _vo2x, _vo2y, l2, l3, _fi2, _fi3, _om2, _om3, _ind);  //получаем om2, om3, ind
        if (_ind > 0) {
            current_stats_pause_or_play = Constants::PAUSE;
            pause_or_play->setIcon(play);
            mechanism->_stop_timer();
            QMessageBox::warning(this, tr("Error"), QString(tr("An error occurred while modelling")), QMessageBox::Ok);
            return;
        }
        Constants::speed0(_vax, _vay, _om2, xc2, yc2, _fi2, _vcx, _vcy, _vc);  //получаем vcx, vcy, vc
        Constants::speed0(_vax, _vay, _om2, l2, 0, _fi2, _vbx,  _vby, _vb);     //получаем vbx, vby, vb
        Constants::accel0(ao1x, ao1y, om1, ep1, l1, 0, _fi1, _aax, _aay, _aa);  //получаем  aax, aay, aa
        double _ao2x = 0;
        double _ao2y = 0;
        accel2(_aax, _aay, _ao2x, _ao2y, _fi2, _fi3, l2, l3, _om2, _om3, _ep2, _ep3, _ind);    //получаем ep2, ep3, ind
        if (_ind > 0) {
            current_stats_pause_or_play =  Constants::PAUSE;
            pause_or_play->setIcon(play);
            mechanism->_stop_timer();
            QMessageBox::warning(this, tr("Error"), QString(tr("An error occurred while modelling")), QMessageBox::Ok);
            return;
        }
        Constants::accel0(_aax, _aay, _om2, _ep2, xc2, yc2, _fi2, _acx, _acy, _ac);  //получаем acx, acy, ac
        Constants::accel0(_aax, _aay, _om2, _ep2, l2, 0, _fi2, _abx, _aby, _ab);     //получаем abx, aby, ab
        Ramka2(xo1, yo1, xo2, yo2, l1, l2, l3, xc2, yc2,
               k, _xmax, _xmin, _ymax, _ymin, _xmid, _ymid, _arat);        //получаем xmax, xmin, ymax, ymin, xmid, ymid, arat

        mechanism->change_position(_xa, _ya, _xb, _yb, _xc, _yc,
                                   _fi1g, _fi2g, _fi3g,
                                   xo1, yo1);
        mechanism->setRamka(_xmin, _ymin, _xmax, _ymax);
        mechanism->setSpeedForPointA(_vax, _vay, _va);
        mechanism->setSpeedForPointB(_vbx, _vby, _vb);
        mechanism->setSpeedForPointC(_vcx, _vcy, _vc);
        mechanism->setAccelForPointA(_aax, _aay, _aa);
        mechanism->setAccelForPointB(_abx, _aby, _ab);
        mechanism->setAccelForPointC(_acx, _acy, _ac);

        double _vo1 = qSqrt(vo1x*vo1x + vo1y*vo1y);
        double _ao1 = qSqrt(ao1x*ao1x + ao1y*ao1y);

        plot->_add_points(_fi1g, vo1x, vo1y, _vo1, ao1x, ao1y, _ao1,
                          _vax, _vay, _va, _aax, _aay, _aa,
                          _vbx, _vby, _vb, _abx, _aby, _ab,
                          _vcx, _vcy, _vc, _acx, _acy, _ac,
                          _vo2x, _vo2y, 0, _ao2x, _ao2y, 0);
    } else {
        current_stats_pause_or_play =  Constants::PAUSE;
        pause_or_play->setIcon(play);
        mechanism->_stop_timer();
        mechanism->incorrect_datas();
    }
}

void Double_slider_crank_linkage::_slot_pause_or_play()
{
    if (current_stats_pause_or_play == Constants::PLAY) {
        current_stats_pause_or_play =  Constants::PAUSE;
        pause_or_play->setIcon(play);
        mechanism->_stop_timer();
    } else {
        current_stats_pause_or_play =  Constants::PLAY;
        pause_or_play->setIcon(pause);
        mechanism->_start_timer();
    }
}

void Double_slider_crank_linkage::_slot_mechanism_or_graphic()
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

void Double_slider_crank_linkage::Calculation()
{
    fi1 = Constants::from_degrees_to_radians(fi1g);
    Constants::coord0(xo1, yo1, l1, 0, fi1, xa, ya);            //получаем xa, ya
    coord2(xa, ya, xo2, yo2, l2, l3, k, fi2, fi3, ind);         //получаем fi2, fi3, ind
    fi2g = Constants::from_radians_to_degrees(fi2);
    fi3g = Constants::from_radians_to_degrees(fi3);
    if (ind > 0) return;
    Constants::coord0(xa, ya, l2, 0, fi2, xb, yb);              //получаем xb, yb
    Constants::coord0(xa, ya, xc2, yc2, fi2, xc, yc);           //получаем xc, yc
    Constants::speed0(vo1x, vo1y, om1, l1, 0, fi1, vax, vay, va);   //получаем vax, vay, va
    vo2x = 0;
    vo2y = 0;
    speed2(vax, vay, vo2x, vo2y, l2, l3, fi2, fi3, om2, om3, ind);  //получаем om2, om3, ind
    if (ind > 0) return;;
    Constants::speed0(vax, vay, om2, xc2, yc2, fi2, vcx, vcy, vc);  //получаем vcx, vcy, vc
    Constants::speed0(vax, vay, om2, l2, 0, fi2, vbx, vby, vb);     //получаем vbx, vby, vb
    Constants::accel0(ao1x, ao1y, om1, ep1, l1, 0, fi1, aax, aay, aa);  //получаем  aax, aay, aa
    ao2x = 0;
    ao2y = 0;
    accel2(aax, aay, ao2x, ao2y, fi2, fi3, l2, l3, om2, om3, ep2, ep3, ind);    //получаем ep2, ep3, ind
    if (ind > 0) return;
    Constants::accel0(aax, aay, om2, ep2, xc2, yc2, fi2, acx, acy, ac);  //получаем acx, acy, ac
    Constants::accel0(aax, aay, om2, ep2, l2, 0, fi2, abx, aby, ab);     //получаем abx, aby, ab
    Ramka2(xo1, yo1, xo2, yo2, l1, l2, l3, xc2, yc2,
           k, xmax, xmin, ymax, ymin, xmid, ymid, arat);        //получаем xmax, xmin, ymax, ymin, xmid, ymid, arat
    vo1 = qSqrt(vo1x*vo1x + vo1y*vo1y);
    ao1 = qSqrt(ao1x*ao1x + ao1y*ao1y);
    vo2 = 0;
    ao2 = 0;

    qDebug() << "***************************************" << Qt::endl;
    qDebug() << "fi1g = " << fi1g << ", fi2g = " << fi2g << ", fi3 = " << fi3g << Qt::endl;
    qDebug() << "om1 = " << om1 << ", om2 = " << om2 << ", om3 = " << om3 << Qt::endl;
    qDebug() << "ep1 = " << ep1 << ", ep2 = " << ep2 << ", ep3 = " << ep3 << Qt::endl;
    qDebug() << "***************************************" << Qt::endl;
    qDebug() << "xo1 = " << xo1 << ", yo1 = " << yo1 << Qt::endl;
    qDebug() << "xo2 = " << xo2 << ", yo2 = " << yo2 << Qt::endl;
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

void Double_slider_crank_linkage::coord2(double xa, double ya, double xc, double yc,
                                         double l1, double l2,
                                         Constants::orientation_l k,
                                         double &fi1, double &fi2,
                                         Double_slider_crank_linkage::types &ind)
{
    double ta, al, ac2, ac, l12, cua, cuc;
    ind = type_first;

    if (qAbs(xc - xa) <= Constants::error)
        (yc > ya) ? al = M_PI_2 : al = -M_PI_2;
    else {
        ta = (yc - ya)/(xc - xa);
        al = qAtan(ta);
        if (xa > xc)
            al += M_PI;
    }

    ac2 = (yc - ya)*(yc - ya) + (xc - xa)*(xc - xa);

    if (qAbs(ac2) <= Constants::error and qAbs(l1 - l2) <= Constants::error)
        ind = type_third;

    if (qAbs(ac2) <= Constants::error and qAbs(l1 - l2) >= Constants::error)
        ind = type_second;

    ac = qSqrt(ac2);
    l12 = l1*l1 - l2*l2;
    cua = (ac2 + l12) / (2 * l1 * ac);
    cuc = (ac2 - l12) / (2 * l2 * ac);

    if (qAbs(cua) > 1 or qAbs(cuc) > 1)
        ind = type_second;

    if (k == Constants::right) {
        fi1 = al + Constants::arccos(cua);
        fi2 = al - Constants::arccos(cuc);
    } else if (k == Constants::left) {
        fi1 = al - Constants::arccos(cua);
        fi2 = al + Constants::arccos(cuc);
    }
}

void Double_slider_crank_linkage::speed2(double vax, double vay, double vcx, double vcy,
                                         double l1, double l2, double fi1, double fi2,
                                         double &om1, double &om2, Double_slider_crank_linkage::types &ind)
{
    double s12, w1, w2, vx, vy;
    ind = type_first;
    s12 = qSin(fi2 - fi1);

    if (qAbs(s12) <= Constants::error)
        ind = type_third;
    vx = vax - vcx;
    vy = vay - vcy;
    w1 = - vx * qCos(fi2) - vy * qSin(fi2);
    w2 =  vx * qCos(fi1) + vy * qSin(fi1);
    om1 = w1 / (l1*s12);
    om2 = w2 / (l2*s12);
}

void Double_slider_crank_linkage::accel2(double aax, double aay, double acx, double acy,
                                         double fi1, double fi2, double l1, double l2, double om1, double om2,
                                         double &ep1, double &ep2, Double_slider_crank_linkage::types &ind)
{
    double s12, c12, wl1, wl2, ax, ay, e1, e2;
    ind = type_first;
    s12 = qSin(fi1 - fi2);
    if (qAbs(s12) <= Constants::error)
        ind = type_third;
    ax  = aax - acx;
    ay  = aay - acy;
    c12 = qCos(fi1 - fi2);
    wl1 = om1 * om1 * l1;
    wl2 = om2 * om2 * l2;
    e1  = ax * qCos(fi2) + ay * qSin(fi2) - wl2 - wl1 * c12;
    ep1 = e1 / (l1*s12);
    e2  = ax * qCos(fi1) + ay * qSin(fi1) - wl1 - wl2 * c12;
    ep2 = -e2 / (l2*s12);
}

void Double_slider_crank_linkage::Ramka2(double xo1, double yo1, double xo2, double yo2, double l1, double l2, double l3, double xc2, double yc2, Constants::orientation_l k, double &xmax, double &xmin, double &ymax, double &ymin, double &xmid, double &ymid, double &arat)
{
    double fi, fi2, fi3; //Зачем тут угол fi3 (см оригнал)
    double xa, ya, xb, yb, xc, yc;
    double xmas[5], ymas[5];
    types kk;

    //double x1al, y1al, x2al, y2al; //Это что-то временное или постоянное?

    xmin = Constants::error;
    ymin = Constants::error;
    xmax = - Constants::error;
    ymax = - Constants::error;

    kk = type_second;

    for (int i = 0; i < 7; i++) {
        fi = i * M_PI_4;
        Constants::coord0(xo1, yo1, l1, 0, fi, xa, ya);
        coord2(xa, ya, xo2, yo2, l2, l3, k, fi2, fi3, ind);
        if (ind == type_first)
            kk = type_first;
        if (ind != type_first)
            return;
        Constants::coord0(xa, ya, l2, 0, fi2, xb, yb);
        Constants::coord0(xa, ya, xc2, yc2, fi2, xc, yc);
        xmas[0] = xo1;
        xmas[1] = xa;
        xmas[2] = xb;
        xmas[3] = xc;
        xmas[4] = xo2;
        ymas[0] = yo1;
        ymas[1] = ya;
        ymas[2] = yb;
        ymas[3] = yc;
        ymas[4] = yo2;
        for (int j = 1; j < 5; j++) {
            if (xmas[j] < xmin)
                xmin = xmas[j];
            if (xmas[j] > xmax)
                xmax = xmas[j];
            if (ymas[j] < ymin)
                ymin = ymas[j];
            if (ymas[j] > ymax)
                ymax = ymas[j];
        }

    }    
    xmid = (xmin + xmax)/2;
    ymid = (ymin + ymax)/2;
    if (qAbs(xmax - xmin) > Constants::error)
        arat = (ymax - ymin)/(xmax - xmin);
    else {
        qDebug() << "xmin=xmax, arat indefinite" << Qt::endl;
        arat = 100;
    }
    ind = kk;
}
