#include "toolbar.h"
#include "game.h"
#include <QDebug>

#define set_tool_macro(name, x, y) \
    do{ \
        toolgrid[name] = new ToolGrid(name); \
        toolgrid[name]->setRect(0, 0, tool_width, tool_height); \
        toolgrid[name]->setPos(x, y); \
        game->scene->addItem(toolgrid[name]); \
        toolgrid[name]->set_tool(x, y); \
    } while(0);

ToolBar::ToolBar()
{
    set_tool_macro(miner, toolbar_x + 1, toolbar_y + 1)
    set_tool_macro(conveyor, toolbar_x + tool_width + 1, toolbar_y + 1)
    set_tool_macro(cutter, toolbar_x + tool_width * 2 + 1, toolbar_y + 1)
    set_tool_macro(eraser, toolbar_x + tool_width * 3 + 1, toolbar_y + 1)
    set_tool_macro(spinner, toolbar_x + tool_width * 4 + 1, toolbar_y + 1);
}

void ToolBar::rotate_clockwise()
{
    toolgrid[miner]->rotate_clockwise();
    toolgrid[conveyor]->rotate_clockwise();
    toolgrid[cutter]->rotate_clockwise();
    toolgrid[eraser]->rotate_clockwise();
    toolgrid[spinner]->rotate_clockwise();
}
