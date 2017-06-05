#include "upointer.h"
#include <QFile>
#include <QDebug>
#include <QApplication>
#include <QGraphicsPixmapItem>

UPointer::UPointer(QString mainConfDir, QObject *parent) : QObject(parent), isEditLine(false), isEditImg(false)
{
    scene=new GraphicsScene();
    confdir = mainConfDir;
    reLoad();
    QPixmap pixData(conf.backGround);
    pic = pixData;
    imgWidth = pic.width();
    imgHeight = pic.height();
    scene->addPixmap(pic);
    mainPosition.x = 0;
    mainPosition.y = 0;
    // создание таймера для анимации воздушных целей
    animationTimer=new QTimer(this);
    connect(animationTimer, SIGNAL(timeout()), scene, SLOT(advance()));
    animationTimer->start(5000);



    iPoint one=conf.airObject.at(0).airPoint.at(0);
    iPoint two=conf.airObject.at(0).airPoint.at(1);

    fPoint f=calcDelta(one, two,1000);
    AirObject* obj=new AirObject(f.x, f.y,calcAngle(one,two));
    obj->setPos(one.x,two.y);

//    QGraphicsEllipseItem* el=new QGraphicsEllipseItem(conf.airPoint.at(0).x-2,conf.airPoint.at(0).y-2,4,4);
//    el->setBrush(Qt::red);
//    QGraphicsEllipseItem* el2=new QGraphicsEllipseItem(conf.airPoint.at(1).x, conf.airPoint.at(1).y, 4,4);
//    el2->setBrush(Qt::red);
//    scene->addItem(el2);
//    scene->addItem(el);
    scene->addItem(obj);
}
GraphicsScene * UPointer::getScene() {
    return scene;
}
QString UPointer::getConfDir(){
    return confdir;
}
void UPointer::setPoint(QPoint qp){
    if(isEditImg) {
        di->position.x = qp.x();
        di->position.y = qp.y();
    }
    if(isEditLine) {
        fPoint qpF;
        qpF.x = qp.x();
        qpF.y = qp.y();
        dl->data.append(qpF);
    }
}
QString UPointer::getBg(){
    return conf.backGround;
}
void UPointer::createLine(iDataLines *dlines){
    dl = dlines;
}
void UPointer::reWrite(int width, int height){
    int picWidth = pic.width();
    int picHeight = pic.height();
    int grWidth = width;
    int grHeight = height;
    left = (qreal)(picWidth - grWidth)/2;
    top = (qreal)(picHeight - grHeight)/2;
    scene->setSceneRect(left,top,grWidth-4,grHeight-4);
    if(groupList.size() > 0){
        for(int i = 0, size = groupList.size(); i < size; i++){
            loadGroup(groupList.at(i));
        }
    }
}
void UPointer::loadGroup(int groupNumber){
    iGroup group = conf.groups[groupNumber];
    if(group.images.size() > 0) {
        for(int i = 0, size = group.images.size(); i < size; i++){
            addImg(group.images[i]);
        }
    }
    if(group.lines.size() > 0) {
        for(int i = 0, size = group.lines.size(); i < size; i++){
            addLine(group.lines[i]);
        }
    }
}
void UPointer::addImg(iDataImages image){
    QPixmap pixData(confdir+conf.imgList[image.imgNum]);
    QGraphicsPixmapItem *itm = new QGraphicsPixmapItem();
    itm->setPixmap(pixData);
    itm->setOffset(image.position.x,image.position.y);
    scene->addItem(itm);
}

qreal UPointer:: calcAngle(iPoint begin, iPoint end)
{
    qreal angle=atan((end.x-begin.x)/(end.y-begin.y));
    angle=angle*(180/3.14159)+90;
    return angle;
}

fPoint UPointer::calcDelta(iPoint begin, iPoint end,float speed)
{ fPoint f;
    float a;
    a=speed/(60.0*60.0); //1000 км/ч -> км/с
    float hyp=sqrt(pow(end.x-begin.x,2)+pow(end.y-begin.y,2));// находим общее ратояние полета (гипотенузу)
    float time=hyp/a;
    f.x=((end.x-begin.x))/time;
    f.y=((end.y-begin.y))/time;
    return f;
}

fPoint UPointer::toCoord(iPoint position){
    fPoint coord;
    float deltaX = conf.lastPosition.x - conf.zPosition.x;
    float deltaY = conf.lastPosition.y - conf.zPosition.y;
    coord.x = (float)(position.x - mainPosition.x)*deltaX/imgWidth;
    coord.y = (float)deltaY*(mainPosition.y - position.y)/imgHeight;
    return coord;
}
iPoint UPointer::fromCoord(fPoint coord){
    iPoint position;
    float deltaX = conf.lastPosition.x - conf.zPosition.x;
    float deltaY = conf.lastPosition.y - conf.zPosition.y;
    position.x = (int)(imgWidth*coord.x/deltaX);
    position.y = (int)(imgHeight*coord.y/deltaY);
    return position;
}
void UPointer::addLine(iDataLines line){
    if(line.data.size() == 0)
        return;
    QPen pen;
    pen.setColor(line.color);
    pen.setWidth(line.bold);
    for(int i = 1, size = line.data.size(); i < size; i++){
        iPoint last;
        last = fromCoord(line.data[i-1]);
        iPoint next;
        next = fromCoord(line.data[i]);
        scene->addLine(last.x,last.y,next.x,next.y,pen);
    }
}
void UPointer::setPosition(float x0,float y0,float x1,float y1){
    fPoint z;
    z.x = x0;
    z.y = y0;
    conf.zPosition = z;
    fPoint last;
    last.x = x1;
    last.y = y1;
    conf.lastPosition = last;
    save();
}
fPoint UPointer::getzPosition(){
    return conf.zPosition;
}
fPoint UPointer::getlastPosition(){
    return conf.lastPosition;
}


void UPointer::reLoad(){
    QString filename = confdir+"config.ob";
    QFile loadFile(filename);
    if(loadFile.exists()){
        if (loadFile.open(QIODevice::ReadOnly)){
            QDataStream in(&loadFile);
            in.setVersion(QDataStream::Qt_5_3);
            QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
            in >> conf;
            QApplication::restoreOverrideCursor();
        }
        loadFile.close();
    } else {
        conf.backGround = ":/img/mainMap.png";
        conf.zoom = 1.0;
        fPoint z;
        z.x = 0.0;
        z.y = 0.0;
        conf.zPosition = z;
        fPoint last;
        last.x = 0.0;
        last.y = 0.0;
        conf.lastPosition = last;

        iPoint i;
        i.x=10+967,i.y=10+603;
        iPoint j;
        j.x=150+967,j.y=150+603;
        flightRoute firstRoute;
        firstRoute.targetNumber=1;
        firstRoute.airPoint.append(i);
        firstRoute.airPoint.append(j);
        conf.airObject.append(firstRoute);
    }

}
void UPointer::setBg(QString bg){
    conf.backGround = bg;
    save();
}
void UPointer::save() {
    QString filename = confdir+"config.ob";
    QFile loadFile(filename);
    if (!loadFile.open(QIODevice::WriteOnly))
    {
        qDebug() << "Could not write to file:" << filename << "Error string:" << loadFile.errorString();
        return;
    }
    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
    QDataStream out(&loadFile);
    out.setVersion(QDataStream::Qt_5_3);
    out << conf;
    QApplication::restoreOverrideCursor();
    loadFile.close();
}
