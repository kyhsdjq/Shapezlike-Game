#include "storage.h"
#include <QDebug>
#include "game.h"

extern int money_table[];

Storage::Storage()
{
    for(int i = 0; i < mineral_type_num; i ++)
        mineral_num[i] = 0;
    money = 0;

    shopwidget = new ShopWidget;
    mineralwidget = new MineralWidget;
}

void Storage::add_mineral(int mineral_type)
{
    mineral_num[mineral_type] ++;
    money += money_table[mineral_type];
    game->moneytext->set_money(money);
    mineralwidget->refresh();
//    qDebug() << "Received!";
    game->mission->check_mission();
}

int Storage::get_num(int mineral_type)
{
    return mineral_num[mineral_type];
}

int Storage::get_money()
{
    return money;
}

void Storage::minus_money(int val)
{
    money -= val;
    game->moneytext->set_money(money);
}

void Storage::open_shopwidget()
{
    shopwidget->show();
    shopwidget->activateWindow();
    shopwidget->raise();
}

void Storage::open_mineralwidget()
{
    mineralwidget->show();
    mineralwidget->activateWindow();
    mineralwidget->raise();
}

void Storage::save_all(QTextStream &out)
{
    out << money << '\n';
    for(int i = 0; i < mineral_type_num; i ++)
        out << mineral_num[i] << ' ';
    out << '\n' << '\n';
}

void Storage::load_all(QTextStream &in)
{
    in >> money;
    for(int i = 0; i < mineral_type_num; i ++)
        in >> mineral_num[i];
    game->moneytext->set_money(money);
}

void Storage::start()
{
    mineralwidget->refresh();
}
