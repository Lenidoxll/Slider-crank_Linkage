#include "mainwindow.h"
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    firstw = new FirstWindow(this);
    firstw->show();

    connect(firstw->btnwinscl1, &QPushButton::clicked, this, &MainWindow::_to_mywidget);
}

void MainWindow::_to_mywidget()
{
    firstw->hide();

    myw = new MyWidget(this);
    myw->show();
}
