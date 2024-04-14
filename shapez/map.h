#ifndef MAP_H
#define MAP_H

#include "grid.h"
#include <QTextStream>

#define map_x 0
#define map_y 224

#define receiver_x 2
#define receiver_y 10

class Map
{
private:
    int rows, cols; 
    int receiver_size;
    QTimer *timer, *timer_convey;
public:
    Grid ***grid;
    Map(int rows_, int cols_, QTimer *timer, QTimer *timer_convey);
    void expand(int rows_, int cols_);
    void expand_receiver();
    void generte_mineral();
    void add_mineral(int mineral_type);
    void set_receiver();
    bool check_legal(int i, int j);
    void refresh_frozen_time();
    void save_all(QTextStream &out);
    void load_all(QTextStream &in);
    void erase();
};

#endif // MAP_H
