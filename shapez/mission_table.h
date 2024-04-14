#ifndef MISSION_TABLE_H
#define MISSION_TABLE_H

struct mission_node{
    int type;
    int val;
    mission_node(int type, int val): type(type), val(val){}
};

#endif // MISSION_TABLE_H
