#ifndef MISSION_H
#define MISSION_H

#define mission_num 4

#define mission_x 0
#define mission_y 96
#define mission_schedule_x 0
#define mission_schedule_y 160

#define mission_fontsize 18
#define mission_schedule_fontsize 18

#include <QGraphicsTextItem>
#include <QTextStream>

class Mission
{
private:
    bool current_completed;
    int current_mission;
    QGraphicsTextItem *text;
    QGraphicsTextItem *text_schedule;
public:
    Mission();
    void display_mission();
    void display_mission_schedule();
    void display_updating();
    void display_mission_completed();
    void check_mission();
    void next_mission();
    bool mission_completed();
    void save_all(QTextStream &out);
    void load_all(QTextStream &in);
};

#endif // MISSION_H
