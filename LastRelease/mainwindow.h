#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QToolBar>
#include <QAction>
#include <QStackedWidget>
#include "menu.h"
#include "double_slider_crank_linkage.h"
#include "slider_crank_linkage.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    int getIdentification() { return identification; }
    void setIdentification(int i) { identification = i; }
    QAction *newAct;
    QAction *backAct;

private:
    Menu* menu;
    Slider_crank_linkage* slider_crank_linkage;
    Double_slider_crank_linkage* double_slider_crank_linkage;
    QMenu* mainMenu;
    QToolBar* toolBar;
    QStackedWidget *stack;

private slots:
    void slot_to_slider_crank_linkage();
    void slot_to_double_slider_crank_linkage();
    void slot_to_menu();
private:
    void createActions();
    void createGeometry();

    bool key = false;
    int identification;
};

#endif // MAINWINDOW_H
