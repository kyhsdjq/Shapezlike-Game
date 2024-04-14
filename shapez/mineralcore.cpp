#include "mineralcore.h"
#include <QDebug>
#include <typeinfo>
#include "game.h"
#include "grid.h"
#include <QPointF>
#include "spin_table.h"

extern int cuttable_main[];
extern int cuttable_side[];

int move_speed = 2;

MineralCore::MineralCore(int type, int x, int y, QTimer *timer, int direction, bool &helper): timer(timer), type(type)
{
//    qDebug() << x << y << type;
    helper = true;
    if(type == none_mineral){
        delete this;
        return;
    }

    setRect(0, 0, 1, 1);
    setPos(x, y);

    connect(timer, SIGNAL(timeout()), this, SLOT(move()));

    mineral = new Mineral(type);
    mineral->setPos(x - mineral_width / 2, y - mineral_height / 2);
    mineral->setZValue(1.0);
    game->scene->addItem(mineral);

    // create points vector
    QVector<QPointF> points;
    points << QPoint(0,-1) << QPoint(1,0) << QPoint(0,1) << QPoint(-1,0);

    // scale points
    int SCALE_FACTOR = mineral_width / 2;
    for (size_t i = 0, n = points.size(); i < n; i++){
        points[i] *= SCALE_FACTOR;
    }

    QList<QGraphicsItem *> colliding_items = mineral->collidingItems();
    for(int i = 0, n = colliding_items.size(); i < n; i ++)
        if(typeid(*(colliding_items[i])) == typeid(QGraphicsPolygonItem)){
//            qDebug() << "Spawn failed!";
            helper = false;
            game->scene->removeItem(mineral);
            delete mineral;
            delete this;
            return;
        }

    // create the QGraphicsPolygonItem
    collider = new QGraphicsPolygonItem(QPolygonF(points),this);
    collider->setPen(QPen(Qt::DotLine));
    collider->setPos(pos().x(), pos().y());
    collider->setZValue(0.1);
    game->scene->addItem(collider);

    switch (direction) {
    case face_up:
        v_x = 0;
        v_y = -move_speed;
        break;
    case face_right:
        v_x = move_speed;
        v_y = 0;
        break;
    case face_down:
        v_x = 0;
        v_y = move_speed;
        break;
    case face_left:
        v_x = -move_speed;
        v_y = 0;
        break;
    default:
        break;
    }

    cutted = false;
    spinned = false;
}

void MineralCore::erase()
{
    game->scene->removeItem(collider);
    delete collider;
    game->scene->removeItem(mineral);
    delete mineral;
    game->scene->removeItem(this);
    delete this;

    return;
}

void MineralCore::move()
{
    Grid *grid = 0;
    QList<QGraphicsItem *> colliding_items = mineral->collidingItems();
    int num_grid = 0;
    for(int i = 0, n = colliding_items.size(); i < n; i ++)
        if(typeid(*(colliding_items[i])) == typeid(Grid)){
            num_grid ++;
            grid = (Grid *)(colliding_items[i]);
            if(grid->get_type() == receiver)
                goto receive_label;
            else if(grid->get_type() == eraser)
                goto erase_label;
        }
    if(num_grid == 0){
        erase();
        return;
    }
    else if(num_grid == 1){
        if(!grid){
            erase();
            return;
        }
        else if(!grid->frozen_loop()){
            return;
        }
        switch(grid->get_type()){
        case conveyor: case cutter_side:
            convey_label:
            switch (grid->get_direction()) {
            case face_up:
                v_x = 0;
                v_y = -move_speed;
                break;
            case face_right:
                v_x = move_speed;
                v_y = 0;
                break;
            case face_down:
                v_x = 0;
                v_y = move_speed;
                break;
            case face_left:
                v_x = -move_speed;
                v_y = 0;
                break;
            default:
                break;
            }
            break;
        case eraser:
            erase_label:
            erase();
            return;
        case cutter_main:
            if(cutted)
                goto convey_label;
            else if(cuttable_main[type] == none_mineral){
                v_x = 0;
                v_y = 0;
            }
            else{
                MineralCore *newmineralcore;
                bool success;
                switch (grid->get_direction()){
                case face_up:
                    newmineralcore = new MineralCore(cuttable_side[type], x() + grid_width, y(), timer, grid->get_direction(), success);
                    v_x = 0;
                    v_y = 0;
//                    qDebug() << "Cut! up";
                    break;
                case face_right:
                    newmineralcore = new MineralCore(cuttable_side[type], x(), y() + grid_height, timer, grid->get_direction(), success);
                    v_x = 0;
                    v_y = 0;
//                    qDebug() << "Cut! right";
                    break;
                case face_down:
                    newmineralcore = new MineralCore(cuttable_side[type], x() - grid_width, y(), timer, grid->get_direction(), success);
                    v_x = 0;
                    v_y = 0;
//                    qDebug() << "Cut! down";
                    break;
                case face_left:
                    newmineralcore = new MineralCore(cuttable_side[type], x(), y() + grid_height, timer, grid->get_direction(), success);
                    v_x = 0;
                    v_y = 0;
//                    qDebug() << "Cut! left";
                    break;
                default:
                    break;
                }
                if(success){
                    if(cuttable_side[type] != none_mineral)
                        game->scene->addItem(newmineralcore);
                    cutted = true;
                    type = cuttable_main[type];
                    mineral->refresh(type);
                }
            }
            break;
        case spinner:
            if(spinned)
                goto convey_label;
            type = spin_table[type];
            mineral->refresh(type);
            spinned = true;
            break;
        case receiver:
            receive_label:
            game->storage->add_mineral(type);
            erase();
            return;
        default:
            v_x = 0;
            v_y = 0;
            break;
        }
    }
    else{
        cutted = false;
        spinned = false;
    }
    setPos(x() + v_x, y() + v_y);
    mineral->setPos(x() - mineral_width / 2, y() - mineral_height / 2);
    collider->setPos(x(), y());
    colliding_items = collider->collidingItems();
    for(int i = 0, n = colliding_items.size(); i < n; i ++)
        if(typeid(*(colliding_items[i])) == typeid(QGraphicsPolygonItem)){
            setPos(x() - v_x, y() - v_y);
            mineral->setPos(x() - mineral_width / 2, y() - mineral_height / 2);
            collider->setPos(x(), y());
            break;
        }

}

