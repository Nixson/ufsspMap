#include "graphicsscene.h"



GraphicsScene::GraphicsScene(QObject *parent) : QGraphicsScene()
{
    Q_UNUSED(parent);
    isCreatePath=false;
    isCreate=false;
    selectInNumberPathPoint=-1;
}

GraphicsScene::~GraphicsScene()
{

}

void GraphicsScene::drawLinePath()
{
    if(path.airPoint.size()>1){
        iPoint last=path.airPoint.at(0);
        for (auto &el : path.airPoint){
            QGraphicsLineItem* line=new QGraphicsLineItem(last.x+2, last.y+2, el.x+2, el.y+2);
            line->setPen(QPen(Qt::black));
            addItem(line);
            this->line.append(line);
            line->setZValue(1);
            last=el;
        }}

}


void GraphicsScene::setIsCreatePath(bool b)
{
    isCreatePath=b;
}

void GraphicsScene::setIsCreate(bool b)
{
    isCreate=b;
}

void GraphicsScene::createItem(QPointF point)
{
    if(isCreatePath)
    {if(isCreate){
            iPoint i;
            i.x=point.x();
            i.y=point.y();
            path.airPoint.append(i);
            //---------------------------------------------
            //later add delete line after draw
            //---------------------------------------------
            drawLinePath();
            MoveItem* item=new MoveItem();
            item->number=path.airPoint.size()-1;
            item->setPos(point.x(),point.y());
            addItem(item);
            moveItemInScene.append(item);
            signalCreateNewPathPoint();
        }}
}

void GraphicsScene::setPath(flightRoute path)
{
    this->path=path;
}

void GraphicsScene::setOGP(int i)
{
    path.OGP=i;
}

void GraphicsScene::setTypeAirObject(int i)
{
    path.typeAirObj=i;
}

flightRoute GraphicsScene::getPath()
{   return path;
}

void GraphicsScene::deleteSceneItem()
{
    for(auto &el:moveItemInScene)
        removeItem(el);
    moveItemInScene.clear();
    for(auto &el:line)
        removeItem(el);
    line.clear();
}

void GraphicsScene::drawPath()
{   int count=0;
    for(auto &el:path.airPoint){
        MoveItem* item=new MoveItem();
        item->number=path.airPoint.size()-1;
        item->setPos(el.x,el.y);
        addItem(item);
        item->setZValue(2);
        if(selectInNumberPathPoint==count++)
                item->setColor(Qt::green);
        moveItemInScene.append(item);
        drawLinePath();
    }
}

void GraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{ QList<QGraphicsItem *> foundItems = this->items(QPolygonF()<< QPointF(event->scenePos().x(), event->scenePos().y())
                                                  << QPointF(event->scenePos().x(), event->scenePos().y() + 1)
                                                  << QPointF(event->scenePos().x() + 1, event->scenePos().y() + 1)
                                                  << QPointF(event->scenePos().x() + 1, event->scenePos().y()));
    emit signalCursor(event->scenePos());
    setIsCreate(true);
    if(foundItems.isEmpty()){

    }else{
        foreach (QGraphicsItem  *item, foundItems){
            if(item->type()==123){
                setIsCreate(false);
            }}}
}

void GraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit createItem(event->scenePos());
}

void GraphicsScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    QList<QGraphicsItem *> foundItems = this->items(QPolygonF()<< QPointF(event->scenePos().x(), event->scenePos().y())
                                                    << QPointF(event->scenePos().x(), event->scenePos().y() + 1)
                                                    << QPointF(event->scenePos().x() + 1, event->scenePos().y() + 1)
                                                    << QPointF(event->scenePos().x() + 1, event->scenePos().y()));
    emit signalCursor(event->scenePos());
    setIsCreate(true);
    if(foundItems.isEmpty()){

    }else{
        foreach (QGraphicsItem  *item, foundItems){
            if(item->type()==123){
                setIsCreate(false);

            }}}
}


