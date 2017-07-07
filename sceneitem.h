#ifndef SCENEITEM_H
#define SCENEITEM_H

#include <QGraphicsPixmapItem>

static int const FOREIGN=1;
static int const OWN=2;
static int const KP_RTV=3;
static int const PU_ORLR=4;

class SceneItem : public QObject, public QGraphicsPixmapItem
{
public:
    SceneItem(int type);
    ~SceneItem();
    int getType();

private:
    int type;
    QPixmap pic;
};

#endif // SCENEITEM_H
