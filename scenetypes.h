#ifndef SCENETYPES_H
#define SCENETYPES_H

#include <QDataStream>
#include <QColor>

typedef struct iPoint_str {
    int x;
    int y;
} iPoint;

typedef struct fPoint_str {
    float x;
    float y;
} fPoint;

typedef struct iDataLines_str {
    int group;
    int bold;
    QColor color;
    QList <fPoint> data;
} iDataLines;

typedef struct iDataImages_str {
    int group;
    int imgNum;
    fPoint position;
} iDataImages;

typedef struct iGroup_str {
    int group;
    QString name;
    QList <iDataLines> lines;
    QList <iDataImages> images;
} iGroup;

typedef struct flightRoute_str {
    QList <iPoint> airPoint;
    qreal targetNumber;
}flightRoute;

typedef struct iConfig_str {
    QString backGround;
    QList <QString> imgList;
    float zoom;
    fPoint zPosition;
    fPoint lastPosition;
    QList <iGroup> groups;
    QList<flightRoute>airObject;
} iConfig;


QDataStream &operator<<(QDataStream &out, const fPoint &str);
QDataStream &operator>>(QDataStream &out, fPoint &str);

QDataStream &operator<<(QDataStream &out, const iPoint &str);
QDataStream &operator>>(QDataStream &out, iPoint &str);

QDataStream &operator<<(QDataStream &out, const iDataLines &str);
QDataStream &operator>>(QDataStream &out, iDataLines &str);

QDataStream &operator<<(QDataStream &out, const iDataImages &str);
QDataStream &operator>>(QDataStream &out, iDataImages &str);

QDataStream &operator<<(QDataStream &out, const iGroup &str);
QDataStream &operator>>(QDataStream &out, iGroup &str);

QDataStream &operator<<(QDataStream &out, const iConfig &str);
QDataStream &operator>>(QDataStream &out, iConfig &str);
#endif // SCENETYPES_H
