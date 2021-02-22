#include "scene.h"
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

Scene::Scene(QObject* parent) : QGraphicsScene(parent) {}

Scene::~Scene() {}

void Scene::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    qDebug() << "It's working!!";
    if (crank1->isBelonging(event->scenePos()))
        crank1->belong = true;
    else
        crank1->belong = false;
}
