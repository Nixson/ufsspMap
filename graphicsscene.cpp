#include "graphicsscene.h"



GraphicsScene::GraphicsScene(QObject *parent) : QGraphicsScene()
{
    Q_UNUSED(parent);
}

GraphicsScene::~GraphicsScene()
{

}

void GraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{

    emit signalCursor(event->scenePos());
}


