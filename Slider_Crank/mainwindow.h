#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "mywidget.h"
#include "firstwindow.h"
#include <QMainWindow>
#include <QMouseEvent>

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

    FirstWindow* firstw;
    MyWidget* myw;

private slots:
    void _to_mywidget();
    //void _to_firstwindow();
};

#endif // MAINWINDOW_H
