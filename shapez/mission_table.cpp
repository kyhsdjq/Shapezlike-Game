#include <QString>
#include <mineral.h>
#include "mission.h"
#include "mission_table.h"

QString mission_table_name[mission_num] = {
"produce 10 circles.",
"produce 10 rectangles.",
"produce 20 left-half rectangles.",
"produce 20 left-down rectangles."
};

mission_node mission_table_storage[mission_num] = {
mission_node(circle_mineral, 10),
mission_node(rectangle_mineral, 10),
mission_node(left_rectangle_mineral, 20),
mission_node(____Ru__, 20)
};
