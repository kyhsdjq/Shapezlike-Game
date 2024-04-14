#include "spin_table.h"
#include "mineral.h"

int spin_table[mineral_type_num]{
none_mineral,//    none_mineral,
circle_mineral,//    circle_mineral,
rectangle_mineral,//    rectangle_mineral,
up_rectangle_mineral,//    left_rectangle_mineral,
down_rectangle_mineral,//    right_rectangle_mineral,
right_rectangle_mineral,//    up_rectangle_mineral,
left_rectangle_mineral,//    down_rectangle_mineral,
__Ru____,//    Ru______,
____Ru__,//    __Ru____,
______Ru,//    ____Ru__,
Ru______,//    ______Ru,
};
