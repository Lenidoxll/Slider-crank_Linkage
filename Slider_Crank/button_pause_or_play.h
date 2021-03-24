#ifndef BUTTON_PAUSE_OR_PLAY_H
#define BUTTON_PAUSE_OR_PLAY_H

#include <QWidget>

class Button_pause_or_play : public QWidget
{
    Q_OBJECT
public:
    explicit Button_pause_or_play(QWidget *parent = nullptr);
    QIcon* pause;
};

#endif // BUTTON_PAUSE_OR_PLAY_H
