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
    void setMoveNumber(int i);
    void advance(int phase);
    void setFlightRote(flightRoute path);
    void setRectItem(int x, int y, int w, int h);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void setCount(int i);
    void setColor(QColor color);
signals:
    void signalFinish(int count, flightRoute path);
    void signalDelete();

protected:
    QRectF boundingRect() const;

private:
    int moveNumber;
    int posX, posY, width, height;
    float dx;
    float dy;
    qreal angle;
    int count;
    int count2;
    flightRoute path;
    QColor color;
};

#endif // AIROBJECT_H
