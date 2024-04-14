#include "game.h"
#include "grid.h"
#include <QDebug>
#include "pixmap_table.h"

Game::Game(): QGraphicsView()
{
//    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
//    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(1280,960);

    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,1024,768);
    setScene(scene);

    timer = new QTimer(this);
    timer->start(10);
    timer_convey = new QTimer(this);
    timer_convey->start(10);

    upgrading = false;

    srand((unsigned)time(0));

    timer_cursor = new QTimer(this);
    timer_cursor->start(10);
}

void Game::start()
{
    setPixMap();
    setMap();
    setToolBar();
    setStorage();
    setMission();
    setMoneyText();
    setSaveText();
    setLoadText();
    setCursorTracker();

    chosen_tool = none_tool;
    direction_tool = face_up;
}

void Game::setPixMap()
{
    mineral_pixmap_table = new QPixmap[mineral_type_num];
    for(int i = 0; i < mineral_type_num; i ++){
        switch (i) {
        case circle_mineral:
            mineral_pixmap_table[circle_mineral] = QPixmap(":/pic/circle.png");
            break;
        case rectangle_mineral:
            mineral_pixmap_table[rectangle_mineral] = QPixmap(":/pic/rectangle.png");
            break;
        case left_rectangle_mineral:
            mineral_pixmap_table[left_rectangle_mineral] = QPixmap(":/pic/left_rectangle.png");
            break;
        case right_rectangle_mineral:
            mineral_pixmap_table[right_rectangle_mineral] = QPixmap(":/pic/right_rectangle.png");
            break;
        case up_rectangle_mineral:
            mineral_pixmap_table[up_rectangle_mineral] = QPixmap(":/pic/up_rectangle.png");
            break;
        case down_rectangle_mineral:
            mineral_pixmap_table[down_rectangle_mineral] = QPixmap(":/pic/down_rectangle.png");
            break;
        case Ru______:
            mineral_pixmap_table[Ru______] = QPixmap(":/pic/Ru------.png");
            break;
        case __Ru____:
            mineral_pixmap_table[__Ru____] = QPixmap(":/pic/--Ru----.png");
            break;
        case ____Ru__:
            mineral_pixmap_table[____Ru__] = QPixmap(":/pic/----Ru--.png");
            break;
        case ______Ru:
            mineral_pixmap_table[______Ru] = QPixmap(":/pic/------Ru.png");
            break;
        default:
            break;
        }
    }
}

void Game::setMap()
{
    map = new Map(8, 16, timer, timer_convey);
    map->generte_mineral();
    map->set_receiver();
}

void Game::setToolBar()
{
    toolbar = new ToolBar;
}

void Game::setStorage()
{
    storage = new Storage;
    storage->start();
}

void Game::setMission()
{
    mission = new Mission;
}

void Game::setMoneyText()
{
    moneytext = new MoneyText;
    scene->addItem(moneytext);
}

void Game::setSaveText()
{
    savetext = new SaveText;
    scene->addItem(savetext);
}

void Game::setLoadText()
{
    loadtext = new LoadText;
    scene->addItem(loadtext);
}

void Game::setCursorTracker()
{
    cursortracker = new CursorTracker;
    connect(timer_cursor, SIGNAL(timeout()), cursortracker, SLOT(track_curse()));
}

void Game::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_R){
//        qDebug() << "R!";
//        qDebug() << direction_tool;
        if(direction_tool == face_left)
            direction_tool = face_up;
        else
            direction_tool ++;
        toolbar->rotate_clockwise();
    }
    else if(event->key() == Qt::Key_1)
        chosen_tool = miner;
    else if(event->key() == Qt::Key_2)
        chosen_tool = conveyor;
    else if(event->key() == Qt::Key_3)
        chosen_tool = cutter;
    else if(event->key() == Qt::Key_4)
        chosen_tool = eraser;
    else if(event->key() == Qt::Key_5)
        chosen_tool = spinner;
    else if(event->key() == Qt::Key_Q)
        storage->open_shopwidget();
}

void Game::set_upgrade_available()
{
    upgrader = new Upgrader;
    scene->addItem(upgrader);
}

void Game::save_all(QTextStream &out)
{
    map->save_all(out);
    storage->save_all(out);
    mission->save_all(out);
    out << upgrader << ' ' << upgrading << '\n' << '\n';
}

void Game::load_all(QTextStream &in)
{
    map->load_all(in);
    storage->load_all(in);
    mission->load_all(in);
    int address_upgrader;
    int temp_upgrading;
    in >> address_upgrader >> temp_upgrading;
    if(address_upgrader) set_upgrade_available();
    upgrading = !!temp_upgrading;
    if(upgrading) mission->display_updating();
}
