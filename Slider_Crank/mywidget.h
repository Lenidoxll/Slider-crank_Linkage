#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QIcon>
#include "mainwidget.h"

class QToolButton;
class QPushButton;
class Plot;
class MyWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MyWidget(QWidget *parent = nullptr);
public:
    QToolButton* pause_or_play;
    QPushButton* mechanism_or_graphic;
private:
    enum status_pause_or_play {
        PAUSE,
        PLAY
    };
    enum status_mechanism_or_graphic {
        MECHANISM,
        GRAPHIC
    };

    status_pause_or_play current_stats_pause_or_play = PLAY;
    status_mechanism_or_graphic current_stats_mechanism_or_graphic = MECHANISM;
    QIcon pause = QIcon(":/new/buttons/pause");
    QIcon play = QIcon(":/new/buttons/play");
    QHBoxLayout* hbox;
    QLabel* label;
    QLineEdit* lineedit;
    MainWidget* mainw;
    Plot* plot;
    QHBoxLayout* hboxright2;
private slots:
    void _slot_pause_or_play();
    void _slot_mechanism_or_graphic();
    void _slot_xBChanged();
};

#endif // MYWIDGET_H
