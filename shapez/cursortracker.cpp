#include "cursortracker.h"
#include "game.h"
#include <QCursor>
#include <QDebug>
#include <QGraphicsRectItem>
#include <typeinfo>

CursorTracker::CursorTracker()
{
    tool = 0;
}

void CursorTracker::track_curse()
{
//    qDebug() << "Track!";
    if(tool != 0){
        game->scene->removeItem(tool);
        delete tool;
        tool = 0;
    }

    QPointF cursor = game->mapToScene(game->mapFromGlobal(QCursor::pos()));

    QGraphicsRectItem colliding_box;
    colliding_box.setRect(0, 0, 1, 1);
    colliding_box.setPos(cursor.x(), cursor.y());
    game->scene->addItem(&colliding_box);

    Grid *grid = 0;
    QList<QGraphicsItem *> colliding_items = colliding_box.collidingItems();
    int num_grid = 0;
    for(int i = 0, n = colliding_items.size(); i < n; i ++)
        if(typeid(*(colliding_items[i])) == typeid(Grid)){
            num_grid ++;
            grid = (Grid *)(colliding_items[i]);
        }
    if(num_grid == 1 && grid->get_type() == none_tool){
        tool = new Tool(game->chosen_tool, game->direction_tool);
        tool->setPos(grid->x() + 1, grid->y() + 1);
        game->scene->addItem(tool);
    }
    game->scene->removeItem(&colliding_box);
}
