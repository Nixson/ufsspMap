#ifndef TARGETNUMBER_H
#define TARGETNUMBER_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include "upointer.h"

class TargetNumber:  public QObject, public QGraphicsItem
{
public:
    TargetNumber(QString number,float dx, float dy);
    // QGraphicsItem interface
    void advance(int phase) override;
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
private:
    QString s;
    float dx,dy;
    int count;
public slots:
     void deleteItem();
};

#endif // TARGETNUMBER_H
