#ifndef DOUBLE_SLIDER_CRANK_LINKAGE_H
#define DOUBLE_SLIDER_CRANK_LINKAGE_H

#include <QWidget>
#include <QIcon>
#include "_constants.h"

QT_BEGIN_NAMESPACE
class InputValues2;
class OutputValues2;
class SpeedAccelStatus2;
class QVBoxLayout;
class QHBoxLayout;
class QLabel;
class QLineEdit;
class QGridLayout;
class QFont;
class QComboBox;
class Mechanism_2;
class QToolButton;
class QPushButton;
class Plot_2;
QT_END_NAMESPACE

class Double_slider_crank_linkage : public QWidget
{
    Q_OBJECT
public:
    explicit Double_slider_crank_linkage(QWidget *parent = nullptr);
private:
    enum types {            //флаг ??? (ind2)
        type_first = 0,   //все ок
        type_second = 1,  //
        type_third = 2    //
    };

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Входные значения~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
    double fi1g;            //угол поворта кривошипа в градусах
    double l1, l2, l3;      //длины кривошипа и шатуна
    Constants::orientation_l k;        //ориентация механизма
    double xc2, yc2;        //координаты точки шатуна (в системе шатуна) (точка С)
    double om1, ep1;        //угловые скорость и ускорение кривошипа
    double xo1, yo1;        //координаты начала системы отсчета (точка О1)
    double xo2, yo2;        //координаты О2
    double vo1x,vo1y;       //проекции скорости точки начала системы отсчета
    double ao1x,ao1y;       //проекции ускорения точки начала системы отсчета

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Выходные значения~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
    types ind;              //флаг (???)
    double fi1;         //углы поворота кривошипа и наклона прямой l в радианах
    double fi2, fi2g;       //угол поворота шатуна относительн оси х в радианах и градусах соответственно
    double fi3, fi3g;
    double om2, ep2;        //угловые скорость и ускорение шатуна
    double om3, ep3;
    double xa, ya;          //координаты шарнира, соединяющего кривошип и шатун (точка А)
    double xb, yb;          //координаты ползуна (точка В)
    double xc, yc;          //координаты точки шатуна (в глобальной системе отсчета) (точка С)
    double vo1, ao1;        //полные скорость и ускорение точки начала системы отсчета (точка О1)
    double vo2x, vo2y, vo2;
    double ao2x, ao2y, ao2;
    double vax, vay, va;    //скорость и ее проекции точки А
    double vcx, vcy, vc;    //скорость и ее проекции точки С
    double vbx, vby, vb;    //скорость и ее проекции точки В
    double aax, aay, aa;    //ускорение и его проекции точки А
    double acx, acy, ac;    //ускорение и его проекции точки С
    double abx, aby, ab;    //ускорение и его проекции точки В

    double xmax, xmin, ymax, ymin, xmid, ymid, arat;    //крайние размеры для определения размеров рисунка и его масштаба

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Окошки ввода/вывода значений~~~~~~~~~~~~~~~~~~~~~~~~//
private:
    InputValues2 *inv;
    OutputValues2 *outv;
    QHBoxLayout *hbox;
    QVBoxLayout *vbox;
    QFont font;
    Mechanism_2* mechanism;
    Plot_2 *plot;

    SpeedAccelStatus2 *SAstatus;

public:
    QToolButton* pause_or_play;
    QPushButton* mechanism_or_graphic;
    QPushButton* calculate;

private:
    Constants::status_pause_or_play current_stats_pause_or_play = Constants::PAUSE;
    Constants::status_mechanism_or_graphic current_stats_mechanism_or_graphic = Constants::MECHANISM;
    QIcon pause = QIcon(":/pause or play/pause");
    QIcon play = QIcon(":/pause or play/play");



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
//    void _fi1g_changed(const QString &text);
//    void _l1_changed(const QString &text);
//    void _l2_changed(const QString &text);
//    void _l3_changed(const QString &text);
//    void _xo2_changed(const QString &text);
//    void _yo2_changed(const QString &text);
//    void _xc2_changed(const QString &text);
//    void _yc2_changed(const QString &text);
//    void _om1_changed(const QString &text);
//    void _ep1_changed(const QString &text);
//    void _xo1_changed(const QString &text);
//    void _yo1_changed(const QString &text);
//    void _vo1x_changed(const QString &text);
//    void _vo1y_changed(const QString &text);
//    void _ao1x_changed(const QString &text);
//    void _ao1y_changed(const QString &text);
//    void _k_changed(const QString &text);
    void _status_vo1_changed(const int index);
    void _status_ao1_changed(const int index);
    void _status_va_changed(const int index);
    void _status_aa_changed(const int index);
    void _status_vb_changed(const int index);
    void _status_ab_changed(const int index);
    void _status_vc_changed(const int index);
    void _status_ac_changed(const int index);
    void _status_vo2_changed(const int index);
    void _status_ao2_changed(const int index);

    void _auto_rotate_mechanism();
    void _slot_pause_or_play();
    void _slot_mechanism_or_graphic();

private:
    void Calculation();                                                //Вычисления
    void coord2(double xa, double ya, double xc, double yc,
                double l1, double l2, Constants::orientation_l k,
                double& fi1, double& fi2,
                types& ind);                                           //находим углы и флаг, зная координаты
    void speed2(double vax, double vay, double vcx, double vcy,
                double l1, double l2, double fi1, double fi2,
                double& om1, double& om2, types& ind);                               //находим угл. ск. и флаг, зная линейные скорости и угол
    void accel2(double aax, double aay, double acx, double acy,
                double fi1, double fi2, double l1, double l2,
                double om1, double om2,
                double& ep1, double& ep2, types& ind);                               //находим угл. уск. и флаг, зная линейные ускорения, угл. ск. и угол
    void Ramka2(double xo1, double yo1, double xo2, double yo2,
                double l1, double l2, double l3,
                double xc2, double yc2, Constants::orientation_l k,
                double& xmax, double& xmin, double& ymax, double& ymin,
                double& xmid, double& ymid, double& arat);
};

#endif // DOUBLE_SLIDER_CRANK_LINKAGE_H
