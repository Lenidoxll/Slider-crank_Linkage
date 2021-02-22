#include "mywidget.h"
#include "plot.h"

#include <QMouseEvent>
#include <QPushButton>
#include <QToolButton>
#include <QDebug>
#include <QScreen>
#include <QGuiApplication>

MyWidget::MyWidget(QWidget *parent) : QWidget(parent)
{
    //задаем размеры
    QPoint center = ((QGuiApplication::primaryScreen())->geometry()).center();
    this->setGeometry(center.x()/2, center.y()/2,
                      ((QGuiApplication::primaryScreen())->geometry()).width()/2,
                      ((QGuiApplication::primaryScreen())->geometry()).height()/2);

    //создаем левую сторону виджета
    hbox = new QHBoxLayout(this);
    label = new QLabel(tr("&Высота: "), this);
    label->setFont(QFont("Purisa", 13));
    label->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    lineedit = new QLineEdit(tr("100"), this);
    label->setBuddy(lineedit);

    //создаем правую сторону: кнопку наверху
    pause_or_play = new QToolButton;
    pause_or_play->setIcon(pause);
    pause_or_play->setIconSize(QSize(50, 50));

    //создаем нижнюю кнопку переключатель
    mechanism_or_graphic = new QPushButton(tr("Graphic"));
    mechanism_or_graphic->setFont(QFont("Times New Roman", 14));

    QHBoxLayout* hboxright1 = new QHBoxLayout();
    hboxright1->addStretch();
    hboxright1->addWidget(pause_or_play);

    //создаем кривошп-шатун
    QVBoxLayout* vboxright = new QVBoxLayout();
    vboxright->addLayout(hboxright1);

    hboxright2 = new QHBoxLayout();
    mainw = new MainWidget;
    hboxright2->addWidget(mainw);
    //vboxright->addWidget(mainw);
    plot = new Plot;
    plot->hide();
    hboxright2->addWidget(plot);
    //vboxright->addWidget(plot);
    vboxright->addLayout(hboxright2);

    QHBoxLayout* hboxright3 = new QHBoxLayout();
    hboxright3->addWidget(mechanism_or_graphic);
    hboxright3->addStretch();
    vboxright->addLayout(hboxright3);

    hbox->addWidget(label);
    hbox->addWidget(lineedit);
    hbox->addLayout(vboxright);
    setLayout(hbox);

    connect(lineedit, SIGNAL(textChanged(const QString &)), mainw, SLOT(_edit_hight(const QString &)));
    connect(pause_or_play, &QToolButton::clicked, this, &MyWidget::_slot_pause_or_play);
    connect(mechanism_or_graphic, &QPushButton::clicked, this, &MyWidget::_slot_mechanism_or_graphic);
    connect(mainw->timer, &QTimer::timeout, this, &MyWidget::_slot_xBChanged);
}

void MyWidget::_slot_pause_or_play()
{
    if (current_stats_pause_or_play == PLAY) {
        current_stats_pause_or_play = PAUSE;
        pause_or_play->setIcon(play);
        mainw->_stop_timer();
        //plot->_stop_timer();
    } else {
        current_stats_pause_or_play = PLAY;
        pause_or_play->setIcon(pause);
        mainw->_start_timer();
        //plot->_start_timer();
    }
}

void MyWidget::_slot_mechanism_or_graphic()
{
    if (current_stats_mechanism_or_graphic == MECHANISM) {
        current_stats_mechanism_or_graphic = GRAPHIC;
        mechanism_or_graphic->setText(tr("Mechanism"));
        mainw->hide();
        plot->show();
    } else {
        current_stats_mechanism_or_graphic = MECHANISM;
        mechanism_or_graphic->setText(tr("Graphic"));
        plot->hide();
        mainw->show();
    }
}

void MyWidget::_slot_xBChanged()
{
    plot->key_B.append(plot->key_B.last()+1000/30);
    plot->value_B.append(mainw->x_B);
    plot->slot_xBChanged();
}
