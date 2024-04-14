#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include "map.h"
#include "toolbar.h"
#include "tool.h"
#include <QKeyEvent>
#include <QTimer>
#include "storage.h"
#include "mission.h"
#include "upgrader.h"
#include "moneytext.h"
#include <time.h>
#include <stdlib.h>
#include "savetext.h"
#include "loadtext.h"
#include <QTextStream>
#include "cursortracker.h"

enum{
    face_up,
    face_right,
    face_down,
    face_left
};

class Game: public QGraphicsView
{
public:
    QGraphicsScene *scene;
    Map *map;
    ToolBar *toolbar;
    int chosen_tool;
    int direction_tool;
    QTimer *timer;
    QTimer *timer_convey;
    QTimer *timer_cursor;
    Storage *storage;
    Mission *mission;
    bool upgrading;
    Upgrader *upgrader;
    MoneyText *moneytext;
    SaveText *savetext;
    LoadText *loadtext;
    CursorTracker *cursortracker;

    Game();
    void start();
    void setPixMap();
    void setMap();
    void setToolBar();
    void setStorage();
    void setMission();
    void setMoneyText();
    void setSaveText();
    void setLoadText();
    void setCursorTracker();
    void keyPressEvent(QKeyEvent * event);
    void set_upgrade_available();
    void save_all(QTextStream &out);
    void load_all(QTextStream &in);
};

extern Game *game;

#endif // GAME_H
