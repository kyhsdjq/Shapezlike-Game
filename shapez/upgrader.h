#ifndef UPGRADER_H
#define UPGRADER_H

#include <QGraphicsRectItem>
#include <QGraphicsPixmapItem>

#define upgrader_x 640
#define upgrader_y 96
#define upgrader_width 64
#define upgrader_height 64

class Upgrader: public QGraphicsRectItem
{
private:
    QGraphicsPixmapItem *icon;
public:
    Upgrader();
    void erase();
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
};

#endif // UPGRADER_H
