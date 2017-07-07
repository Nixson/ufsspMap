#include "airobject.h"
#include <QRect>

AirObject::AirObject(): QGraphicsItem()
{
    dx=2;
    dy=2;
    count=0;
    count2=0;
    moveNumber=0;
    color=QColor(Qt::white);
}

AirObject::AirObject(float dx, float dy, qreal angle): AirObject()
{   this->angle=angle;
    this->dx=dx;
    this->dy=dy;
    posX = -5;
    posY = -5;
    width = 10;
    height = 10;
    setRotation(angle);
}

AirObject::AirObject(float dx, float dy,qreal angle,int x, int y, int w, int h) : AirObject(dx,dy,angle)
{
    posX = x;
    posY = y;
    width = w;
    height = h;
}

void AirObject::setMoveNumber(int i)
{
    this->moveNumber=i;
}

QRectF AirObject::boundingRect() const
{
    return QRectF(posX,posY,width,height);   // Ограничиваем область, в которой лежит треугольник
}

void AirObject::advance(int phase)
{   if(phase){
        if(count==moveNumber){
            signalFinish(path.count, path);
            signalDelete();
            delete this;
            return;
        }
        if(((++count)%5)==0){
            moveBy(dx*10,dy*10);
            //--------------------------------------
        }
    }}

void AirObject::setFlightRote(flightRoute path)
{
    this->path=path;
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
    painter->setBrush(color);
    painter->setPen(color);
    QRect r(-2,-2,4,4);
    painter->drawEllipse(r);
    painter->drawLine(0,0,0,-10);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void AirObject::setCount(int i)
{
    this->count2=i;
}

void AirObject::setColor(QColor color)
{
    this->color=color;
}
