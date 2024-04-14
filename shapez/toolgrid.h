#ifndef TOOLGRID_H
#define TOOLGRID_H

#include <QGraphicsRectItem>
#include "tool.h"

class ToolGrid: public QGraphicsRectItem
{
private:
    int type;
    Tool *tool;
public:
    ToolGrid(int type_);
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    void set_tool(int x, int y);
    void rotate_clockwise();
};

#endif // TOOLGRID_H
