#ifndef MENU_H
#define MENU_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QPushButton;
class QLabel;
class QFont;
QT_END_NAMESPACE

class Menu : public QWidget
{
    Q_OBJECT
public:
    explicit Menu(QWidget *parent = nullptr);

public:
    QPushButton* btnwinscl1;
    QPushButton* btnwinscl2;

private:
    void resizeEvent(QResizeEvent* event) override;

    void createWindow();
    QLabel* label;
    QFont font;
};

#endif // MENU_H
