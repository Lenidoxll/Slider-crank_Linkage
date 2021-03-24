#include "firstwindow.h"
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>

FirstWindow::FirstWindow(QWidget *parent) : QWidget(parent)
{
    label = new QLabel("Click to select the mechanism:", this);
    label->setFont(QFont("Times New Roman", 20));
    btnwinscl1 = new QPushButton("Slider-crank linkage", this);
    btnwinscl1->setFont(QFont("Times New Roman", 14));
    btnwinscl2 = new QPushButton("Double slider-crank lonkage", this);
    btnwinscl2->setFont(QFont("Times New Roman", 14));
    this->setFixedSize(700, 250);
    createWindow();
}

void FirstWindow::createWindow()
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
