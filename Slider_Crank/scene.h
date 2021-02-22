#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include "crank.h"

class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Scene(QObject *parent = nullptr);
    ~Scene();

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

    Crank* crank1;
};

#endif // SCENE_H
