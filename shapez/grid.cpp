#include "grid.h"
#include <QDebug>
#include "game.h"
#include <typeinfo>
#include "mineralcore.h"
#include <QApplication>

extern int frozen_time_table[];

Grid::Grid(): QObject(), QGraphicsRectItem()
{
    mineral_type = none_mineral;
    tool_type = none_tool;
    tool_direction = face_up;

    set_max_frozen_time();
    frozen_time = 0;
    tool = 0;
    mineral_img = 0;
}

void Grid::set_row_col(int row_, int col_)
{
    row = row_;
    col = col_;
}

void Grid::set_mineral_type(int mineral_type_)
{
    mineral_type = mineral_type_;
    set_mineral_img();
}

void Grid::set_mineral_img()
{
    if(mineral_img != 0){
        game->scene->removeItem(mineral_img);
        delete mineral_img;
        mineral_img = 0;
    }
    if(mineral_type != none_mineral){
        mineral_img = new Mineral(mineral_type, 62, 62);
        mineral_img->setPos(x() + 1, y() + 1);
        game->scene->addItem(mineral_img);
        mineral_img->setZValue(0.5);
    }
}

int Grid::get_mineral_type()
{
    return mineral_type;
}

void Grid::set_tool_type(int tool_type_, int tool_direction_, int special_type)
{
    if(tool != 0){
        game->scene->removeItem(tool);
        delete tool;
        tool = 0;
    }
    tool_type = tool_type_;
    set_max_frozen_time();
    tool_direction = tool_direction_;
    set_tool(special_type);
}

void Grid::set_tool(int special_type)
{
    if(tool != 0){
        game->scene->removeItem(tool);
        delete tool;
        tool = 0;
    }
    tool = new Tool(tool_type, tool_direction, special_type);
    tool->setPos(x() + 1, y() + 1);
    game->scene->addItem(tool);
}

void Grid::set_timer(QTimer *timer_){
    timer = timer_;
    connect(timer, SIGNAL(timeout()), this, SLOT(generate_mineral()));
}

void Grid::set_timer_convey(QTimer *timer_convey_){
    timer_convey = timer_convey_;
}

void Grid::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
//    qDebug() << x() << y();
    if(tool_type == none_tool && event->button() == Qt::MouseButton::LeftButton){
        if(game->chosen_tool == cutter){
            Grid *side = 0;
            switch (game->direction_tool) {
            case face_up:
                if(game->map->check_legal(row, col + 1))
                    side = game->map->grid[row][col + 1];
                break;
            case face_right:
                if(game->map->check_legal(row + 1, col))
                    side = game->map->grid[row + 1][col];
                break;
            case face_down:
                if(game->map->check_legal(row, col - 1))
                    side = game->map->grid[row][col - 1];
                break;
            case face_left:
                if(game->map->check_legal(row - 1, col))
                    side = game->map->grid[row - 1][col];
                break;
            default:
                break;
            }
            if(!side) return;
            if(side->tool_type == none_tool){
                tool_type = cutter_main;
                set_max_frozen_time();
                tool_direction = game->direction_tool;
                Tool *tool_main = new Tool(tool_type, tool_direction);
                tool_main->setPos(x() + 1, y() + 1);
                game->scene->addItem(tool_main);

                side->tool_type = cutter_side;
                side->set_max_frozen_time();
                side->tool_direction = game->direction_tool;
                Tool *tool_side = new Tool(side->tool_type, side->tool_direction);
                tool_side->setPos(side->x() + 1, side->y() + 1);
                game->scene->addItem(tool_side);
                tool = tool_main;
                side->tool = tool_side;
                tool_main->setZValue(2.0);
                tool_side->setZValue(2.0);
                game->chosen_tool = none_tool;
            }
        }
        else{
            tool_type = game->chosen_tool;
            set_max_frozen_time();
            tool_direction = game->direction_tool;
            tool = new Tool(tool_type, tool_direction);
            tool->setPos(x() + 1, y() + 1);
            game->scene->addItem(tool);
            if(tool_type == conveyor)
                tool->setZValue(0.9);
            else
                tool->setZValue(2.0);
            Qt::KeyboardModifiers modifier = QApplication::keyboardModifiers();
            if(!QApplication::keyboardModifiers().testFlag(Qt::ShiftModifier)) {
                game->chosen_tool = none_tool;
            }
        }
    }
    else if(tool_type == receiver && event->button()== Qt::MouseButton::LeftButton){
        game->storage->open_mineralwidget();
        return;
    }
    else if(tool_type != none_tool && tool_type != receiver && event->button() == Qt::MouseButton::RightButton){
        if(tool_type == cutter_main){
            Grid *side = 0;
            switch (tool_direction) {
            case face_up:
                side = game->map->grid[row][col + 1];
                break;
            case face_right:
                side = game->map->grid[row + 1][col];
                break;
            case face_down:
                side = game->map->grid[row][col - 1];
                break;
            case face_left:
                side = game->map->grid[row - 1][col];
                break;
            default:
                break;
            }
            game->scene->removeItem(tool);
            delete tool;
            tool_type = none_tool;
            game->scene->removeItem(side->tool);
            delete side->tool;
            side->tool_type = none_tool;
            QList<QGraphicsItem *> colliding_items = collidingItems();
            for(int i = 0, n = colliding_items.size(); i < n; i ++)
                if(typeid(*(colliding_items[i])) == typeid(MineralCore))
                    ((MineralCore *)(colliding_items[i]))->erase();
            colliding_items = side->collidingItems();
            for(int i = 0, n = colliding_items.size(); i < n; i ++)
                if(typeid(*(colliding_items[i])) == typeid(MineralCore))
                    ((MineralCore *)(colliding_items[i]))->erase();
        }
        else if(tool_type == cutter_side){
            Grid *side = 0;
            switch (tool_direction) {
            case face_up:
                side = game->map->grid[row][col - 1];
                break;
            case face_right:
                side = game->map->grid[row - 1][col];
                break;
            case face_down:
                side = game->map->grid[row][col + 1];
                break;
            case face_left:
                side = game->map->grid[row + 1][col];
                break;
            default:
                break;
            }
            game->scene->removeItem(tool);
            delete tool;
            tool_type = none_tool;
            game->scene->removeItem(side->tool);
            delete side->tool;
            side->tool_type = none_tool;
            QList<QGraphicsItem *> colliding_items = collidingItems();
            for(int i = 0, n = colliding_items.size(); i < n; i ++)
                if(typeid(*(colliding_items[i])) == typeid(MineralCore))
                    ((MineralCore *)(colliding_items[i]))->erase();
            colliding_items = side->collidingItems();
            for(int i = 0, n = colliding_items.size(); i < n; i ++)
                if(typeid(*(colliding_items[i])) == typeid(MineralCore))
                    ((MineralCore *)(colliding_items[i]))->erase();
        }
        else{
            game->scene->removeItem(tool);
            delete tool;
            tool_type = none_tool;
            QList<QGraphicsItem *> colliding_items = collidingItems();
            for(int i = 0, n = colliding_items.size(); i < n; i ++)
                if(typeid(*(colliding_items[i])) == typeid(MineralCore))
                    ((MineralCore *)(colliding_items[i]))->erase();
        }
    }
    else if(tool_type == none_tool && event->button() == Qt::MouseButton::RightButton){
        game->chosen_tool = none_tool;
    }
}

void Grid::set_max_frozen_time()
{
    max_frozen_time = frozen_time_table[tool_type];
}

int Grid::get_type()
{
    return tool_type;
}

int Grid::get_direction()
{
    return tool_direction;
}

void Grid::save_all(QTextStream &out)
{
    out << mineral_type << ' ' << tool_type << ' ' << tool_direction << '\n' << '\n';
}

void Grid::load_all(QTextStream &in)
{
    in >> mineral_type >> tool_type >> tool_direction;
    set_max_frozen_time();
    set_mineral_img();
    set_tool();
}

bool Grid::frozen_loop()
{
    if(frozen_time == 0){
        frozen_time = max_frozen_time;
        return true;
    }
    else
    {
        frozen_time --;
        return false;
    }

}

void Grid::erase()
{
    if(tool){
        game->scene->removeItem(tool);
        delete tool;
    }
    if(mineral_img){
        game->scene->removeItem(mineral_img);
        delete mineral_img;
    }

    game->scene->removeItem(this);
    delete this;
}

void Grid::generate_mineral()
{
//    if(tool_type == miner)
//        qDebug() << row << col << mineral_type;
    if(tool_type == miner && mineral_type != none_mineral && frozen_loop()){
//        qDebug() << "Try to generate!";
        QList<QGraphicsItem *> colliding_items = collidingItems();
        for(int i = 0, n = colliding_items.size(); i < n; i ++)
            if(typeid(*(colliding_items[i])) == typeid(QGraphicsPolygonItem))
                    return;
        int xx = x() + grid_width / 2, yy = y() + grid_height / 2;
        int offset_x = grid_width / 2 - mineral_width / 2;
        int offset_y = grid_height / 2 - mineral_height / 2;
        switch (tool_direction) {
        case face_up:
            yy -= offset_y;
            break;
        case face_right:
            xx += offset_x;
            break;
        case face_down:
            yy += offset_y;
            break;
        case face_left:
            xx -= offset_x;
            break;
        default:
            break;
        }
        bool success;
        MineralCore *mineral = new MineralCore(mineral_type, xx, yy, timer_convey, tool_direction, success);
        if(success)
            game->scene->addItem(mineral);
//        qDebug() << "Generate!";
    }
}
