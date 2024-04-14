#ifndef MINERALCORE_H
#define MINERALCORE_H

#include "mineral.h"
#include <QGraphicsRectItem>
#include <QTimer>
#include <QObject>
#include <QGraphicsPolygonItem>

extern int move_speed;

#define move_speed_max (grid_width - mineral_width - 1)

class MineralCore: public QObject, public QGraphicsRectItem
{
    Q_OBJECT
private:
    Mineral *mineral;
    int type;
    int v_x;
    int v_y;
    bool cutted;
    bool spinned;
    QTimer *timer;
    QGraphicsPolygonItem *collider;
public:
    MineralCore(int type, int x, int y, QTimer *timer, int direction, bool &helper);
    void erase();

public slots:
    void move();
};

#endif // MINERALCORE_H
