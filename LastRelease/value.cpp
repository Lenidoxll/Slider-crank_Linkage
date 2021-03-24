#include "value.h"
#include "_constants.h"

#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QString>
#include <QHBoxLayout>
#include <QGridLayout>

ValueLineEdit::ValueLineEdit(QString name, QString value, QWidget *parent) : QWidget(parent)
{
    label = new QLabel(tr("%1").arg(name));
    label->setFont(QFont("Purisa", 11));
    label->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    lineEdit = new QLineEdit(tr("%1").arg(value));
    lineEdit->setFont(QFont("Purisa", 11));
    lineEdit->setAlignment(Qt::AlignLeft);
    label->setBuddy(lineEdit); //Если будет нужно (если будут горячие клавиши)

    lineEdit->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);


    //hbox->setContentsMargins(5, 2, 2, 5);
    //this->setMaximumWidth(this->width()*1.7);
    //setFixedWidth(sizeHint().width());
}

void ValueLineEdit::setFont(QFont font)
{
    label->setFont(font);
    lineEdit->setFont(font);
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~МУСОР~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

//ValueComboBox::ValueComboBox(QString name, orientation_l value, QWidget *parent) : QWidget(parent)
//{
//    label = new QLabel(tr("%1").arg(name));
//    label->setFont(QFont("Purisa", 11));
//    label->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

//    comboBox = new QComboBox(this);

//    comboBox->addItem(tr("right"), orientation_l::right);
//    comboBox->addItem(tr("left"), orientation_l::left);

//    if (value == orientation_l::right)
//        comboBox->setCurrentIndex(0);
//    else
//        comboBox->setCurrentIndex(1);
//    QHBoxLayout* hbox = new QHBoxLayout(this);
//    hbox->addWidget(label, Qt::AlignLeft);
//    hbox->addStretch(1);
//    hbox->addWidget(comboBox, Qt::AlignRight);

////    grid = new QGridLayout(this);
////    grid->addWidget(label, 0, 0);
////    grid->addWidget(comboBox, 1, 0);


//    label->setBuddy(comboBox); //Если будет нужно (если будут горячие клавиши)

//    comboBox->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
//}

//void ValueComboBox::setFont(QFont font)
//{
//    label->setFont(font);
//    comboBox->setFont(font);
//}

InputValues::InputValues(QWidget *parent) : QWidget(parent)
{
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Создаем виджеты~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
    title_for_initial_values = new QLabel(tr("Входные данные  ->"));

    fi1g_value = new ValueLineEdit(QString("fi1g:"), QString("70.0"), this);
    alg_value = new ValueLineEdit(QString("alg:"), QString("70.0"), this);
    l1_value = new ValueLineEdit(QString("l1:"), QString("12"), this);
    l2_value = new ValueLineEdit(QString("l2:"), QString("46"), this);
    xl_value = new ValueLineEdit(QString("xl:"), QString("30"), this);
    yl_value = new ValueLineEdit(QString("yl:"), QString("10"), this);
    xc2_value = new ValueLineEdit(QString("xc2:"), QString("30.666"), this);
    yc2_value = new ValueLineEdit(QString("yc2:"), QString("0"), this);
    om1_value = new ValueLineEdit(QString("om1:"), QString("2"), this);
    ep1_value = new ValueLineEdit(QString("ep1:"), QString("0"), this);
    xo1_value = new ValueLineEdit(QString("xo1:"), QString("0"), this);
    yo1_value = new ValueLineEdit(QString("yo1:"), QString("0"), this);
    vo1x_value = new ValueLineEdit(QString("vo1x:"), QString("0"), this);
    vo1y_value = new ValueLineEdit(QString("vo1y:"), QString("0"), this);
    ao1x_value = new ValueLineEdit(QString("ao1x:"), QString("0"), this);
    ao1y_value = new ValueLineEdit(QString("ao1y:"), QString("0"), this);

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Создаем k_value~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
    k_label = new QLabel(tr("k:"));
    k_label->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

    k_comboBox = new QComboBox();

    k_comboBox->addItem(tr("right"), orientation_l::right);
    k_comboBox->addItem(tr("left"), orientation_l::left);
    k_comboBox->setCurrentIndex(0);

    k_comboBox->setInsertPolicy(QComboBox::InsertBeforeCurrent); //???


    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Создаем grid~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
    layout_for_values = new QGridLayout(this);

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Создаем сетку~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
    createGrid();

}

void InputValues::setFont(QFont font)
{
    title_for_initial_values->setFont(font);

    fi1g_value->setFont(font);
    alg_value->setFont(font);
    l1_value->setFont(font);
    l2_value->setFont(font);
    xl_value->setFont(font);
    yl_value->setFont(font);
    xc2_value->setFont(font);
    yc2_value->setFont(font);
    k_label->setFont(font);
    k_comboBox->setFont(font);
    om1_value->setFont(font);
    ep1_value->setFont(font);
    xo1_value->setFont(font);
    yo1_value->setFont(font);
    vo1x_value->setFont(font);
    vo1y_value->setFont(font);
    ao1x_value->setFont(font);
    ao1y_value->setFont(font);

}

void InputValues::createGrid()
{
    layout_for_values->addWidget(title_for_initial_values, 0, 0, 1, 0);  //title_for_initial_value
    layout_for_values->addWidget(fi1g_value->label, 1, 0);              //fi1g_value
    layout_for_values->addWidget(fi1g_value->lineEdit, 1, 1);
    layout_for_values->addWidget(alg_value->label, 2, 0);               //alg_value
    layout_for_values->addWidget(alg_value->lineEdit, 2, 1);
    layout_for_values->addWidget(l1_value->label, 3, 0);                //l1_value
    layout_for_values->addWidget(l1_value->lineEdit, 3, 1);
    layout_for_values->addWidget(l2_value->label, 4, 0);                //l2_value
    layout_for_values->addWidget(l2_value->lineEdit, 4, 1);
    layout_for_values->addWidget(xl_value->label, 5, 0);                //xl_value
    layout_for_values->addWidget(xl_value->lineEdit, 5, 1);
    layout_for_values->addWidget(yl_value->label, 6, 0);                //yl_value
    layout_for_values->addWidget(yl_value->lineEdit, 6, 1);
    layout_for_values->addWidget(xc2_value->label, 7, 0);               //xc2_value
    layout_for_values->addWidget(xc2_value->lineEdit, 7, 1);
    layout_for_values->addWidget(yc2_value->label, 8, 0);               //yc2_value
    layout_for_values->addWidget(yc2_value->lineEdit, 8, 1);
    layout_for_values->addWidget(k_label, 9, 0);                        //k_label и k_comboBox
    layout_for_values->addWidget(k_comboBox, 9, 1);
    layout_for_values->addWidget(om1_value->label, 10, 0);               //om1_value
    layout_for_values->addWidget(om1_value->lineEdit, 10, 1);
    layout_for_values->addWidget(ep1_value->label, 11, 0);               //ep1_value
    layout_for_values->addWidget(ep1_value->lineEdit, 11, 1);
    layout_for_values->addWidget(xo1_value->label, 12, 0);               //xo1_value
    layout_for_values->addWidget(xo1_value->lineEdit, 12, 1);
    layout_for_values->addWidget(yo1_value->label, 13, 0);               //yo1_value
    layout_for_values->addWidget(yo1_value->lineEdit, 13, 1);
    layout_for_values->addWidget(vo1x_value->label, 14, 0);              //vo1x_value
    layout_for_values->addWidget(vo1x_value->lineEdit, 14, 1);
    layout_for_values->addWidget(vo1y_value->label, 15, 0);              //vo1y_value
    layout_for_values->addWidget(vo1y_value->lineEdit, 15, 1);
    layout_for_values->addWidget(ao1x_value->label, 16, 0);              //ao1x_value
    layout_for_values->addWidget(ao1x_value->lineEdit, 16, 1);
    layout_for_values->addWidget(ao1y_value->label, 17, 0);              //ao1y_value
    layout_for_values->addWidget(ao1y_value->lineEdit, 17, 1);
}

OutputValues::OutputValues(QWidget *parent) : QWidget(parent)
{
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Создаем виджеты~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
    title_for_output_values = new QLabel(tr("Выходные значения  ->"));

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Создаем и настраиваем lineEdit~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
    fiO1g_lineEdit = new QLineEdit;                     //создаем
    fiABg_lineEdit = new QLineEdit;
    omO1_lineEdit = new QLineEdit;
    omAB_lineEdit = new QLineEdit;
    epO1_lineEdit = new QLineEdit;
    epAB_lineEdit = new QLineEdit;
    xO1_lineEdit = new QLineEdit;
    yO1_lineEdit = new QLineEdit;
    xA_lineEdit = new QLineEdit;
    yA_lineEdit = new QLineEdit;
    xB_lineEdit = new QLineEdit;
    yB_lineEdit = new QLineEdit;
    xC_lineEdit = new QLineEdit;
    yC_lineEdit = new QLineEdit;
    vxO1_lineEdit = new QLineEdit;
    vyO1_lineEdit = new QLineEdit;
    vO1_lineEdit = new QLineEdit;
    vxA_lineEdit = new QLineEdit;
    vyA_lineEdit = new QLineEdit;
    vA_lineEdit = new QLineEdit;
    vxB_lineEdit = new QLineEdit;
    vyB_lineEdit = new QLineEdit;
    vB_lineEdit = new QLineEdit;
    vxC_lineEdit = new QLineEdit;
    vyC_lineEdit = new QLineEdit;
    vC_lineEdit = new QLineEdit;
    axO1_lineEdit = new QLineEdit;
    ayO1_lineEdit = new QLineEdit;
    aO1_lineEdit = new QLineEdit;
    axA_lineEdit = new QLineEdit;
    ayA_lineEdit = new QLineEdit;
    aA_lineEdit = new QLineEdit;
    axB_lineEdit = new QLineEdit;
    ayB_lineEdit = new QLineEdit;
    aB_lineEdit = new QLineEdit;
    axC_lineEdit = new QLineEdit;
    ayC_lineEdit = new QLineEdit;
    aC_lineEdit = new QLineEdit;

    fiO1g_lineEdit->setEnabled(false);                      //видимость
    fiABg_lineEdit->setEnabled(false);
    omO1_lineEdit->setEnabled(false);
    omAB_lineEdit->setEnabled(false);
    epO1_lineEdit->setEnabled(false);
    epAB_lineEdit->setEnabled(false);
    xO1_lineEdit->setEnabled(false);
    yO1_lineEdit->setEnabled(false);
    xA_lineEdit->setEnabled(false);
    yA_lineEdit->setEnabled(false);
    xB_lineEdit->setEnabled(false);
    yB_lineEdit->setEnabled(false);
    xC_lineEdit->setEnabled(false);
    yC_lineEdit->setEnabled(false);
    vxO1_lineEdit->setEnabled(false);
    vyO1_lineEdit->setEnabled(false);
    vO1_lineEdit->setEnabled(false);
    vxA_lineEdit->setEnabled(false);
    vyA_lineEdit->setEnabled(false);
    vA_lineEdit->setEnabled(false);
    vxB_lineEdit->setEnabled(false);
    vyB_lineEdit->setEnabled(false);
    vB_lineEdit->setEnabled(false);
    vxC_lineEdit->setEnabled(false);
    vyC_lineEdit->setEnabled(false);
    vC_lineEdit->setEnabled(false);
    axO1_lineEdit->setEnabled(false);
    ayO1_lineEdit->setEnabled(false);
    aO1_lineEdit->setEnabled(false);
    axA_lineEdit->setEnabled(false);
    ayA_lineEdit->setEnabled(false);
    aA_lineEdit->setEnabled(false);
    axB_lineEdit->setEnabled(false);
    ayB_lineEdit->setEnabled(false);
    aB_lineEdit->setEnabled(false);
    axC_lineEdit->setEnabled(false);
    ayC_lineEdit->setEnabled(false);
    aC_lineEdit->setEnabled(false);

    fiO1g_lineEdit->setAlignment(Qt::AlignHCenter);            //положение
    fiABg_lineEdit->setAlignment(Qt::AlignHCenter);
    omO1_lineEdit->setAlignment(Qt::AlignHCenter);
    omAB_lineEdit->setAlignment(Qt::AlignHCenter);
    epO1_lineEdit->setAlignment(Qt::AlignHCenter);
    epAB_lineEdit->setAlignment(Qt::AlignHCenter);
    xO1_lineEdit->setAlignment(Qt::AlignHCenter);
    yO1_lineEdit->setAlignment(Qt::AlignHCenter);
    xA_lineEdit->setAlignment(Qt::AlignHCenter);
    yA_lineEdit->setAlignment(Qt::AlignHCenter);
    xB_lineEdit->setAlignment(Qt::AlignHCenter);
    yB_lineEdit->setAlignment(Qt::AlignHCenter);
    xC_lineEdit->setAlignment(Qt::AlignHCenter);
    yC_lineEdit->setAlignment(Qt::AlignHCenter);
    vxO1_lineEdit->setAlignment(Qt::AlignHCenter);
    vyO1_lineEdit->setAlignment(Qt::AlignHCenter);
    vO1_lineEdit->setAlignment(Qt::AlignHCenter);
    vxA_lineEdit->setAlignment(Qt::AlignHCenter);
    vyA_lineEdit->setAlignment(Qt::AlignHCenter);
    vA_lineEdit->setAlignment(Qt::AlignHCenter);
    vxB_lineEdit->setAlignment(Qt::AlignHCenter);
    vyB_lineEdit->setAlignment(Qt::AlignHCenter);
    vB_lineEdit->setAlignment(Qt::AlignHCenter);
    vxC_lineEdit->setAlignment(Qt::AlignHCenter);
    vyC_lineEdit->setAlignment(Qt::AlignHCenter);
    vC_lineEdit->setAlignment(Qt::AlignHCenter);
    axO1_lineEdit->setAlignment(Qt::AlignHCenter);
    ayO1_lineEdit->setAlignment(Qt::AlignHCenter);
    aO1_lineEdit->setAlignment(Qt::AlignHCenter);
    axA_lineEdit->setAlignment(Qt::AlignHCenter);
    ayA_lineEdit->setAlignment(Qt::AlignHCenter);
    aA_lineEdit->setAlignment(Qt::AlignHCenter);
    axB_lineEdit->setAlignment(Qt::AlignHCenter);
    ayB_lineEdit->setAlignment(Qt::AlignHCenter);
    aB_lineEdit->setAlignment(Qt::AlignHCenter);
    axC_lineEdit->setAlignment(Qt::AlignHCenter);
    ayC_lineEdit->setAlignment(Qt::AlignHCenter);
    aC_lineEdit->setAlignment(Qt::AlignHCenter);

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Создаем и настраиваем label~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
    fi_label = new QLabel(tr("fi"));                //создаем
    om_label = new QLabel(tr("om"));
    ep_label = new QLabel(tr("ep"));
    O1A_label = new QLabel(tr("O1A"));
    AB_label = new QLabel(tr("AB"));
    O1_label_1 = new QLabel(tr("O1"));
    A_label_1 = new QLabel(tr("A"));
    B_label_1 = new QLabel(tr("B"));
    C_label_1 = new QLabel(tr("C"));
    O1_label_2 = new QLabel(tr("O1"));
    A_label_2 = new QLabel(tr("A"));
    B_label_2 = new QLabel(tr("B"));
    C_label_2 = new QLabel(tr("C"));
    O1_label_3 = new QLabel(tr("O1"));
    A_label_3 = new QLabel(tr("A"));
    B_label_3 = new QLabel(tr("B"));
    C_label_3 = new QLabel(tr("C"));
    x_label = new QLabel(tr("x"));
    y_label = new QLabel(tr("y"));
    vx_label = new QLabel(tr("Vx"));
    vy_label = new QLabel(tr("Vy"));
    v_label = new QLabel(tr("V"));
    ax_label = new QLabel(tr("ax"));
    ay_label = new QLabel(tr("ay"));
    a_label = new QLabel(tr("a"));

    fi_label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);    //положение
    om_label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ep_label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    O1A_label->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    AB_label->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    O1_label_1->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    A_label_1->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    B_label_1->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    C_label_1->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    O1_label_2->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    A_label_2->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    B_label_2->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    C_label_2->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    O1_label_3->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    A_label_3->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    B_label_3->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    C_label_3->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    x_label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    y_label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    vx_label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    vy_label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    v_label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ax_label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ay_label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    a_label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Создаем grid~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
    grid_1 = new QGridLayout();
    grid_2 = new QGridLayout();
    grid_3 = new QGridLayout();
    grid_4 = new QGridLayout();
    vbox = new QVBoxLayout(this);

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Создаем сетку~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
    createGrid();
}

void OutputValues::setFont(QFont font)
{
    title_for_output_values->setFont(font);

    fiO1g_lineEdit->setFont(font);
    fiABg_lineEdit->setFont(font);
    omO1_lineEdit->setFont(font);
    omAB_lineEdit->setFont(font);
    epO1_lineEdit->setFont(font);
    epAB_lineEdit->setFont(font);
    xO1_lineEdit->setFont(font);
    yO1_lineEdit->setFont(font);
    xA_lineEdit->setFont(font);
    yA_lineEdit->setFont(font);
    xB_lineEdit->setFont(font);
    yB_lineEdit->setFont(font);
    xC_lineEdit->setFont(font);
    yC_lineEdit->setFont(font);
    vxO1_lineEdit->setFont(font);
    vyO1_lineEdit->setFont(font);
    vO1_lineEdit->setFont(font);
    vxA_lineEdit->setFont(font);
    vyA_lineEdit->setFont(font);
    vA_lineEdit->setFont(font);
    vxB_lineEdit->setFont(font);
    vyB_lineEdit->setFont(font);
    vB_lineEdit->setFont(font);
    vxC_lineEdit->setFont(font);
    vyC_lineEdit->setFont(font);
    vC_lineEdit->setFont(font);
    axO1_lineEdit->setFont(font);
    ayO1_lineEdit->setFont(font);
    aO1_lineEdit->setFont(font);
    axA_lineEdit->setFont(font);
    ayA_lineEdit->setFont(font);
    aA_lineEdit->setFont(font);
    axB_lineEdit->setFont(font);
    ayB_lineEdit->setFont(font);
    aB_lineEdit->setFont(font);
    axC_lineEdit->setFont(font);
    ayC_lineEdit->setFont(font);
    aC_lineEdit->setFont(font);

    fi_label->setFont(font);
    om_label->setFont(font);
    ep_label->setFont(font);
    O1A_label->setFont(font);
    AB_label->setFont(font);
    O1_label_1->setFont(font);
    A_label_1->setFont(font);
    B_label_1->setFont(font);
    C_label_1->setFont(font);
    O1_label_2->setFont(font);
    A_label_2->setFont(font);
    B_label_2->setFont(font);
    C_label_2->setFont(font);
    O1_label_3->setFont(font);
    A_label_3->setFont(font);
    B_label_3->setFont(font);
    C_label_3->setFont(font);
    x_label->setFont(font);
    y_label->setFont(font);
    vx_label->setFont(font);
    vy_label->setFont(font);
    v_label->setFont(font);
    ax_label->setFont(font);
    ay_label->setFont(font);
    a_label->setFont(font);
}

void OutputValues::createGrid()
{
    vbox->addWidget(title_for_output_values);

    grid_1->addWidget(fi_label, 0, 1);
    grid_1->addWidget(om_label, 0, 2);
    grid_1->addWidget(ep_label, 0, 3);
    grid_1->addWidget(O1A_label, 1, 0);
    grid_1->addWidget(AB_label, 2, 0);
    grid_1->addWidget(fiO1g_lineEdit, 1, 1);
    grid_1->addWidget(fiABg_lineEdit, 2, 1);
    grid_1->addWidget(omO1_lineEdit, 1, 2);
    grid_1->addWidget(omAB_lineEdit, 2, 2);
    grid_1->addWidget(epO1_lineEdit, 1, 3);
    grid_1->addWidget(epAB_lineEdit, 2, 3);

    vbox->addStretch();
    vbox->addLayout(grid_1);

    grid_2->addWidget(x_label, 0, 1);
    grid_2->addWidget(y_label, 0, 2);
    grid_2->addWidget(O1_label_1, 1, 0);
    grid_2->addWidget(A_label_1, 2, 0);
    grid_2->addWidget(B_label_1, 3, 0);
    grid_2->addWidget(C_label_1, 4, 0);
    grid_2->addWidget(xO1_lineEdit, 1, 1);
    grid_2->addWidget(yO1_lineEdit, 1, 2);
    grid_2->addWidget(xA_lineEdit, 2, 1);
    grid_2->addWidget(yA_lineEdit, 2, 2);
    grid_2->addWidget(xB_lineEdit, 3, 1);
    grid_2->addWidget(yB_lineEdit, 3, 2);
    grid_2->addWidget(xC_lineEdit, 4, 1);
    grid_2->addWidget(yC_lineEdit, 4, 2);

    vbox->addStretch();
    vbox->addLayout(grid_2);

    grid_3->addWidget(vx_label, 0, 1);
    grid_3->addWidget(vy_label, 0, 2);
    grid_3->addWidget(v_label, 0, 3);
    grid_3->addWidget(O1_label_2, 1, 0);
    grid_3->addWidget(A_label_2, 2, 0);
    grid_3->addWidget(B_label_2, 3, 0);
    grid_3->addWidget(C_label_2, 4, 0);
    grid_3->addWidget(vxO1_lineEdit, 1, 1);
    grid_3->addWidget(vyO1_lineEdit, 1, 2);
    grid_3->addWidget(vO1_lineEdit, 1, 3);
    grid_3->addWidget(vxA_lineEdit, 2, 1);
    grid_3->addWidget(vyA_lineEdit, 2, 2);
    grid_3->addWidget(vA_lineEdit, 2, 3);
    grid_3->addWidget(vxB_lineEdit, 3, 1);
    grid_3->addWidget(vyB_lineEdit, 3, 2);
    grid_3->addWidget(vB_lineEdit, 3, 3);
    grid_3->addWidget(vxC_lineEdit, 4, 1);
    grid_3->addWidget(vyC_lineEdit, 4, 2);
    grid_3->addWidget(vC_lineEdit, 4, 3);

    vbox->addStretch();
    vbox->addLayout(grid_3);

    grid_4->addWidget(ax_label, 0, 1);
    grid_4->addWidget(ay_label, 0, 2);
    grid_4->addWidget(a_label, 0, 3);
    grid_4->addWidget(O1_label_3, 1, 0);
    grid_4->addWidget(A_label_3, 2, 0);
    grid_4->addWidget(B_label_3, 3, 0);
    grid_4->addWidget(C_label_3, 4, 0);
    grid_4->addWidget(axO1_lineEdit, 1, 1);
    grid_4->addWidget(ayO1_lineEdit, 1, 2);
    grid_4->addWidget(aO1_lineEdit, 1, 3);
    grid_4->addWidget(axA_lineEdit, 2, 1);
    grid_4->addWidget(ayA_lineEdit, 2, 2);
    grid_4->addWidget(aA_lineEdit, 2, 3);
    grid_4->addWidget(axB_lineEdit, 3, 1);
    grid_4->addWidget(ayB_lineEdit, 3, 2);
    grid_4->addWidget(aB_lineEdit, 3, 3);
    grid_4->addWidget(axC_lineEdit, 4, 1);
    grid_4->addWidget(ayC_lineEdit, 4, 2);
    grid_4->addWidget(aC_lineEdit, 4, 3);

    vbox->addStretch();
    vbox->addLayout(grid_4);
    vbox->addStretch();
}

void OutputValues::_fiO1g_change(double value)
{
    fiO1g_lineEdit->setText(QString::number(value, 'g',  4));
}

void OutputValues::_fiABg_change(double value)
{
    fiABg_lineEdit->setText(QString::number(value, 'g',  4));
}

void OutputValues::_omO1_change(double value)
{
    omO1_lineEdit->setText(QString::number(value, 'g',  4));
}

void OutputValues::_omAB_change(double value)
{
    omAB_lineEdit->setText(QString::number(value, 'g',  4));
}

void OutputValues::_epO1_change(double value)
{
    epO1_lineEdit->setText(QString::number(value, 'g',  4));
}

void OutputValues::_epAB_change(double value)
{
    epAB_lineEdit->setText(QString::number(value, 'g',  4));
}

void OutputValues::_xO1_change(double value)
{
    xO1_lineEdit->setText(QString::number(value, 'g',  4));
}

void OutputValues::_yO1_change(double value)
{
    yO1_lineEdit->setText(QString::number(value, 'g',  4));
}

void OutputValues::_xA_change(double value)
{
    xA_lineEdit->setText(QString::number(value, 'g',  4));
}

void OutputValues::_yA_change(double value)
{
    yA_lineEdit->setText(QString::number(value, 'g',  4));
}


void OutputValues::_xB_change(double value)
{
    xB_lineEdit->setText(QString::number(value, 'g',  4));
}


void OutputValues::_yB_change(double value)
{
    yB_lineEdit->setText(QString::number(value, 'g',  4));
}


void OutputValues::_xC_change(double value)
{
    xC_lineEdit->setText(QString::number(value, 'g',  4));
}


void OutputValues::_yC_change(double value)
{
    yC_lineEdit->setText(QString::number(value, 'g',  4));
}

void OutputValues::_vxO1_change(double value)
{
    vxO1_lineEdit->setText(QString::number(value, 'g',  4));
}


void OutputValues::_vyO1_change(double value)
{
    vyO1_lineEdit->setText(QString::number(value, 'g',  4));
}


void OutputValues::_vO1_change(double value)
{
    vO1_lineEdit->setText(QString::number(value, 'g',  4));
}

void OutputValues::_vxA_change(double value)
{
    vxA_lineEdit->setText(QString::number(value, 'g',  4));
}

void OutputValues::_vyA_change(double value)
{
    vyA_lineEdit->setText(QString::number(value, 'g',  4));
}

void OutputValues::_vA_change(double value)
{
    vA_lineEdit->setText(QString::number(value, 'g',  4));
}

void OutputValues::_vxB_change(double value)
{
    vxB_lineEdit->setText(QString::number(value, 'g',  4));
}

void OutputValues::_vyB_change(double value)
{
    vyB_lineEdit->setText(QString::number(value, 'g',  4));
}

void OutputValues::_vB_change(double value)
{
    vB_lineEdit->setText(QString::number(value, 'g',  4));
}

void OutputValues::_vxC_change(double value)
{
    vxC_lineEdit->setText(QString::number(value, 'g',  4));
}

void OutputValues::_vyC_change(double value)
{
    vyC_lineEdit->setText(QString::number(value, 'g',  4));
}

void OutputValues::_vC_change(double value)
{
    vC_lineEdit->setText(QString::number(value, 'g',  4));
}

void OutputValues::_axO1_change(double value)
{
    axO1_lineEdit->setText(QString::number(value, 'g',  4));
}

void OutputValues::_ayO1_change(double value)
{
    ayO1_lineEdit->setText(QString::number(value, 'g',  4));
}

void OutputValues::_aO1_change(double value)
{
    aO1_lineEdit->setText(QString::number(value, 'g',  4));
}

void OutputValues::_axA_change(double value)
{
    axA_lineEdit->setText(QString::number(value, 'g',  4));
}

void OutputValues::_ayA_change(double value)
{
    ayA_lineEdit->setText(QString::number(value, 'g',  4));
}

void OutputValues::_aA_change(double value)
{
    aA_lineEdit->setText(QString::number(value, 'g',  4));
}

void OutputValues::_axB_change(double value)
{
    axB_lineEdit->setText(QString::number(value, 'g',  4));
}

void OutputValues::_ayB_change(double value)
{
    ayB_lineEdit->setText(QString::number(value, 'g',  4));
}

void OutputValues::_aB_change(double value)
{
    aB_lineEdit->setText(QString::number(value, 'g',  4));
}

void OutputValues::_axC_change(double value)
{
    axC_lineEdit->setText(QString::number(value, 'g',  4));
}

void OutputValues::_ayC_change(double value)
{
    ayC_lineEdit->setText(QString::number(value, 'g',  4));
}

void OutputValues::_aC_change(double value)
{
    aC_lineEdit->setText(QString::number(value, 'g', 4));
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Задание статусов скоростей и ускорений~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
SpeedAccelStatus::SpeedAccelStatus(QWidget *parent) : QWidget(parent)
{
    title = new QLabel(tr("Изменить отображаемые вектора скоростей/ускорений ->"));
    textO1 = new QLabel(tr("O1"));
    textA = new QLabel(tr("A"));
    textB = new QLabel(tr("B"));
    textC = new QLabel(tr("C"));
    textSpeed = new QLabel(tr("v"));
    textAccel = new QLabel(tr("a"));

    title->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    textO1->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    textA->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    textB->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    textC->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    textSpeed->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    textAccel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    vo1 = new QComboBox();
    ao1 = new QComboBox();
    va = new QComboBox();
    aa = new QComboBox();
    vb = new QComboBox();
    ab = new QComboBox();
    vc = new QComboBox();
    ac = new QComboBox();


    createSpeedBox(vo1);
    createSpeedBox(va);
    createSpeedBox(vb);
    createSpeedBox(vc);

    createAccelBox(ao1);
    createAccelBox(aa);
    createAccelBox(ab);
    createAccelBox(ac);

    vc->setCurrentIndex(0);
    ac->setCurrentIndex(0);

    createGrid();

    vbox = new QVBoxLayout();
    vbox->addWidget(title);
    QHBoxLayout *hbox = new QHBoxLayout();
    hbox->addLayout(grid);
    hbox->addStretch();
    vbox->addLayout(hbox);
    setLayout(vbox);
}

void SpeedAccelStatus::createSpeedBox(QComboBox *box)
{
    box->addItem(tr("V"), Constants::SHOWV);
    box->addItem(tr("Vx"), Constants::SHOWVX);
    box->addItem(tr("Vy"), Constants::SHOWVY);
    box->addItem(tr("V и Vx"), Constants::SHOWVXV);
    box->addItem(tr("V и Vy"), Constants::SHOWVYV);
    box->addItem(tr("Vx и Vy"), Constants::SHOWVXY);
    box->addItem(tr("V, Vx и Vy"), Constants::SHOWSPEED);
    box->addItem(tr("скрыть"), Constants::SHOWNOTHINGSPEED);

    box->setCurrentIndex(7);
    box->setInsertPolicy(QComboBox::InsertBeforeCurrent); //???
}

void SpeedAccelStatus::createAccelBox(QComboBox *box)
{
    box->addItem(tr("A"), Constants::SHOWA);
    box->addItem(tr("Ax"), Constants::SHOWAX);
    box->addItem(tr("Ay"), Constants::SHOWAY);
    box->addItem(tr("A и Ax"), Constants::SHOWAXA);
    box->addItem(tr("A и Ay"), Constants::SHOWAYA);
    box->addItem(tr("Ax и Ay"), Constants::SHOWAXY);
    box->addItem(tr("A, Ax и Ay"), Constants::SHOWSPEED);
    box->addItem(tr("скрыть"), Constants::SHOWNOTHINGACCEL);

    box->setCurrentIndex(7);
    box->setInsertPolicy(QComboBox::InsertBeforeCurrent); //???
}

void SpeedAccelStatus::setFont(QFont font)
{
    title->setFont(font);
    textO1->setFont(font);
    textA->setFont(font);
    textB->setFont(font);
    textC->setFont(font);
    textSpeed->setFont(font);
    textAccel->setFont(font);
    vo1->setFont(font);
    ao1->setFont(font);
    va->setFont(font);
    aa->setFont(font);
    vb->setFont(font);
    ab->setFont(font);
    vc->setFont(font);
    ac->setFont(font);
}

void SpeedAccelStatus::createGrid()
{
    grid = new QGridLayout();

    grid->addWidget(textSpeed, 1, 0);
    grid->addWidget(textAccel, 2, 0);
    grid->addWidget(textO1, 0, 1);
    grid->addWidget(textA, 0, 2);
    grid->addWidget(textB, 0, 3);
    grid->addWidget(textC, 0, 4);
    grid->addWidget(vo1, 1, 1);
    grid->addWidget(ao1, 2, 1);
    grid->addWidget(va, 1, 2);
    grid->addWidget(aa, 2, 2);
    grid->addWidget(vb, 1, 3);
    grid->addWidget(ab, 2, 3);
    grid->addWidget(vc, 1, 4);
    grid->addWidget(ac, 2, 4);

//    grid->addWidget(textSpeed, 0, 1);
//    grid->addWidget(textAccel, 0, 2);
//    grid->addWidget(textO1, 1, 0);
//    grid->addWidget(textA, 2, 0);
//    grid->addWidget(textB, 3, 0);
//    grid->addWidget(textC, 4, 0);
//    grid->addWidget(vo1, 1, 1);
//    grid->addWidget(ao1, 1, 2);
//    grid->addWidget(va, 2, 1);
//    grid->addWidget(aa, 2, 2);
//    grid->addWidget(vb, 3, 1);
//    grid->addWidget(ab, 3, 2);
//    grid->addWidget(vc, 4, 1);
//    grid->addWidget(ac, 4, 2);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Входные значения~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
InputValues2::InputValues2(QWidget *parent) : QWidget(parent)
{
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Создаем виджеты~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
    title_for_initial_values = new QLabel(tr("Входные данные  ->"));

    fi1g_value = new ValueLineEdit(QString("fi1g:"), QString("90.0"), this);
    l1_value = new ValueLineEdit(QString("l1:"), QString("10"), this);
    l2_value = new ValueLineEdit(QString("l2:"), QString("20"), this);
    l3_value = new ValueLineEdit(QString("l3:"), QString("40"), this);
    xo2_value = new ValueLineEdit(QString("xo2:"), QString("-30"), this);
    yo2_value = new ValueLineEdit(QString("yo2:"), QString("-7.1"), this);
    xc2_value = new ValueLineEdit(QString("xc2:"), QString("15"), this);
    yc2_value = new ValueLineEdit(QString("yc2:"), QString("0"), this);
    om1_value = new ValueLineEdit(QString("om1:"), QString("2"), this);
    ep1_value = new ValueLineEdit(QString("ep1:"), QString("2"), this);
    xo1_value = new ValueLineEdit(QString("xo1:"), QString("0"), this);
    yo1_value = new ValueLineEdit(QString("yo1:"), QString("0"), this);
    vo1x_value = new ValueLineEdit(QString("vo1x:"), QString("0"), this);
    vo1y_value = new ValueLineEdit(QString("vo1y:"), QString("0"), this);
    ao1x_value = new ValueLineEdit(QString("ao1x:"), QString("0"), this);
    ao1y_value = new ValueLineEdit(QString("ao1y:"), QString("0"), this);

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Создаем k_value~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
    k_label = new QLabel(tr("k:"));
    k_label->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

    k_comboBox = new QComboBox();

    k_comboBox->addItem(tr("right"), orientation_l::right);
    k_comboBox->addItem(tr("left"), orientation_l::left);
    k_comboBox->setCurrentIndex(1);

    k_comboBox->setInsertPolicy(QComboBox::InsertBeforeCurrent); //???


    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Создаем grid~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
    layout_for_values = new QGridLayout(this);

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Создаем сетку~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
    createGrid();
}

void InputValues2::setFont(QFont font)
{
    title_for_initial_values->setFont(font);

    fi1g_value->setFont(font);
    l3_value->setFont(font);
    l1_value->setFont(font);
    l2_value->setFont(font);
    xo2_value->setFont(font);
    yo2_value->setFont(font);
    xc2_value->setFont(font);
    yc2_value->setFont(font);
    k_label->setFont(font);
    k_comboBox->setFont(font);
    om1_value->setFont(font);
    ep1_value->setFont(font);
    xo1_value->setFont(font);
    yo1_value->setFont(font);
    vo1x_value->setFont(font);
    vo1y_value->setFont(font);
    ao1x_value->setFont(font);
    ao1y_value->setFont(font);
}

void InputValues2::createGrid()
{
    layout_for_values->addWidget(title_for_initial_values, 0, 0, 1, 0);  //title_for_initial_value
    layout_for_values->addWidget(fi1g_value->label, 1, 0);              //fi1g_value
    layout_for_values->addWidget(fi1g_value->lineEdit, 1, 1);
    layout_for_values->addWidget(l1_value->label, 2, 0);               //alg_value
    layout_for_values->addWidget(l1_value->lineEdit, 2, 1);
    layout_for_values->addWidget(l2_value->label, 3, 0);                //l1_value
    layout_for_values->addWidget(l2_value->lineEdit, 3, 1);
    layout_for_values->addWidget(l3_value->label, 4, 0);                //l2_value
    layout_for_values->addWidget(l3_value->lineEdit, 4, 1);
    layout_for_values->addWidget(xo2_value->label, 5, 0);                //xl_value
    layout_for_values->addWidget(xo2_value->lineEdit, 5, 1);
    layout_for_values->addWidget(yo2_value->label, 6, 0);                //yl_value
    layout_for_values->addWidget(yo2_value->lineEdit, 6, 1);
    layout_for_values->addWidget(k_label, 7, 0);               //xc2_value
    layout_for_values->addWidget(k_comboBox, 7, 1);
    layout_for_values->addWidget(xc2_value->label, 8, 0);               //yc2_value
    layout_for_values->addWidget(xc2_value->lineEdit, 8, 1);
    layout_for_values->addWidget(yc2_value->label, 9, 0);                        //k_label и k_comboBox
    layout_for_values->addWidget(yc2_value->lineEdit, 9, 1);
    layout_for_values->addWidget(om1_value->label, 10, 0);               //om1_value
    layout_for_values->addWidget(om1_value->lineEdit, 10, 1);
    layout_for_values->addWidget(ep1_value->label, 11, 0);               //ep1_value
    layout_for_values->addWidget(ep1_value->lineEdit, 11, 1);
    layout_for_values->addWidget(xo1_value->label, 12, 0);               //xo1_value
    layout_for_values->addWidget(xo1_value->lineEdit, 12, 1);
    layout_for_values->addWidget(yo1_value->label, 13, 0);               //yo1_value
    layout_for_values->addWidget(yo1_value->lineEdit, 13, 1);
    layout_for_values->addWidget(vo1x_value->label, 14, 0);              //vo1x_value
    layout_for_values->addWidget(vo1x_value->lineEdit, 14, 1);
    layout_for_values->addWidget(vo1y_value->label, 15, 0);              //vo1y_value
    layout_for_values->addWidget(vo1y_value->lineEdit, 15, 1);
    layout_for_values->addWidget(ao1x_value->label, 16, 0);              //ao1x_value
    layout_for_values->addWidget(ao1x_value->lineEdit, 16, 1);
    layout_for_values->addWidget(ao1y_value->label, 17, 0);              //ao1y_value
    layout_for_values->addWidget(ao1y_value->lineEdit, 17, 1);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Выходные значения~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
OutputValues2::OutputValues2(QWidget *parent) : QWidget(parent)
{
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Создаем виджеты~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
    title_for_output_values = new QLabel(tr("Выходные значения  ->"));

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Создаем и настраиваем lineEdit~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
    fiO1Ag_lineEdit = new QLineEdit;                     //создаем
    fiABg_lineEdit = new QLineEdit;
    fiBO2g_lineEdit = new QLineEdit;
    omO1A_lineEdit = new QLineEdit;
    omAB_lineEdit = new QLineEdit;
    omBO2_lineEdit = new QLineEdit;
    epO1A_lineEdit = new QLineEdit;
    epAB_lineEdit = new QLineEdit;
    epBO2_lineEdit = new QLineEdit;
    xO1_lineEdit = new QLineEdit;
    yO1_lineEdit = new QLineEdit;
    xA_lineEdit = new QLineEdit;
    yA_lineEdit = new QLineEdit;
    xB_lineEdit = new QLineEdit;
    yB_lineEdit = new QLineEdit;
    xC_lineEdit = new QLineEdit;
    yC_lineEdit = new QLineEdit;
    xO2_lineEdit = new QLineEdit;
    yO2_lineEdit = new QLineEdit;
    vxO1_lineEdit = new QLineEdit;
    vyO1_lineEdit = new QLineEdit;
    vO1_lineEdit = new QLineEdit;
    vxA_lineEdit = new QLineEdit;
    vyA_lineEdit = new QLineEdit;
    vA_lineEdit = new QLineEdit;
    vxB_lineEdit = new QLineEdit;
    vyB_lineEdit = new QLineEdit;
    vB_lineEdit = new QLineEdit;
    vxC_lineEdit = new QLineEdit;
    vyC_lineEdit = new QLineEdit;
    vC_lineEdit = new QLineEdit;
    vxO2_lineEdit = new QLineEdit;
    vyO2_lineEdit = new QLineEdit;
    vO2_lineEdit = new QLineEdit;
    axO1_lineEdit = new QLineEdit;
    ayO1_lineEdit = new QLineEdit;
    aO1_lineEdit = new QLineEdit;
    axA_lineEdit = new QLineEdit;
    ayA_lineEdit = new QLineEdit;
    aA_lineEdit = new QLineEdit;
    axB_lineEdit = new QLineEdit;
    ayB_lineEdit = new QLineEdit;
    aB_lineEdit = new QLineEdit;
    axC_lineEdit = new QLineEdit;
    ayC_lineEdit = new QLineEdit;
    aC_lineEdit = new QLineEdit;
    axO2_lineEdit = new QLineEdit;
    ayO2_lineEdit = new QLineEdit;
    aO2_lineEdit = new QLineEdit;

    fiO1Ag_lineEdit->setEnabled(false);                      //видимость
    fiABg_lineEdit->setEnabled(false);
    fiBO2g_lineEdit->setEnabled(false);                      //видимость

    omO1A_lineEdit->setEnabled(false);
    omAB_lineEdit->setEnabled(false);
    omBO2_lineEdit->setEnabled(false);
    epO1A_lineEdit->setEnabled(false);
    epAB_lineEdit->setEnabled(false);
    epBO2_lineEdit->setEnabled(false);
    xO1_lineEdit->setEnabled(false);
    yO1_lineEdit->setEnabled(false);
    xA_lineEdit->setEnabled(false);
    yA_lineEdit->setEnabled(false);
    xB_lineEdit->setEnabled(false);
    yB_lineEdit->setEnabled(false);
    xC_lineEdit->setEnabled(false);
    yC_lineEdit->setEnabled(false);
    xO2_lineEdit->setEnabled(false);
    yO2_lineEdit->setEnabled(false);
    vxO1_lineEdit->setEnabled(false);
    vyO1_lineEdit->setEnabled(false);
    vO1_lineEdit->setEnabled(false);
    vxA_lineEdit->setEnabled(false);
    vyA_lineEdit->setEnabled(false);
    vA_lineEdit->setEnabled(false);
    vxB_lineEdit->setEnabled(false);
    vyB_lineEdit->setEnabled(false);
    vB_lineEdit->setEnabled(false);
    vxC_lineEdit->setEnabled(false);
    vyC_lineEdit->setEnabled(false);
    vC_lineEdit->setEnabled(false);
    vxO2_lineEdit->setEnabled(false);
    vyO2_lineEdit->setEnabled(false);
    vO2_lineEdit->setEnabled(false);
    axO1_lineEdit->setEnabled(false);
    ayO1_lineEdit->setEnabled(false);
    aO1_lineEdit->setEnabled(false);
    axA_lineEdit->setEnabled(false);
    ayA_lineEdit->setEnabled(false);
    aA_lineEdit->setEnabled(false);
    axB_lineEdit->setEnabled(false);
    ayB_lineEdit->setEnabled(false);
    aB_lineEdit->setEnabled(false);
    axC_lineEdit->setEnabled(false);
    ayC_lineEdit->setEnabled(false);
    aC_lineEdit->setEnabled(false);
    axO2_lineEdit->setEnabled(false);
    ayO2_lineEdit->setEnabled(false);
    aO2_lineEdit->setEnabled(false);

    fiO1Ag_lineEdit->setAlignment(Qt::AlignHCenter);            //положение
    fiABg_lineEdit->setAlignment(Qt::AlignHCenter);
    fiBO2g_lineEdit->setAlignment(Qt::AlignHCenter);
    omO1A_lineEdit->setAlignment(Qt::AlignHCenter);
    omAB_lineEdit->setAlignment(Qt::AlignHCenter);
    omBO2_lineEdit->setAlignment(Qt::AlignHCenter);
    epO1A_lineEdit->setAlignment(Qt::AlignHCenter);
    epAB_lineEdit->setAlignment(Qt::AlignHCenter);
    epBO2_lineEdit->setAlignment(Qt::AlignHCenter);
    xO1_lineEdit->setAlignment(Qt::AlignHCenter);
    yO1_lineEdit->setAlignment(Qt::AlignHCenter);
    xA_lineEdit->setAlignment(Qt::AlignHCenter);
    yA_lineEdit->setAlignment(Qt::AlignHCenter);
    xB_lineEdit->setAlignment(Qt::AlignHCenter);
    yB_lineEdit->setAlignment(Qt::AlignHCenter);
    xC_lineEdit->setAlignment(Qt::AlignHCenter);
    yC_lineEdit->setAlignment(Qt::AlignHCenter);
    xO2_lineEdit->setAlignment(Qt::AlignHCenter);
    yO2_lineEdit->setAlignment(Qt::AlignHCenter);
    vxO1_lineEdit->setAlignment(Qt::AlignHCenter);
    vyO1_lineEdit->setAlignment(Qt::AlignHCenter);
    vO1_lineEdit->setAlignment(Qt::AlignHCenter);
    vxA_lineEdit->setAlignment(Qt::AlignHCenter);
    vyA_lineEdit->setAlignment(Qt::AlignHCenter);
    vA_lineEdit->setAlignment(Qt::AlignHCenter);
    vxB_lineEdit->setAlignment(Qt::AlignHCenter);
    vyB_lineEdit->setAlignment(Qt::AlignHCenter);
    vB_lineEdit->setAlignment(Qt::AlignHCenter);
    vxC_lineEdit->setAlignment(Qt::AlignHCenter);
    vyC_lineEdit->setAlignment(Qt::AlignHCenter);
    vC_lineEdit->setAlignment(Qt::AlignHCenter);
    vxO2_lineEdit->setAlignment(Qt::AlignHCenter);
    vyO2_lineEdit->setAlignment(Qt::AlignHCenter);
    vO2_lineEdit->setAlignment(Qt::AlignHCenter);
    axO1_lineEdit->setAlignment(Qt::AlignHCenter);
    ayO1_lineEdit->setAlignment(Qt::AlignHCenter);
    aO1_lineEdit->setAlignment(Qt::AlignHCenter);
    axA_lineEdit->setAlignment(Qt::AlignHCenter);
    ayA_lineEdit->setAlignment(Qt::AlignHCenter);
    aA_lineEdit->setAlignment(Qt::AlignHCenter);
    axB_lineEdit->setAlignment(Qt::AlignHCenter);
    ayB_lineEdit->setAlignment(Qt::AlignHCenter);
    aB_lineEdit->setAlignment(Qt::AlignHCenter);
    axC_lineEdit->setAlignment(Qt::AlignHCenter);
    ayC_lineEdit->setAlignment(Qt::AlignHCenter);
    aC_lineEdit->setAlignment(Qt::AlignHCenter);
    axO2_lineEdit->setAlignment(Qt::AlignHCenter);
    ayO2_lineEdit->setAlignment(Qt::AlignHCenter);
    aO2_lineEdit->setAlignment(Qt::AlignHCenter);

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Создаем и настраиваем label~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
    fi_label = new QLabel(tr("fi"));                //создаем
    om_label = new QLabel(tr("om"));
    ep_label = new QLabel(tr("ep"));
    O1A_label = new QLabel(tr("O1A"));
    AB_label = new QLabel(tr("AB"));
    BO2_label = new QLabel(tr("BO2"));
    O1_label_1 = new QLabel(tr("O1"));
    A_label_1 = new QLabel(tr("A"));
    B_label_1 = new QLabel(tr("B"));
    C_label_1 = new QLabel(tr("C"));
    O2_label_1 = new QLabel(tr("O2"));
    O1_label_2 = new QLabel(tr("O1"));
    A_label_2 = new QLabel(tr("A"));
    B_label_2 = new QLabel(tr("B"));
    C_label_2 = new QLabel(tr("C"));
    O2_label_2 = new QLabel(tr("O2"));
    O1_label_3 = new QLabel(tr("O1"));
    A_label_3 = new QLabel(tr("A"));
    B_label_3 = new QLabel(tr("B"));
    C_label_3 = new QLabel(tr("C"));
    O2_label_3 = new QLabel(tr("O2"));
    x_label = new QLabel(tr("x"));
    y_label = new QLabel(tr("y"));
    vx_label = new QLabel(tr("Vx"));
    vy_label = new QLabel(tr("Vy"));
    v_label = new QLabel(tr("V"));
    ax_label = new QLabel(tr("ax"));
    ay_label = new QLabel(tr("ay"));
    a_label = new QLabel(tr("a"));

    fi_label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);    //положение
    om_label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ep_label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    O1A_label->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    AB_label->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    BO2_label->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    O1_label_1->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    A_label_1->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    B_label_1->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    C_label_1->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    O2_label_1->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    O1_label_2->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    A_label_2->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    B_label_2->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    C_label_2->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    O2_label_2->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    O1_label_3->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    A_label_3->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    B_label_3->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    C_label_3->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    O2_label_3->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    x_label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    y_label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    vx_label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    vy_label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    v_label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ax_label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ay_label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    a_label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Создаем grid~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
    grid_1 = new QGridLayout();
    grid_2 = new QGridLayout();
    grid_3 = new QGridLayout();
    grid_4 = new QGridLayout();
    vbox = new QVBoxLayout(this);

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Создаем сетку~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
    createGrid();
}

void OutputValues2::setFont(QFont font)
{
    title_for_output_values->setFont(font);

    fiO1Ag_lineEdit->setFont(font);
    fiABg_lineEdit->setFont(font);
    fiBO2g_lineEdit->setFont(font);
    omO1A_lineEdit->setFont(font);
    omAB_lineEdit->setFont(font);
    omBO2_lineEdit->setFont(font);
    epO1A_lineEdit->setFont(font);
    epAB_lineEdit->setFont(font);
    epBO2_lineEdit->setFont(font);
    xO1_lineEdit->setFont(font);
    yO1_lineEdit->setFont(font);
    xA_lineEdit->setFont(font);
    yA_lineEdit->setFont(font);
    xB_lineEdit->setFont(font);
    yB_lineEdit->setFont(font);
    xC_lineEdit->setFont(font);
    yC_lineEdit->setFont(font);
    xO2_lineEdit->setFont(font);
    yO2_lineEdit->setFont(font);
    vxO1_lineEdit->setFont(font);
    vyO1_lineEdit->setFont(font);
    vO1_lineEdit->setFont(font);
    vxA_lineEdit->setFont(font);
    vyA_lineEdit->setFont(font);
    vA_lineEdit->setFont(font);
    vxB_lineEdit->setFont(font);
    vyB_lineEdit->setFont(font);
    vB_lineEdit->setFont(font);
    vxC_lineEdit->setFont(font);
    vyC_lineEdit->setFont(font);
    vC_lineEdit->setFont(font);
    vxO2_lineEdit->setFont(font);
    vyO2_lineEdit->setFont(font);
    vO2_lineEdit->setFont(font);
    axO1_lineEdit->setFont(font);
    ayO1_lineEdit->setFont(font);
    aO1_lineEdit->setFont(font);
    axA_lineEdit->setFont(font);
    ayA_lineEdit->setFont(font);
    aA_lineEdit->setFont(font);
    axB_lineEdit->setFont(font);
    ayB_lineEdit->setFont(font);
    aB_lineEdit->setFont(font);
    axC_lineEdit->setFont(font);
    ayC_lineEdit->setFont(font);
    aC_lineEdit->setFont(font);
    axO2_lineEdit->setFont(font);
    ayO2_lineEdit->setFont(font);
    aO2_lineEdit->setFont(font);

    fi_label->setFont(font);
    om_label->setFont(font);
    ep_label->setFont(font);
    O1A_label->setFont(font);
    AB_label->setFont(font);
    BO2_label->setFont(font);
    O1_label_1->setFont(font);
    A_label_1->setFont(font);
    B_label_1->setFont(font);
    C_label_1->setFont(font);
    O2_label_1->setFont(font);
    O1_label_2->setFont(font);
    A_label_2->setFont(font);
    B_label_2->setFont(font);
    C_label_2->setFont(font);
    O2_label_2->setFont(font);
    O1_label_3->setFont(font);
    A_label_3->setFont(font);
    B_label_3->setFont(font);
    C_label_3->setFont(font);
    O2_label_3->setFont(font);
    x_label->setFont(font);
    y_label->setFont(font);
    vx_label->setFont(font);
    vy_label->setFont(font);
    v_label->setFont(font);
    ax_label->setFont(font);
    ay_label->setFont(font);
    a_label->setFont(font);
}

void OutputValues2::createGrid()
{
    vbox->addWidget(title_for_output_values);

    grid_1->addWidget(fi_label, 0, 1);
    grid_1->addWidget(om_label, 0, 2);
    grid_1->addWidget(ep_label, 0, 3);
    grid_1->addWidget(O1A_label, 1, 0);
    grid_1->addWidget(AB_label, 2, 0);
    grid_1->addWidget(BO2_label, 3, 0);
    grid_1->addWidget(fiO1Ag_lineEdit, 1, 1);
    grid_1->addWidget(fiABg_lineEdit, 2, 1);
    grid_1->addWidget(fiBO2g_lineEdit, 3, 1);
    grid_1->addWidget(omO1A_lineEdit, 1, 2);
    grid_1->addWidget(omAB_lineEdit, 2, 2);
    grid_1->addWidget(omBO2_lineEdit, 3, 2);
    grid_1->addWidget(epO1A_lineEdit, 1, 3);
    grid_1->addWidget(epAB_lineEdit, 2, 3);
    grid_1->addWidget(epBO2_lineEdit, 3, 3);

    vbox->addStretch();
    vbox->addLayout(grid_1);

    grid_2->addWidget(x_label, 0, 1);
    grid_2->addWidget(y_label, 0, 2);
    grid_2->addWidget(O1_label_1, 1, 0);
    grid_2->addWidget(A_label_1, 2, 0);
    grid_2->addWidget(B_label_1, 3, 0);
    grid_2->addWidget(C_label_1, 4, 0);
    grid_2->addWidget(O2_label_1, 5, 0);
    grid_2->addWidget(xO1_lineEdit, 1, 1);
    grid_2->addWidget(yO1_lineEdit, 1, 2);
    grid_2->addWidget(xA_lineEdit, 2, 1);
    grid_2->addWidget(yA_lineEdit, 2, 2);
    grid_2->addWidget(xB_lineEdit, 3, 1);
    grid_2->addWidget(yB_lineEdit, 3, 2);
    grid_2->addWidget(xC_lineEdit, 4, 1);
    grid_2->addWidget(yC_lineEdit, 4, 2);
    grid_2->addWidget(xO2_lineEdit, 5, 1);
    grid_2->addWidget(yO2_lineEdit, 5, 2);

    vbox->addStretch();
    vbox->addLayout(grid_2);

    grid_3->addWidget(vx_label, 0, 1);
    grid_3->addWidget(vy_label, 0, 2);
    grid_3->addWidget(v_label, 0, 3);
    grid_3->addWidget(O1_label_2, 1, 0);
    grid_3->addWidget(A_label_2, 2, 0);
    grid_3->addWidget(B_label_2, 3, 0);
    grid_3->addWidget(C_label_2, 4, 0);
    grid_3->addWidget(O2_label_2, 5, 0);
    grid_3->addWidget(vxO1_lineEdit, 1, 1);
    grid_3->addWidget(vyO1_lineEdit, 1, 2);
    grid_3->addWidget(vO1_lineEdit, 1, 3);
    grid_3->addWidget(vxA_lineEdit, 2, 1);
    grid_3->addWidget(vyA_lineEdit, 2, 2);
    grid_3->addWidget(vA_lineEdit, 2, 3);
    grid_3->addWidget(vxB_lineEdit, 3, 1);
    grid_3->addWidget(vyB_lineEdit, 3, 2);
    grid_3->addWidget(vB_lineEdit, 3, 3);
    grid_3->addWidget(vxC_lineEdit, 4, 1);
    grid_3->addWidget(vyC_lineEdit, 4, 2);
    grid_3->addWidget(vC_lineEdit, 4, 3);
    grid_3->addWidget(vxO2_lineEdit, 5, 1);
    grid_3->addWidget(vyO2_lineEdit, 5, 2);
    grid_3->addWidget(vO2_lineEdit, 5, 3);

    vbox->addStretch();
    vbox->addLayout(grid_3);

    grid_4->addWidget(ax_label, 0, 1);
    grid_4->addWidget(ay_label, 0, 2);
    grid_4->addWidget(a_label, 0, 3);
    grid_4->addWidget(O1_label_3, 1, 0);
    grid_4->addWidget(A_label_3, 2, 0);
    grid_4->addWidget(B_label_3, 3, 0);
    grid_4->addWidget(C_label_3, 4, 0);
    grid_4->addWidget(O2_label_3, 5, 0);
    grid_4->addWidget(axO1_lineEdit, 1, 1);
    grid_4->addWidget(ayO1_lineEdit, 1, 2);
    grid_4->addWidget(aO1_lineEdit, 1, 3);
    grid_4->addWidget(axA_lineEdit, 2, 1);
    grid_4->addWidget(ayA_lineEdit, 2, 2);
    grid_4->addWidget(aA_lineEdit, 2, 3);
    grid_4->addWidget(axB_lineEdit, 3, 1);
    grid_4->addWidget(ayB_lineEdit, 3, 2);
    grid_4->addWidget(aB_lineEdit, 3, 3);
    grid_4->addWidget(axC_lineEdit, 4, 1);
    grid_4->addWidget(ayC_lineEdit, 4, 2);
    grid_4->addWidget(aC_lineEdit, 4, 3);
    grid_4->addWidget(axO2_lineEdit, 5, 1);
    grid_4->addWidget(ayO2_lineEdit, 5, 2);
    grid_4->addWidget(aO2_lineEdit, 5, 3);

    vbox->addStretch();
    vbox->addLayout(grid_4);
    vbox->addStretch();
}

void OutputValues2::_fiO1Ag_change(double value)
{
    if (qAbs(value) <= Constants::error)
        value = 0;
    fiO1Ag_lineEdit->setText(QString::number(value, 'g',  4));
}

void OutputValues2::_fiABg_change(double value)
{
    if (qAbs(value) <= Constants::error)
        value = 0;
    fiABg_lineEdit->setText(QString::number(value, 'g',  4));
}

void OutputValues2::_fiBO2g_change(double value)
{
    if (qAbs(value) <= Constants::error)
        value = 0;
    fiBO2g_lineEdit->setText(QString::number(value, 'g',  4));
}

void OutputValues2::_omO1A_change(double value)
{
    if (qAbs(value) <= Constants::error)
        value = 0;
    omO1A_lineEdit->setText(QString::number(value, 'g',  4));
}

void OutputValues2::_omAB_change(double value)
{
    if (qAbs(value) <= Constants::error)
        value = 0;
    omAB_lineEdit->setText(QString::number(value, 'g',  4));
}

void OutputValues2::_omBO2_change(double value)
{
    if (qAbs(value) <= Constants::error)
        value = 0;
    omBO2_lineEdit->setText(QString::number(value, 'g',  4));
}

void OutputValues2::_epO1A_change(double value)
{
    if (qAbs(value) <= Constants::error)
        value = 0;
    epO1A_lineEdit->setText(QString::number(value, 'g',  4));
}

void OutputValues2::_epAB_change(double value)
{
    if (qAbs(value) <= Constants::error)
        value = 0;
    epAB_lineEdit->setText(QString::number(value, 'g',  4));
}

void OutputValues2::_epBO2_change(double value)
{
    if (qAbs(value) <= Constants::error)
        value = 0;
    epBO2_lineEdit->setText(QString::number(value, 'g',  4));
}

void OutputValues2::_xO1_change(double value)
{
    if (qAbs(value) <= Constants::error)
        value = 0;
    xO1_lineEdit->setText(QString::number(value, 'g',  4));
}

void OutputValues2::_yO1_change(double value)
{
    if (qAbs(value) <= Constants::error)
        value = 0;
    yO1_lineEdit->setText(QString::number(value, 'g',  4));
}

void OutputValues2::_xA_change(double value)
{
    if (qAbs(value) <= Constants::error)
        value = 0;
    xA_lineEdit->setText(QString::number(value, 'g',  4));
}

void OutputValues2::_yA_change(double value)
{
    if (qAbs(value) <= Constants::error)
        value = 0;
    yA_lineEdit->setText(QString::number(value, 'g',  4));
}

void OutputValues2::_xB_change(double value)
{
    if (qAbs(value) <= Constants::error)
        value = 0;
    xB_lineEdit->setText(QString::number(value, 'g',  4));
}

void OutputValues2::_yB_change(double value)
{
    if (qAbs(value) <= Constants::error)
        value = 0;
    yB_lineEdit->setText(QString::number(value, 'g',  4));
}

void OutputValues2::_xC_change(double value)
{
    if (qAbs(value) <= Constants::error)
        value = 0;
    xC_lineEdit->setText(QString::number(value, 'g',  4));
}

void OutputValues2::_yC_change(double value)
{
    if (qAbs(value) <= Constants::error)
        value = 0;
    yC_lineEdit->setText(QString::number(value, 'g',  4));
}

void OutputValues2::_xO2_change(double value)
{
    if (qAbs(value) <= Constants::error)
        value = 0;
    xO2_lineEdit->setText(QString::number(value, 'g',  4));
}

void OutputValues2::_yO2_change(double value)
{
    if (qAbs(value) <= Constants::error)
        value = 0;
    yO2_lineEdit->setText(QString::number(value, 'g',  4));
}

void OutputValues2::_vxO1_change(double value)
{
    if (qAbs(value) <= Constants::error)
        value = 0;
    vxO1_lineEdit->setText(QString::number(value, 'g',  4));
}

void OutputValues2::_vyO1_change(double value)
{
    if (qAbs(value) <= Constants::error)
        value = 0;
    vyO1_lineEdit->setText(QString::number(value, 'g',  4));
}

void OutputValues2::_vO1_change(double value)
{
    if (qAbs(value) <= Constants::error)
        value = 0;
    vO1_lineEdit->setText(QString::number(value, 'g',  4));
}

void OutputValues2::_vxA_change(double value)
{
    if (qAbs(value) <= Constants::error)
        value = 0;
    vxA_lineEdit->setText(QString::number(value, 'g',  4));
}

void OutputValues2::_vyA_change(double value)
{
    if (qAbs(value) <= Constants::error)
        value = 0;
    vyA_lineEdit->setText(QString::number(value, 'g',  4));
}

void OutputValues2::_vA_change(double value)
{
    if (qAbs(value) <= Constants::error)
        value = 0;
    vA_lineEdit->setText(QString::number(value, 'g',  4));
}

void OutputValues2::_vxB_change(double value)
{
    if (qAbs(value) <= Constants::error)
        value = 0;
    vxB_lineEdit->setText(QString::number(value, 'g',  4));
}

void OutputValues2::_vyB_change(double value)
{
    if (qAbs(value) <= Constants::error)
        value = 0;
    vyB_lineEdit->setText(QString::number(value, 'g',  4));
}

void OutputValues2::_vB_change(double value)
{
    if (qAbs(value) <= Constants::error)
        value = 0;
    vB_lineEdit->setText(QString::number(value, 'g',  4));
}

void OutputValues2::_vxC_change(double value)
{
    if (qAbs(value) <= Constants::error)
        value = 0;
    vxC_lineEdit->setText(QString::number(value, 'g',  4));
}

void OutputValues2::_vyC_change(double value)
{
    if (qAbs(value) <= Constants::error)
        value = 0;
    vyC_lineEdit->setText(QString::number(value, 'g',  4));
}

void OutputValues2::_vC_change(double value)
{
    if (qAbs(value) <= Constants::error)
        value = 0;
    vC_lineEdit->setText(QString::number(value, 'g',  4));
}

void OutputValues2::_vxO2_change(double value)
{
    if (qAbs(value) <= Constants::error)
        value = 0;
    vxO2_lineEdit->setText(QString::number(value, 'g',  4));
}

void OutputValues2::_vyO2_change(double value)
{
    if (qAbs(value) <= Constants::error)
        value = 0;
    vyO2_lineEdit->setText(QString::number(value, 'g',  4));
}

void OutputValues2::_vO2_change(double value)
{
    if (qAbs(value) <= Constants::error)
        value = 0;
    vO2_lineEdit->setText(QString::number(value, 'g',  4));
}

void OutputValues2::_axO1_change(double value)
{
    if (qAbs(value) <= Constants::error)
        value = 0;
    axO1_lineEdit->setText(QString::number(value, 'g',  4));
}

void OutputValues2::_ayO1_change(double value)
{
    if (qAbs(value) <= Constants::error)
        value = 0;
    ayO1_lineEdit->setText(QString::number(value, 'g',  4));
}

void OutputValues2::_aO1_change(double value)
{
    if (qAbs(value) <= Constants::error)
        value = 0;
    aO1_lineEdit->setText(QString::number(value, 'g',  4));
}

void OutputValues2::_axA_change(double value)
{
    if (qAbs(value) <= Constants::error)
        value = 0;
    axA_lineEdit->setText(QString::number(value, 'g',  4));
}

void OutputValues2::_ayA_change(double value)
{
    if (qAbs(value) <= Constants::error)
        value = 0;
    ayA_lineEdit->setText(QString::number(value, 'g',  4));
}

void OutputValues2::_aA_change(double value)
{
    if (qAbs(value) <= Constants::error)
        value = 0;
    aA_lineEdit->setText(QString::number(value, 'g',  4));
}

void OutputValues2::_axB_change(double value)
{
    if (qAbs(value) <= Constants::error)
        value = 0;
    axB_lineEdit->setText(QString::number(value, 'g',  4));
}

void OutputValues2::_ayB_change(double value)
{
    if (qAbs(value) <= Constants::error)
        value = 0;
    ayB_lineEdit->setText(QString::number(value, 'g',  4));
}

void OutputValues2::_aB_change(double value)
{
    if (qAbs(value) <= Constants::error)
        value = 0;
    aB_lineEdit->setText(QString::number(value, 'g',  4));
}

void OutputValues2::_axC_change(double value)
{
    if (qAbs(value) <= Constants::error)
        value = 0;
    axC_lineEdit->setText(QString::number(value, 'g',  4));
}

void OutputValues2::_ayC_change(double value)
{
    if (qAbs(value) <= Constants::error)
        value = 0;
    ayC_lineEdit->setText(QString::number(value, 'g',  4));
}

void OutputValues2::_aC_change(double value)
{
    if (qAbs(value) <= Constants::error)
        value = 0;
    aC_lineEdit->setText(QString::number(value, 'g',  4));
}

void OutputValues2::_axO2_change(double value)
{
    if (qAbs(value) <= Constants::error)
        value = 0;
    axO2_lineEdit->setText(QString::number(value, 'g',  4));
}

void OutputValues2::_ayO2_change(double value)
{
    if (qAbs(value) <= Constants::error)
        value = 0;
    ayO2_lineEdit->setText(QString::number(value, 'g',  4));
}

void OutputValues2::_aO2_change(double value)
{
    if (qAbs(value) <= Constants::error)
        value = 0;
    aO2_lineEdit->setText(QString::number(value, 'g',  4));
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Задание статусов скоростей и ускорений~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
SpeedAccelStatus2::SpeedAccelStatus2(QWidget *parent) : QWidget(parent)
{
    title = new QLabel(tr("Изменить отображаемые вектора скоростей/ускорений ->"));
    textO1 = new QLabel(tr("O1"));
    textA = new QLabel(tr("A"));
    textB = new QLabel(tr("B"));
    textC = new QLabel(tr("C"));
    textO2 = new QLabel(tr("O2"));
    textSpeed = new QLabel(tr("v"));
    textAccel = new QLabel(tr("a"));

    title->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    textO1->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    textA->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    textB->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    textC->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    textO2->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    textSpeed->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    textAccel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    vo1 = new QComboBox();
    ao1 = new QComboBox();
    va = new QComboBox();
    aa = new QComboBox();
    vb = new QComboBox();
    ab = new QComboBox();
    vc = new QComboBox();
    ac = new QComboBox();
    vo2 = new QComboBox();
    ao2 = new QComboBox();

    createSpeedBox(vo1);
    createSpeedBox(va);
    createSpeedBox(vb);
    createSpeedBox(vc);
    createSpeedBox(vo2);

    createAccelBox(ao1);
    createAccelBox(aa);
    createAccelBox(ab);
    createAccelBox(ac);
    createAccelBox(ao2);

    vc->setCurrentIndex(0);
    ac->setCurrentIndex(0);

    createGrid();

    vbox = new QVBoxLayout();
    vbox->addWidget(title);
    QHBoxLayout *hbox = new QHBoxLayout();
    hbox->addLayout(grid);
    hbox->addStretch();
    vbox->addLayout(hbox);
    setLayout(vbox);
}

void SpeedAccelStatus2::createSpeedBox(QComboBox *box)
{
    box->addItem(tr("V"), Constants::SHOWV);
    box->addItem(tr("Vx"), Constants::SHOWVX);
    box->addItem(tr("Vy"), Constants::SHOWVY);
    box->addItem(tr("V и Vx"), Constants::SHOWVXV);
    box->addItem(tr("V и Vy"), Constants::SHOWVYV);
    box->addItem(tr("Vx и Vy"), Constants::SHOWVXY);
    box->addItem(tr("V, Vx и Vy"), Constants::SHOWSPEED);
    box->addItem(tr("скрыть"), Constants::SHOWNOTHINGSPEED);

    box->setCurrentIndex(7);
    box->setInsertPolicy(QComboBox::InsertBeforeCurrent); //???
}

void SpeedAccelStatus2::createAccelBox(QComboBox *box)
{
    box->addItem(tr("A"), Constants::SHOWA);
    box->addItem(tr("Ax"), Constants::SHOWAX);
    box->addItem(tr("Ay"), Constants::SHOWAY);
    box->addItem(tr("A и Ax"), Constants::SHOWAXA);
    box->addItem(tr("A и Ay"), Constants::SHOWAYA);
    box->addItem(tr("Ax и Ay"), Constants::SHOWAXY);
    box->addItem(tr("A, Ax и Ay"), Constants::SHOWSPEED);
    box->addItem(tr("скрыть"), Constants::SHOWNOTHINGACCEL);

    box->setCurrentIndex(7);
    box->setInsertPolicy(QComboBox::InsertBeforeCurrent); //???
}

void SpeedAccelStatus2::setFont(QFont font)
{
    title->setFont(font);
    textO1->setFont(font);
    textA->setFont(font);
    textB->setFont(font);
    textC->setFont(font);
    textO2->setFont(font);
    textSpeed->setFont(font);
    textAccel->setFont(font);
    vo1->setFont(font);
    ao1->setFont(font);
    va->setFont(font);
    aa->setFont(font);
    vb->setFont(font);
    ab->setFont(font);
    vc->setFont(font);
    ac->setFont(font);
    vo2->setFont(font);
    ao2->setFont(font);
}

void SpeedAccelStatus2::createGrid()
{
    grid = new QGridLayout();

    grid->addWidget(textSpeed, 1, 0);
    grid->addWidget(textAccel, 2, 0);
    grid->addWidget(textO1, 0, 1);
    grid->addWidget(textA, 0, 2);
    grid->addWidget(textB, 0, 3);
    grid->addWidget(textC, 0, 4);
    grid->addWidget(textO1, 0, 5);
    grid->addWidget(vo1, 1, 1);
    grid->addWidget(ao1, 2, 1);
    grid->addWidget(va, 1, 2);
    grid->addWidget(aa, 2, 2);
    grid->addWidget(vb, 1, 3);
    grid->addWidget(ab, 2, 3);
    grid->addWidget(vc, 1, 4);
    grid->addWidget(ac, 2, 4);
    grid->addWidget(vo1, 1, 5);
    grid->addWidget(ao1, 2, 5);
}
