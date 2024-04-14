#ifndef GRID_H
#define GRID_H

#include <QGraphicsRectItem>
#include "tool.h"
#include <QTimer>
#include <QObject>
#include "mineralcore.h"
#include <QTextStream>
#include <QGraphicsSceneMouseEvent>

#define grid_width 64
#define grid_height 64

class Grid: public QObject, public QGraphicsRectItem
{
    Q_OBJECT
private:
    int row, col;
    int mineral_type;
    int tool_type;
    int tool_direction;
    Tool *tool;
    QTimer *timer;
    QTimer *timer_convey;
    int max_frozen_time;
    int frozen_time;
    Mineral *mineral_img;
public:
    Grid();
    virtual ~Grid() {}
    void set_row_col(int row_, int col_);
    void set_mineral_type(int mineral_type_);
    void set_mineral_img();
    int get_mineral_type();
    void set_tool_type(int tool_type_, int tool_direction_, int special_type = 0);
    void set_tool(int special_type = 0);
    void set_timer(QTimer *timer_);
    void set_timer_convey(QTimer *timer_convey_);
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    void set_max_frozen_time();
    int get_type();
    int get_direction();
    void save_all(QTextStream &out);
    void load_all(QTextStream &in);

    bool frozen_loop();
    void erase();
public slots:
    void generate_mineral();
};

#endif // GRID_H
