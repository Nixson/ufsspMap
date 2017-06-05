#ifndef AIROBJECT_H
#define AIROBJECT_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include "upointer.h"



class AirObject :  public QObject, public QGraphicsItem
{
    Q_OBJECT

public:
    AirObject();
    AirObject(float dx, float dy, qreal angle);
    AirObject(float dx, float dy, qreal angle, int x, int y, int w, int h );
protected:
    QRectF boundingRect() const;
public:
    void advance(int phase);
    void setRectItem(int x, int y, int w, int h);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
private:
    int posX, posY, width, height;
    float dx;
    float dy;
    qreal angle;
};

#endif // AIROBJECT_H
