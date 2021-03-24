#ifndef VALUE_H
#define VALUE_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QLabel;
class QLineEdit;
class QComboBox;
class QString;
class QGridLayout;
class QVBoxLayout;
class InputValues;
class InputValues2;
class Slider_crank_linkage;
class Double_slider_crank_linkage;
QT_END_NAMESPACE

class ValueLineEdit : public QWidget
{
    Q_OBJECT
public:
    explicit ValueLineEdit(QString name, QString value = nullptr, QWidget *parent = nullptr);
private:
    QLabel* label;
    QLineEdit* lineEdit;

    void setFont(QFont font);

    friend InputValues;
    friend InputValues2;
    friend Slider_crank_linkage;
    friend Double_slider_crank_linkage;
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Входные значения~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
class InputValues : public QWidget
{
    Q_OBJECT
public:
    explicit InputValues(QWidget *parent = nullptr);

private:
    enum orientation_l {    //ориентация (int2)
        right = 0,
        left = 1
    };

    ValueLineEdit *fi1g_value, *alg_value, *l1_value, *l2_value,
          *xl_value, *yl_value, *xc2_value, *yc2_value,
          *om1_value, *ep1_value,
          *xo1_value, *yo1_value, *vo1x_value, *vo1y_value, *ao1x_value, *ao1y_value;
    QLabel *title_for_initial_values;
    QLabel *k_label;
    QComboBox *k_comboBox;
    QGridLayout* layout_for_values;

    void setFont(QFont font);
    void createGrid();

    friend Slider_crank_linkage;
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Выходные значения~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
class OutputValues : public QWidget
{
    Q_OBJECT
public:
    explicit OutputValues(QWidget *parent = nullptr);

private:
    QLineEdit *fiO1g_lineEdit, *fiABg_lineEdit, *omO1_lineEdit, *omAB_lineEdit, *epO1_lineEdit, *epAB_lineEdit,
            *xO1_lineEdit, *yO1_lineEdit, *xA_lineEdit, *yA_lineEdit, *xB_lineEdit, *yB_lineEdit, *xC_lineEdit, *yC_lineEdit,
            *vxO1_lineEdit, *vyO1_lineEdit, *vO1_lineEdit, *vxA_lineEdit, *vyA_lineEdit, *vA_lineEdit, *vxB_lineEdit, *vyB_lineEdit, *vB_lineEdit, *vxC_lineEdit, *vyC_lineEdit, *vC_lineEdit,
            *axO1_lineEdit, *ayO1_lineEdit, *aO1_lineEdit, *axA_lineEdit, *ayA_lineEdit, *aA_lineEdit, *axB_lineEdit, *ayB_lineEdit, *aB_lineEdit, *axC_lineEdit, *ayC_lineEdit, *aC_lineEdit;
    QLabel *title_for_output_values, *fi_label, *om_label, *ep_label,
            *O1A_label, *AB_label, *O1_label_1, *A_label_1, *B_label_1, *C_label_1,
            *O1_label_2, *A_label_2, *B_label_2, *C_label_2,
            *O1_label_3, *A_label_3, *B_label_3, *C_label_3,
            *x_label, *y_label, *vx_label, *vy_label, *v_label, *ax_label, *ay_label, *a_label;
    QGridLayout *grid_1, *grid_2, *grid_3, *grid_4;
    QVBoxLayout *vbox;

private:
    void setFont(QFont font);
    void createGrid();

private slots:
    void _fiO1g_change(double value);
    void _fiABg_change(double value);
    void _omO1_change(double value);
    void _omAB_change(double value);
    void _epO1_change(double value);
    void _epAB_change(double value);
    void _xO1_change(double value);
    void _yO1_change(double value);
    void _xA_change(double value);
    void _yA_change(double value);
    void _xB_change(double value);
    void _yB_change(double value);
    void _xC_change(double value);
    void _yC_change(double value);
    void _vxO1_change(double value);
    void _vyO1_change(double value);
    void _vO1_change(double value);
    void _vxA_change(double value);
    void _vyA_change(double value);
    void _vA_change(double value);
    void _vxB_change(double value);
    void _vyB_change(double value);
    void _vB_change(double value);
    void _vxC_change(double value);
    void _vyC_change(double value);
    void _vC_change(double value);
    void _axO1_change(double value);
    void _ayO1_change(double value);
    void _aO1_change(double value);
    void _axA_change(double value);
    void _ayA_change(double value);
    void _aA_change(double value);
    void _axB_change(double value);
    void _ayB_change(double value);
    void _aB_change(double value);
    void _axC_change(double value);
    void _ayC_change(double value);
    void _aC_change(double value);

    friend Slider_crank_linkage;
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Задание статусов скоростей и ускорений~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
class SpeedAccelStatus : public QWidget
{
    Q_OBJECT
public:
    explicit SpeedAccelStatus(QWidget *parent = nullptr);
private:
    QLabel *title, *textO1, *textA, *textB, *textC, *textSpeed, *textAccel;
    QComboBox *vo1, *ao1, *va, *aa, *vb, *ab, *vc, *ac;
    QGridLayout *grid;
    QVBoxLayout *vbox;

    void createSpeedBox(QComboBox *box);
    void createAccelBox(QComboBox *box);
    void setFont(QFont font);
    void createGrid();

    friend Slider_crank_linkage;
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Входные значения~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
class InputValues2 : public QWidget
{
    Q_OBJECT
public:
    explicit InputValues2(QWidget *parent = nullptr);

private:
    enum orientation_l {    //ориентация (int2)
        right = 0,
        left = 1
    };

    ValueLineEdit *fi1g_value, *l1_value, *l2_value, *l3_value,
          *xo2_value, *yo2_value, *xc2_value, *yc2_value,
          *om1_value, *ep1_value,
          *xo1_value, *yo1_value, *vo1x_value, *vo1y_value, *ao1x_value, *ao1y_value;
    QLabel *title_for_initial_values;
    QLabel *k_label;
    QComboBox *k_comboBox;
    QGridLayout* layout_for_values;

    void setFont(QFont font);
    void createGrid();

    friend Double_slider_crank_linkage;
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Выходные значения~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
class OutputValues2 : public QWidget
{
    Q_OBJECT
public:
    explicit OutputValues2(QWidget *parent = nullptr);

private:
    QLineEdit *fiO1Ag_lineEdit, *fiABg_lineEdit, *fiBO2g_lineEdit, *omO1A_lineEdit, *omAB_lineEdit, *omBO2_lineEdit, *epO1A_lineEdit, *epAB_lineEdit, *epBO2_lineEdit,
            *xO1_lineEdit, *yO1_lineEdit, *xA_lineEdit, *yA_lineEdit, *xB_lineEdit, *yB_lineEdit, *xC_lineEdit, *yC_lineEdit, *xO2_lineEdit, *yO2_lineEdit,
            *vxO1_lineEdit, *vyO1_lineEdit, *vO1_lineEdit, *vxA_lineEdit, *vyA_lineEdit, *vA_lineEdit, *vxB_lineEdit, *vyB_lineEdit, *vB_lineEdit, *vxC_lineEdit, *vyC_lineEdit, *vC_lineEdit, *vxO2_lineEdit, *vyO2_lineEdit, *vO2_lineEdit,
            *axO1_lineEdit, *ayO1_lineEdit, *aO1_lineEdit, *axA_lineEdit, *ayA_lineEdit, *aA_lineEdit, *axB_lineEdit, *ayB_lineEdit, *aB_lineEdit, *axC_lineEdit, *ayC_lineEdit, *aC_lineEdit, *axO2_lineEdit, *ayO2_lineEdit, *aO2_lineEdit;
    QLabel *title_for_output_values, *fi_label, *om_label, *ep_label,
            *O1A_label, *AB_label, *BO2_label, *O1_label_1, *A_label_1, *B_label_1, *C_label_1, *O2_label_1,
            *O1_label_2, *A_label_2, *B_label_2, *C_label_2, *O2_label_2,
            *O1_label_3, *A_label_3, *B_label_3, *C_label_3, *O2_label_3,
            *x_label, *y_label, *vx_label, *vy_label, *v_label, *ax_label, *ay_label, *a_label;
    QGridLayout *grid_1, *grid_2, *grid_3, *grid_4;
    QVBoxLayout *vbox;

private:
    void setFont(QFont font);
    void createGrid();

private slots:
    void _fiO1Ag_change(double value);
    void _fiABg_change(double value);
    void _fiBO2g_change(double value);
    void _omO1A_change(double value);
    void _omAB_change(double value);
    void _omBO2_change(double value);
    void _epO1A_change(double value);
    void _epAB_change(double value);
    void _epBO2_change(double value);
    void _xO1_change(double value);
    void _yO1_change(double value);
    void _xA_change(double value);
    void _yA_change(double value);
    void _xB_change(double value);
    void _yB_change(double value);
    void _xC_change(double value);
    void _yC_change(double value);
    void _xO2_change(double value);
    void _yO2_change(double value);
    void _vxO1_change(double value);
    void _vyO1_change(double value);
    void _vO1_change(double value);
    void _vxA_change(double value);
    void _vyA_change(double value);
    void _vA_change(double value);
    void _vxB_change(double value);
    void _vyB_change(double value);
    void _vB_change(double value);
    void _vxC_change(double value);
    void _vyC_change(double value);
    void _vC_change(double value);
    void _vxO2_change(double value);
    void _vyO2_change(double value);
    void _vO2_change(double value);
    void _axO1_change(double value);
    void _ayO1_change(double value);
    void _aO1_change(double value);
    void _axA_change(double value);
    void _ayA_change(double value);
    void _aA_change(double value);
    void _axB_change(double value);
    void _ayB_change(double value);
    void _aB_change(double value);
    void _axC_change(double value);
    void _ayC_change(double value);
    void _aC_change(double value);
    void _axO2_change(double value);
    void _ayO2_change(double value);
    void _aO2_change(double value);

    friend Double_slider_crank_linkage;
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Задание статусов скоростей и ускорений~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
class SpeedAccelStatus2 : public QWidget
{
    Q_OBJECT
public:
    explicit SpeedAccelStatus2(QWidget *parent = nullptr);
private:
    QLabel *title, *textO1, *textA, *textB, *textC, *textO2, *textSpeed, *textAccel;
    QComboBox *vo1, *ao1, *va, *aa, *vb, *ab, *vc, *ac, *vo2, *ao2;
    QGridLayout *grid;
    QVBoxLayout *vbox;

    void createSpeedBox(QComboBox *box);
    void createAccelBox(QComboBox *box);
    void setFont(QFont font);
    void createGrid();

    friend Double_slider_crank_linkage;
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~МУСОР~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

//class ValueComboBox : public QWidget
//{
//    Q_OBJECT

//public:
//    enum orientation_l {    //ориентация (int2)
//        right = 0,
//        left = 1
//    };

//    explicit ValueComboBox(QString name, orientation_l value = right, QWidget *parent = nullptr);
//    QLabel* label;
//    QComboBox* comboBox;

//    void setFont(QFont font);

//};

#endif // VALUE_H
