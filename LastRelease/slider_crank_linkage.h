#ifndef SLIDER_CRANK_LINKAGE_H
#define SLIDER_CRANK_LINKAGE_H

#include <QWidget>
#include "_constants.h"
#include <QIcon>

QT_BEGIN_NAMESPACE
class InputValues;
class OutputValues;
class SpeedAccelStatus;
class QVBoxLayout;
class QHBoxLayout;
class QLabel;
class QLineEdit;
class QGridLayout;
class QFont;
class QComboBox;
class Image_of_slider_crank_linkage;
class Mechanism_1;
class QToolButton;
class QPushButton;
class Plot;
QT_END_NAMESPACE

class Slider_crank_linkage : public QWidget
{
    Q_OBJECT

public:
    explicit Slider_crank_linkage(QWidget *parent = nullptr);

private:
    enum orientation_l {    //ориентация (int2)
        right = 0,
        left = 1
    };
    enum types {            //флаг ??? (ind2)
        type_first = 0,   //все ок
        type_second = 1,  //
        type_third = 2    //
    };

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Входные значения~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
    double fi1g;            //угол поворта кривошипа в градусах
    double l1, l2, l3;      //длины кривошипа и шатуна
    double alg;             //угол налона прямой, по которой движется ползун, в градусах
    double xl, yl;          //коордиаты точки L, принадлежаещей прямой l
    orientation_l k;        //ориентация механизма
    double xc2, yc2;        //координаты точки шатуна (в системе шатуна) (точка С)
    double om1, ep1;        //угловые скорость и ускорение кривошипа
    double xo1, yo1;        //координаты начала системы отсчета (точка О1)
    double vo1x,vo1y;       //проекции скорости точки начала системы отсчета
    double ao1x,ao1y;       //проекции ускорения точки начала системы отсчета

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Выходные значения~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
    types ind;              //флаг (???)
    double fi1, al;         //углы поворота кривошипа и наклона прямой l в радианах
    double fi2, fi2g;       //угол поворота шатуна относительн оси х в радианах и градусах соответственно
    double om2, ep2;        //угловые скорость и ускорение шатуна
    double xa, ya;          //координаты шарнира, соединяющего кривошип и шатун (точка А)
    double xb, yb;          //координаты ползуна (точка В)
    double xc, yc;          //координаты точки шатуна (в глобальной системе отсчета) (точка С)
    double vo1, ao1;        //полные скорость и ускорение точки начала системы отсчета (точка О1)
    double vax, vay, va;    //скорость и ее проекции точки А
    double vcx, vcy, vc;    //скорость и ее проекции точки С
    double vbx, vby, vb;    //скорость и ее проекции точки В
    double aax, aay, aa;    //ускорение и его проекции точки А
    double acx, acy, ac;    //ускорение и его проекции точки С
    double abx, aby, ab;    //ускорение и его проекции точки В

    double xmax, xmin, ymax, ymin, xmid, ymid, arat;    //крайние размеры для определения размеров рисунка и его масштаба

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Окошки ввода/вывода значений~~~~~~~~~~~~~~~~~~~~~~~~//
private:
    InputValues *inv;
    OutputValues *outv;
    SpeedAccelStatus *SAstatus;
    QHBoxLayout *hbox;
    QVBoxLayout *vbox;
    QFont font;
    Mechanism_1* mechanism;
    Plot *plot;

public:
    QToolButton* pause_or_play;
    QPushButton* mechanism_or_graphic;
    QPushButton* calculate;

private:
    Constants::status_pause_or_play current_stats_pause_or_play = Constants::PAUSE;
    Constants::status_mechanism_or_graphic current_stats_mechanism_or_graphic = Constants::MECHANISM;
    QIcon pause = QIcon(":/pause or play/pause");
    QIcon play = QIcon(":/pause or play/play");
    Constants::On_or_off current_status_on_or_off;


    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Подготовительные этапы~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
private:
    void initial_value();
    void create_values();
    void create_mechanism();
    void create_plot();
    void change_output_values();
    void change_mechanism();
    void change_plot();


private slots:
    void _correct_calculation();
    void _fi1g_changed(const QString &text);
    void _alg_changed(const QString &text);
    void _l1_changed(const QString &text);
    void _l2_changed(const QString &text);
    void _xl_changed(const QString &text);
    void _yl_changed(const QString &text);
    void _xc2_changed(const QString &text);
    void _yc2_changed(const QString &text);
    void _om1_changed(const QString &text);
    void _ep1_changed(const QString &text);
    void _xo1_changed(const QString &text);
    void _yo1_changed(const QString &text);
    void _vo1x_changed(const QString &text);
    void _vo1y_changed(const QString &text);
    void _ao1x_changed(const QString &text);
    void _ao1y_changed(const QString &text);
    void _k_changed(const QString &text);
    void _status_vo1_changed(int index);
    void _status_ao1_changed(const int index);
    void _status_va_changed(const int index);
    void _status_aa_changed(const int index);
    void _status_vb_changed(const int index);
    void _status_ab_changed(const int index);
    void _status_vc_changed(const int index);
    void _status_ac_changed(const int index);


    void _auto_rotate_mechanism();
    void _slot_pause_or_play();
    void _slot_mechanism_or_graphic();

public:
    void _slot_on();
    void _slot_off();

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Вычисления~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
private:
    void Calculation();                                                //Вычисления
    void coord1(double xa, double ya, double l, double al,
                double xl, double yl, orientation_l k,
                double& fi,
                types& ind);                                           //находим углы и флаг, зная координаты
    void speed1(double vax, double vay, double l,
                double al, double fi,
                double& om, types& ind);                               //находим угл. ск. и флаг, зная линейные скорости и угол
    void accel1(double aax, double aay, double l,
                double al, double fi, double om,
                double& ep, types& ind);                               //находим угл. уск. и флаг, зная линейные ускорения, угл. ск. и угол
    void Ramka1(double xo1, double yo1, double xl, double yl,
                double l1, double l2, double al,
                double xc2, double yc2, orientation_l k,
                double& xmax, double& xmin, double& ymax, double& ymin,
                double& xmid, double& ymid, double& arat);             //опредление границ и масштаба рисунка


    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~МУСОР~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//    void CoordRotat2(double xo1, double yo1, double xo2, double yo2,
//                     double l1, double l2, double l3,
//                     double xc2, double yc2, orientation_l k,
//                     QVector<double>& xapic, QVector<double>& yapic, QVector<double>& xbpic, QVector<double>& ybpic,
//                     int N,
//                     bool& boolvalue);


};
#endif // SLIDER_CRANK_LINKAGE_H
