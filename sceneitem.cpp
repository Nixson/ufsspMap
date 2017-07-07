#include "sceneitem.h"


SceneItem::SceneItem(int type):QObject(), QGraphicsPixmapItem()
{
    this->type=type;
    switch (type) {
    case 1:
        pic=QPixmap(":/MyImage/foreign.png");
        break;
    case 2:
        pic=QPixmap(":/MyImage/own.png");
        break;
    case 3:
        pic=QPixmap(":/MyImage/KP_RTV.png");
        break;
    case 4:
        pic=QPixmap(":/MyImage/PU-ORLR.png");
        break;
    case 5:
        pic=QPixmap(":/MyImage/KP_RTB.png");
        break;
    default:
        pic=QPixmap();
        break;
    }
    setPixmap(pic);
}

SceneItem::~SceneItem()
{

}

int SceneItem::getType()
{
 return type;
}

