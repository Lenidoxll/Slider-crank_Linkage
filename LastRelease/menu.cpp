#include "menu.h"
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QtMath>
#include <QDebug>

Menu::Menu(QWidget *parent) : QWidget(parent)
{
    font = QFont("Purisa", 11);

    label = new QLabel("Выберите тип механизма:", this);
    label->setFont(font);
    btnwinscl1 = new QPushButton("Кривошипно-шатунный\nмеханизм", this);
    btnwinscl1->setFont(font);
    btnwinscl2 = new QPushButton("Двухкривошипный\nмеханизм", this);
    btnwinscl2->setFont(font);
    createWindow();
}

void Menu::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
    double height = geometry().height();
    int size = qFloor(height / 30);
    qDebug() << " size was = " << font.pointSize() << Qt::endl;
    font.setPointSize(size);
    qDebug() << " size is = " << font.pointSize() << Qt::endl;
    label->setFont(font);
    btnwinscl1->setFont(font);
    btnwinscl2->setFont(font);
}

void Menu::createWindow()
{
    QVBoxLayout* vbox = new QVBoxLayout(this);
    QHBoxLayout* hbox = new QHBoxLayout();

    hbox->addStretch(3);
    hbox->addWidget(btnwinscl1, 1, Qt::AlignLeft);
    hbox->addStretch(1);
    hbox->addWidget(btnwinscl2, 1, Qt::AlignRight);
    hbox->addStretch(3);

    vbox->addStretch(5);
    vbox->addWidget(label, 0, Qt::AlignCenter);
    vbox->addStretch(3);
    vbox->addLayout(hbox);
    vbox->addStretch(5);
}
