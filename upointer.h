
#ifndef UPOINTER_H
#define UPOINTER_H

#include <iostream>
#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsLineItem>
#include <QTimer>
#include <QFile>
#include <QDebug>
#include <QApplication>

#include <math.h>

#include "graphicsscene.h"
#include "scenetypes.h"
#include "airobject.h"
#include "moveitem.h"
#include "sceneitem.h"
#include "targetnumber.h"


static float const PI=3.14159265358979323846;

class UPointer : public QObject
{
    Q_OBJECT
public:
    void reWritePath(flightRoute path);
    explicit UPointer(QString mainConfDir, QObject *parent = 0);
    void reWrite(int width, int height);
    GraphicsScene * getScene();
    QString getConfDir();
    void setBg(QString bg);
    QString getBg();
    void setPoint(QPoint qp);
    void createLine(iDataLines *dlines);
    void setPosition(float x0,float y0,float x1,float y1);
    fPoint getzPosition();
    fPoint getlastPosition();
    void addConfAir(flightRoute path);
    iConfig getConfig();
    void drawAir();
    void save();
    void setTrainingConf(iConfig conf);
    void setAirObjectConf(iConfig conf);
 //   void reLoad();

signals:   
public slots:
 void airfieldAll();
 void airfieldOwn();
 void airfieldForeign();
 void flight2(int num, flightRoute path);
private:
    fPoint calcDelta(iPoint begin,iPoint end, float speed);
    void drawPath(flightRoute path);
    flightRoute p;
    void flight(flightRoute path);
    qreal left;
    qreal top;
    QPixmap pic;
    GraphicsScene *scene;
    void reLoad();

    iConfig conf;
    iConfig trainingConf;
    QList <int> groupList;
    void loadGroup(int groupNumber);
    void addLine(iDataLines line);
    void addImg(iDataImages image);
    int imgWidth;
    int imgHeight;
    iPoint mainPosition;
    float calcAngle(iPoint begin, iPoint end);
    QTimer* animationTimer;
    int moveNumber(iPoint begin, iPoint end,float speed);
    fPoint toCoord(iPoint position);
    iPoint fromCoord(fPoint position);
    QString confdir;
    bool isEditLine;
    bool isEditImg;
    iDataLines *dl;
    iDataImages *di;
    QColor getColor(int i);
    QList <SceneItem*> itemSceneList;
    bool isAirfieldAll;
    bool isAirfieldOwn;
    bool isAirfieldForeign;
};

#endif // UPOINTER_H
