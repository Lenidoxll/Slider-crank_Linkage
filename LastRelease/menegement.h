#ifndef MENEGEMENT_H
#define MENEGEMENT_H

#include <QWidget>
#include "mainwindow.h"

class Menegement : public QWidget
{
    Q_OBJECT
public:
    explicit Menegement(QWidget *parent = nullptr);
    QVector < MainWindow* > manager;

protected:
    bool eventFilter(QObject *pObject, QEvent *pEvent) override;
    void _new_mainWindow();
};

#endif // MENEGEMENT_H
