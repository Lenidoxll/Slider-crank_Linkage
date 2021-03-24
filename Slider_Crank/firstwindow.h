#ifndef FIRSTWINDOW_H
#define FIRSTWINDOW_H

#include <QWidget>

class QPushButton;
class QLabel;

class FirstWindow : public QWidget
{
    Q_OBJECT
public:
    explicit FirstWindow(QWidget *parent = nullptr);

public:
    QPushButton* btnwinscl1;
    QPushButton* btnwinscl2;

private:
    void createWindow();
    QLabel* label;

};

#endif // FIRSTWINDOW_H
