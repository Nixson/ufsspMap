#include "upointer.h"
#include "iostream"
static float const PI=3.14159265358979323846;



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
    //-----------------------------------------
    //------------foreign------------------------
    QPixmap pic1=QPixmap(":/MyImage/foreign.png");
    QGraphicsPixmapItem* foreignItem=new QGraphicsPixmapItem();
    foreignItem->setPixmap(pic1);
    foreignItem->setPos(519-10,615-10);
    scene->addItem(foreignItem);
    QGraphicsPixmapItem* foreignItem2=new QGraphicsPixmapItem();
    foreignItem2->setPixmap(pic1);
    foreignItem2->setPos(544-10,645-10);
    scene->addItem(foreignItem2);
    QGraphicsPixmapItem* foreignItem3=new QGraphicsPixmapItem();
    foreignItem3->setPixmap(pic1);
    foreignItem3->setPos(517-10,743-10);
    scene->addItem(foreignItem3);
    QGraphicsPixmapItem* foreignItem4=new QGraphicsPixmapItem();
    foreignItem4->setPixmap(pic1);
    foreignItem4->setPos(590-10,748-10);
    scene->addItem(foreignItem4);

    //----------------own---------------------------------
    QPixmap pic2=QPixmap(":/MyImage/own.png");
    QGraphicsPixmapItem* OwnItem=new QGraphicsPixmapItem();
    OwnItem->setPixmap(pic2);
    OwnItem->setPos(939,750);
    scene->addItem(OwnItem);
    QGraphicsPixmapItem* OwnItem2=new QGraphicsPixmapItem();
    OwnItem2->setPixmap(pic2);
    OwnItem2->setPos(791,696);
    scene->addItem(OwnItem2);
    QGraphicsPixmapItem* OwnItem3=new QGraphicsPixmapItem();
    OwnItem3->setPixmap(pic2);
    OwnItem3->setPos(715,796);
    scene->addItem(OwnItem3);
    QGraphicsPixmapItem* OwnItem4=new QGraphicsPixmapItem();
    OwnItem4->setPixmap(pic2);
    OwnItem4->setPos(653,683);
    scene->addItem(OwnItem4);
    QGraphicsPixmapItem* OwnItem5=new QGraphicsPixmapItem();
    OwnItem5->setPixmap(pic2);
    OwnItem5->setPos(663,551);
    scene->addItem(OwnItem5);

    //-------------------KP_RTV-----------------------
    QPixmap pic4=QPixmap(":/MyImage/KP_RTV.png");
    QGraphicsPixmapItem* item4=new QGraphicsPixmapItem();
    item4->setPixmap(pic4);
    item4->setPos(667,570);
    scene->addItem(item4);

    //---------------PU_ORLR---------------------------
    QPixmap pic5=QPixmap(":/MyImage/PU-ORLR.png");
    QGraphicsPixmapItem* PuItem=new QGraphicsPixmapItem();
    PuItem->setPixmap(pic5);
    PuItem->setPos(704,480);
    scene->addItem(PuItem);
    QGraphicsPixmapItem* PuItem1=new QGraphicsPixmapItem();
    PuItem1->setPixmap(pic5);
    PuItem1->setPos(631,586);
    scene->addItem(PuItem1);
    QGraphicsPixmapItem* PuItem2=new QGraphicsPixmapItem();
    PuItem2->setPixmap(pic5);
    PuItem2->setPos(649,710);
    scene->addItem(PuItem2);
    QGraphicsPixmapItem* PuItem3=new QGraphicsPixmapItem();
    PuItem3->setPixmap(pic5);
    PuItem3->setPos(740,834);
    scene->addItem(PuItem3);

    //------------------------------------------
    mainPosition.x = 0;
    mainPosition.y = 0;
    // создание таймера для анимации воздушных целей
    animationTimer=new QTimer(this);
    connect(animationTimer, SIGNAL(timeout()), scene, SLOT(advance()));
    animationTimer->start(1000);

    //------------------------------------------
    //    MoveItem* item=new MoveItem();
    //    item->setPos(947,563);
    //    scene->addItem(item);
    //    item->setZValue(1);
    //------------------------------------------
}
GraphicsScene * UPointer::getScene() {
    return scene;
}
void UPointer::reWritePath(flightRoute path)
{   int size=conf.airObject.size();
    conf.airObject.append(path);
    conf.airObject.swap(path.targetNumber-1,size);
    conf.airObject.removeLast();
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
float UPointer:: calcAngle(iPoint begin, iPoint end)
{    float hyp=::sqrt(pow(end.x-begin.x,2)+pow(end.y-begin.y,2));
     float angle=::acos((end.x-begin.x)/hyp);
      if((end.y-begin.y)<0){
          angle=2*PI-angle;}
      while(angle<0)
          angle+=2*PI;
       while(angle>2*PI)
           angle-=2*PI;
        angle=angle*(180/PI)+90;
         return angle;
}
int UPointer::moveNumber(iPoint begin, iPoint end, float speed)
{float a;
    a=speed/(60.0*60.0); //км/ч -> км/с
    float hyp=::sqrt(pow(end.x-begin.x,2)+pow(end.y-begin.y,2));// находим общее расстояние полета (гипотенузу)
    float time=hyp/a;
    return (int)time/2;
}

fPoint UPointer::calcDelta(iPoint begin, iPoint end,float speed)
{ fPoint f;
    float a;
    a=speed/(60.0*60.0); //км/ч -> км/с
    float hyp=::sqrt(pow(end.x-begin.x,2)+pow(end.y-begin.y,2));// находим общее расстояние полета (гипотенузу)
    float time=hyp/a;
    f.x=((end.x-begin.x))/time;
    f.y=((end.y-begin.y))/time;
    return f;
}

void UPointer::drawPath(flightRoute path)
{
    for(auto &el:path.airPoint)
        scene->addEllipse(el.x,el.y,5,5,QPen(Qt::black),QBrush(Qt::green));
}

void UPointer::flight2(int num, flightRoute path)
{      if(p.airPoint.size()>(num)){
        iPoint last=path.airPoint.at(num-1);
        iPoint next=path.airPoint.at(num);
        fPoint f=calcDelta(last,next,2000);
        AirObject *obj=new AirObject(f.x,f.y,calcAngle(last,next));
        obj->setPos(last.x+3,last.y+3);
        obj->setMoveNumber(moveNumber(last,next,2000));
        obj->setColor(getColor(path.OGP));
        scene->addItem(obj);
        path.count++;
        obj->setFlightRote(path);
        obj->setCount(path.count);
        connect(obj,&AirObject::signalFinish,this, &UPointer::flight2);
    }
}

void UPointer::flight(flightRoute path)
{   iPoint last;
    this->p=path;
    path.count=1;
    if(path.airPoint.size()>1){
        last=path.airPoint.at(0);
        fPoint f=calcDelta(last,path.airPoint.at(1),2000);
        AirObject *obj=new AirObject(f.x,f.y,calcAngle(last,path.airPoint.at(1)));
        obj->setPos(last.x+3,last.y+3);
        obj->setMoveNumber(moveNumber(last,path.airPoint.at(1),2000));
        obj->setColor(getColor(path.OGP));
        scene->addItem(obj);
        path.count++;
        obj->setFlightRote(path);
        obj->setCount(path.count);
        connect(obj,&AirObject::signalFinish,this, &UPointer::flight2);
    }
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

QColor UPointer::getColor(int i)
{
    if(i==0)
        return QColor(Qt::green);
    if(i==1)
        return QColor(Qt::red);
    return QColor(Qt::lightGray);
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
void UPointer::addConfAir(flightRoute path)
{
    conf.airObject.append(path);
}
iConfig UPointer::getConfig()
{
    return conf;
}

void UPointer::drawAir()
{
    for(auto el:trainingConf.airObject){
       // drawPath(el);
        flight(el);
    }
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
            std::cout<<"I is reload"<<"\n";
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
//----------------------------------------
// Create first flightRoute
        iPoint i;
        i.x=10+967,i.y=10+603;
        iPoint j;
        j.x=120+967,j.y=45+603;
        iPoint q;
        q.x=200+967,q.y=250+603;
        flightRoute firstRoute;
        firstRoute.targetNumber=1;
        firstRoute.airPoint.append(i);
        firstRoute.airPoint.append(j);
        firstRoute.airPoint.append(q);
        firstRoute.OGP=0;
        firstRoute.typeAirObj=0;
        conf.airObject.append(firstRoute);
//-----------------------------------------
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

void UPointer::setTrainingConf(iConfig conf)
{
    this->trainingConf=conf;
}
