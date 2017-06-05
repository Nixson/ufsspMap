#include "airobject.h"
#include <QRect>

AirObject::AirObject(): QGraphicsItem()
{
    dx=2;
    dy=2;

}

AirObject::AirObject(float dx, float dy, qreal angle): AirObject()
{   this->angle=angle;
//    this->dx=1;
//    this->dy=1;
    this->dx=dx;
    this->dy=dy;
    posX = -10;
    posY = -10;
    width = 20;
    height = 20;
    setRotation(angle);
}

AirObject::AirObject(float dx, float dy,qreal angle,int x, int y, int w, int h) : AirObject(dx,dy,angle)
{
    posX = x;
    posY = y;
    width = w;
    height = h;
}

QRectF AirObject::boundingRect() const
{
    return QRectF(posX,posY,width,height);   // Ограничиваем область, в которой лежит треугольник
}

void AirObject::advance(int phase)
{
    if(phase)
        moveBy(dx*10,dy*10);
}

void AirObject::setRectItem(int x, int y, int w, int h)
{
    posX = x;
    posY = y;
    width = w;
    height = h;
}

void AirObject::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::white);
    painter->setPen(Qt::white);
    QRect r(-2,-2,4,4);
    painter->drawEllipse(r);
    painter->drawLine(0,0,0,-10);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}
