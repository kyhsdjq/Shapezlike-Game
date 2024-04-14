#ifndef MINERAL_H
#define MINERAL_H

#include <QGraphicsPixmapItem>

#define mineral_width 36
#define mineral_height 36


enum{
    none_mineral,
    circle_mineral,
    rectangle_mineral,
    left_rectangle_mineral,
    right_rectangle_mineral,
    up_rectangle_mineral,
    down_rectangle_mineral,
    Ru______,
    __Ru____,
    ____Ru__,
    ______Ru,


    end_mineral
};

#define mineral_type_num end_mineral

class Mineral: public QGraphicsPixmapItem
{
private:
    int width, height;
public:
    Mineral(int type, int width = mineral_width, int height = mineral_height, QGraphicsItem *parent = 0);
    void refresh(int type);
};

#endif // MINERAL_H
