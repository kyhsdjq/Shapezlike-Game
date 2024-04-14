#ifndef TOOL_H
#define TOOL_H

#include <QGraphicsPixmapItem>

#define tool_width 64
#define tool_height 64

enum{
    none_tool,
    miner,
    conveyor,
    cutter,
    cutter_main,
    cutter_side,
    eraser,
    receiver,
    spinner,


    end_tool
};

#define tool_type_num end_tool

class Tool: public QGraphicsPixmapItem
{
public:
    Tool(int type, int direction, int special_type = 0);

    void rotate_clockwise();
};

#endif // TOOL_H
