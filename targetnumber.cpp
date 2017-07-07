#include "targetnumber.h"


TargetNumber::TargetNumber(QString number,float dx, float dy)
{
    s=number;
    this->dx=dx;
    this->dy=dy;
    count=0;
}

void TargetNumber::advance(int phase)
{   if(phase){
        if(((++count)%5)==0){
            moveBy(dx*10,dy*10);

        }
    }}

QRectF TargetNumber::boundingRect() const
{
    return QRectF(0,0,20,20);
}

void TargetNumber::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawText(QRect(0,0,20,20),s);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void TargetNumber::deleteItem()
{
    delete this;
}
