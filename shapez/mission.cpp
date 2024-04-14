#include <QDebug>

#include "mission.h"
#include "game.h"
#include "mission_table.h"

extern QString mission_table_name[];
extern mission_node mission_table_storage[];

Mission::Mission()
{
    current_completed = false;
    current_mission = 0;
    text = 0;
    text_schedule = 0;
    display_mission();
    display_mission_schedule();
}

void Mission::display_mission()
{
    if(!mission_completed()){
        if(text != 0){
            game->scene->removeItem(text);
            delete text;
            text = 0;
        }
        text = new QGraphicsTextItem;
        text->setPlainText(QString("Mission: ") + mission_table_name[current_mission]);
        text->setPos(mission_x, mission_y);
        text->setFont(QFont("mission", mission_fontsize));
        game->scene->addItem(text);
    }
}

void Mission::display_mission_schedule()
{
    if(!mission_completed()){
        if(text_schedule != 0){
            game->scene->removeItem(text_schedule);
            delete text_schedule;
            text_schedule = 0;
        }
        text_schedule = new QGraphicsTextItem;
        if(current_completed)
            text_schedule->setPlainText(QString("Mission complete. Please update."));
        else
            text_schedule->setPlainText(QString("(") + QString::number(game->storage->get_num(mission_table_storage[current_mission].type)) + QString("/") + QString::number(mission_table_storage[current_mission].val) + QString(")"));
        text_schedule->setPos(mission_schedule_x, mission_schedule_y);
        text_schedule->setFont(QFont("mission_schedule", mission_schedule_fontsize));
        game->scene->addItem(text_schedule);
    }
}

void Mission::display_updating()
{
    if(text_schedule != 0){
        game->scene->removeItem(text_schedule);
        delete text_schedule;
        text_schedule = 0;
    }
    text_schedule = new QGraphicsTextItem;
    text_schedule->setPlainText(QString("Choose a tool to update."));
    text_schedule->setPos(mission_schedule_x, mission_schedule_y);
    text_schedule->setFont(QFont("mission_schedule", mission_schedule_fontsize));
    game->scene->addItem(text_schedule);
}

void Mission::display_mission_completed()
{
    if(text != 0){
        game->scene->removeItem(text);
        delete text;
        text = 0;
    }
    if(text_schedule != 0){
        game->scene->removeItem(text_schedule);
        delete text_schedule;
        text_schedule = 0;
    }
    text = new QGraphicsTextItem;
    text->setPlainText(QString("All missions have been completed."));
    text->setPos(mission_x, mission_y);
    text->setFont(QFont("mission", mission_fontsize));
    game->scene->addItem(text);
}

void Mission::check_mission()
{
    if(mission_completed() || current_completed)
        return;
    if(game->storage->get_num(mission_table_storage[current_mission].type) >= mission_table_storage[current_mission].val){
//        qDebug() << "Mission complete!";
        game->set_upgrade_available();
        current_completed = true;
    }
    display_mission_schedule();
}

void Mission::next_mission()
{
    current_mission ++;
    if(!mission_completed()){
        current_completed = false;
        display_mission();
        display_mission_schedule();
    }
    else{
        display_mission_completed();
    }
}

bool Mission::mission_completed()
{
    return current_mission == mission_num;
}

void Mission::save_all(QTextStream &out)
{
    out << current_completed << ' ' << current_mission << '\n' << '\n';
}

void Mission::load_all(QTextStream &in)
{
    int temp_current_completed;
    in >> temp_current_completed >> current_mission;
    current_completed = !!temp_current_completed;
    if(!mission_completed()){
        display_mission();
        display_mission_schedule();
    }
    else
        display_mission_completed();
}
