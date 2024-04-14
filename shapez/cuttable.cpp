#include "mineral.h"

int cuttable_main[mineral_type_num] = {
none_mineral,//    none_mineral,
none_mineral,//    circle_mineral,
left_rectangle_mineral,//    rectangle_mineral,
left_rectangle_mineral,//    left_rectangle_mineral
right_rectangle_mineral,//    right_rectangle_mineral
______Ru,//    up_rectangle_mineral,
____Ru__,//    down_rectangle_mineral,
Ru______,//    Ru______,
__Ru____,//    __Ru____,
____Ru__,//    ____Ru__,
______Ru//    ______Ru,
};

int cuttable_side[mineral_type_num] = {
none_mineral,//    none_mineral,
none_mineral,//    circle_mineral,
right_rectangle_mineral,//    rectangle_mineral,
none_mineral,//    left_rectangle_mineral
none_mineral,//    right_rectangle_mineral
Ru______,//    up_rectangle_mineral,
__Ru____,//    down_rectangle_mineral,
none_mineral,//    Ru______,
none_mineral,//    __Ru____,
none_mineral,//    ____Ru__,
none_mineral//    ______Ru,
};
