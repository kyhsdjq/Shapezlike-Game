#include "mineral.h"
#include "mineralcore.h"
#include <QDebug>
#include "pixmap_table.h"

Mineral::Mineral(int type, int width, int height, QGraphicsItem *parent): QGraphicsPixmapItem(parent), width(width), height(height)
{
//    qDebug() << width << height;
    refresh(type);
}

void Mineral::refresh(int type)
{
//    qDebug() << type;
    setPixmap(mineral_pixmap_table[type].scaled(width, height));
}
