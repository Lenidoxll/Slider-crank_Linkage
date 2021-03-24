#include "mainwindow.h"

#include <QPushButton>
#include <QtWidgets>
#include <QEvent>
#include <QSizePolicy>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    menu = new Menu();
    slider_crank_linkage = new Slider_crank_linkage();
    double_slider_crank_linkage = new Double_slider_crank_linkage();
    stack = new QStackedWidget(this);
    stack->addWidget(menu);
    stack->addWidget(slider_crank_linkage);
    stack->addWidget(double_slider_crank_linkage);
    stack->setCurrentWidget(menu);
    createGeometry();
    setCentralWidget(stack);
    //createGeometry();
//    QHBoxLayout* hboxright2 = new QHBoxLayout(this);
//    hboxright2->addWidget(stack);
//    setLayout(hboxright2);

    const QIcon newIcon = QIcon::fromTheme("document-new", QIcon(":/actions/new"));
    newAct = new QAction(newIcon, tr("&New"), this);
    const QIcon backIcon =  QIcon::fromTheme("back", QIcon(":/actions/back"));
    backAct = new QAction(backIcon, tr("back"), this);

    connect(menu->btnwinscl1, &QPushButton::clicked, this, &MainWindow::slot_to_slider_crank_linkage);
    connect(menu->btnwinscl2, &QPushButton::clicked, this, &MainWindow::slot_to_double_slider_crank_linkage);
    connect(backAct, &QAction::triggered, this, &MainWindow::slot_to_menu);


}

void MainWindow::slot_to_slider_crank_linkage()
{
    stack->setCurrentWidget(slider_crank_linkage);
    if (key == false)
    {
        key = true;
        createActions();
    }
    else
    {
        menuBar()->actions()[0]->setVisible(true);
        toolBar->setVisible(true);
    }
    createGeometry();
}

void MainWindow::slot_to_double_slider_crank_linkage()
{
    stack->setCurrentWidget(double_slider_crank_linkage);
    if (key == false)
    {
        key = true;
        createActions();
    }
    else
    {
        menuBar()->actions()[0]->setVisible(true);
        toolBar->setVisible(true);
    }
    createGeometry();
}

void MainWindow::slot_to_menu()
{
    stack->setCurrentWidget(menu);
    menuBar()->actions()[0]->setVisible(false);
    toolBar->setVisible(false);
    createGeometry();
}

//void MainWindow::slot_to_second_widget()
//{
////    menu->hide();
////    setCentralWidget(slider_crank_linkage);
////    slider_crank_linkage->show();
//    //stack->addWidget(slider_crank_linkage);
//    //slider_crank_linkage->_slot_on();
//    stack->setCurrentWidget(slider_crank_linkage);
//    slider_crank_linkage->show();
//    //stack->removeWidget(menu);
//    if (key == false)
//    {
//        key = true;
//        createActions();
//    }
//    else
//    {
//        menuBar()->actions()[0]->setVisible(true);
//        toolBar->setVisible(true);
//    }
//    createGeometry();

//}

//void MainWindow::slot_to_first_widget()
//{
//    //stack->addWidget(menu);
//    stack->setCurrentWidget(menu);
//    slider_crank_linkage->hide();
//    //stack->removeWidget(slider_crank_linkage);
//    //slider_crank_linkage->_slot_off();
////    slider_crank_linkage->hide();
//    menuBar()->actions()[0]->setVisible(false);
//    toolBar->setVisible(false);
//    //setGeometry(menu->geometry().x(), menu->geometry().y(), menu->geometry().width(), menu->geometry().height());
//    createGeometry();
////    bool answer = (menu == nullptr) ? true : false;
////    qDebug() << "is menu nullptr?" << answer << Qt::endl;
////    setFixedSize(menu->size());
////    qDebug() << "its working 1" << Qt::endl;

////    //setCentralWidget(menu);
////    menu->show();
////    qDebug() << "its working" << Qt::endl;
////    //slider_crank_linkage->show();
//}

//void MainWindow::init()
//{
//    menu = new Menu(this);
//    slider_crank_linkage = new Slider_crank_linkage(this);
//    slider_crank_linkage->hide();
//    setCentralWidget(menu);

//    connect(menu->btnwinscl1, &QPushButton::clicked, this, &MainWindow::slot_to_second_widget);
//}

void MainWindow::createActions()
{
    mainMenu = menuBar()->addMenu(tr("&File"));
    toolBar = addToolBar(tr("File"));

    backAct->setStatusTip(tr("Back to menu"));
    toolBar->addAction(backAct);

    newAct->setShortcuts(QKeySequence::New);
    newAct->setStatusTip(tr("Create a new file"));
    menu->addAction(newAct);
    toolBar->addAction(newAct);
}

void MainWindow::createGeometry()
{
    //QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding, QSizePolicy::Frame);
    //stack->setSizePolicy(sizePolicy);
    QPoint center = ((QGuiApplication::primaryScreen())->geometry()).center();
    this->setGeometry(center.x()/4, center.y()/4,
                      ((QGuiApplication::primaryScreen())->geometry()).width()/2,
                      ((QGuiApplication::primaryScreen())->geometry()).height()/2);
    if (stack->currentWidget() == menu) {
        stack->setGeometry(center.x() - menu->geometry().width()/2, center.y() - menu->geometry().height()/2,
                          700, 250);
        qDebug() << "currentIndex = 0, geomentry = " << this->geometry() << Qt::endl;
    } else {
        stack->setGeometry(center.x()/4, center.y()/4,
                          ((QGuiApplication::primaryScreen())->geometry()).width()/2,
                          ((QGuiApplication::primaryScreen())->geometry()).height()/2);
        stack->setMaximumSize((QGuiApplication::primaryScreen())->geometry().width(),
                (QGuiApplication::primaryScreen())->geometry().height());
        qDebug() << "currentIndex = 1, geomentry = " << this->geometry() << Qt::endl;
    }

}
