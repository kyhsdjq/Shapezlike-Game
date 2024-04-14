#include <QDebug>
#include "toolgrid.h"
#include "game.h"
#include "grid.h"

extern int frozen_time_table[];

ToolGrid::ToolGrid(int type_): QGraphicsRectItem(), type(type_)
{
    tool = new Tool(type, face_up);
}

void ToolGrid::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(game->upgrading){
        if(type == cutter){
            frozen_time_table[cutter_main] /= 2;
            frozen_time_table[cutter_side] /= 2;
        }
        else if(type == conveyor){
            move_speed ++;
            if(move_speed > move_speed_max)
                move_speed --;
        }
        else
            frozen_time_table[type] /= 2;
        game->map->refresh_frozen_time();
        game->upgrading = false;
        game->mission->next_mission();
    }
    else{
        game->chosen_tool = type;
    }
    //    qDebug() << type;
}

void ToolGrid::set_tool(int x, int y)
{
    tool->setPos(x, y);
    game->scene->addItem(tool);
}

void ToolGrid::rotate_clockwise()
{
    tool->rotate_clockwise();
}

