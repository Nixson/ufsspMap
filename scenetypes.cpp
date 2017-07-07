#include "scenetypes.h"


#ifndef SCENETYPES_INIT
#define SCENETYPES_INIT

QDataStream &operator<<(QDataStream &out, const iPoint &str)
{
    out << str.x;
    out << str.y;
    return out;
}
QDataStream &operator>>(QDataStream &out, iPoint &str)
{
    out >> str.x;
    out >> str.y;
    return out;
}

QDataStream &operator<<(QDataStream &out, const fPoint &str)
{
    out << str.x;
    out << str.y;
    return out;
}
QDataStream &operator>>(QDataStream &out, fPoint &str)
{
    out >> str.x;
    out >> str.y;
    return out;
}

QDataStream &operator<<(QDataStream &out, const iDataLines &str)
{
    out << str.bold;
    out << str.color;
    out << str.data;
    out << str.group;
    return out;
}
QDataStream &operator>>(QDataStream &out, iDataLines &str)
{
    out >> str.bold;
    out >> str.color;
    out >> str.data;
    out >> str.group;
    return out;
}

QDataStream &operator<<(QDataStream &out, const iDataImages &str)
{
    out << str.group;
    out << str.imgNum;
    out << str.position;
    return out;
}
QDataStream &operator>>(QDataStream &out, iDataImages &str)
{
    out >> str.group;
    out >> str.imgNum;
    out >> str.position;
    return out;
}

QDataStream &operator<<(QDataStream &out, const iGroup &str)
{
    out << str.group;
    out << str.images;
    out << str.lines;
    out << str.name;
    return out;
}
QDataStream &operator>>(QDataStream &out,flightRoute &str)
{
    out >> str.airPoint;
    out >> str.targetNumber;
    out >> str.OGP;
    out >> str.typeAirObj;
    out >> str.count;
    return out;
}
QDataStream &operator<<(QDataStream &out, const flightRoute &str)
{
    out << str.airPoint;
    out << str.targetNumber;
    out << str.OGP;
    out << str.typeAirObj;
    out << str.count;
    return out;
}
QDataStream &operator>>(QDataStream &out, iGroup &str)
{
    out >> str.group;
    out >> str.images;
    out >> str.lines;
    out >> str.name;
    return out;
}


QDataStream &operator<<(QDataStream &out, const iConfig &str)
{
    out << str.backGround;
    out << str.groups;
    out << str.imgList;
    out << str.lastPosition;
    out << str.zoom;
    out << str.zPosition;
    out << str.airObject;
    return out;
}
QDataStream &operator>>(QDataStream &out, iConfig &str)
{
    out >> str.backGround;
    out >> str.groups;
    out >> str.imgList;
    out >> str.lastPosition;
    out >> str.zoom;
    out >> str.zPosition;
    out >> str.airObject;
    return out;
}


#endif // SCENETYPES_INIT
