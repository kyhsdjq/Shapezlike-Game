#ifndef STORAGE_H
#define STORAGE_H

#include "mineral.h"
#include "shopwidget.h"
#include "mineralwidget.h"
#include <QTextStream>

class Storage
{
private:
    ShopWidget *shopwidget;
    MineralWidget *mineralwidget;
    int mineral_num[mineral_type_num];
    int money;
public:
    Storage();
    void add_mineral(int mineral_type);
    int get_num(int mineral_type);
    int get_money();
    void minus_money(int val);
    void open_shopwidget();
    void open_mineralwidget();
    void save_all(QTextStream &out);
    void load_all(QTextStream &in);
    void start();
};

#endif // STORAGE_H
