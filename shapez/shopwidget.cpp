#include "shopwidget.h"
#include <QString>
#include <QFont>
#include <QDebug>
#include <QMessageBox>
#include "mineral.h"

#include "game.h"

extern int money_table[];

#define set_comidity(name, function_name, text, x, y) \
do{ \
    name = new QPushButton(this); \
    name->setText(QString(text)); \
    name->setFont(QFont("comidity", comidity_fontsize)); \
    name->setGeometry(x, y, comidity_width, comidity_height); \
    name->show(); \
    connect(name, SIGNAL(clicked(bool)), this, SLOT(function_name())); \
} while(0);

ShopWidget::ShopWidget(QWidget *parent) : QWidget(parent)
{
    setFixedSize(360, 480);
    set_comidity(comidity1, function1, "Add price of circle. ($100)", 20, 20)
    set_comidity(comidity2, function2, "Expand the receiver. ($200)", 20, 135)
    set_comidity(comidity3, function3, "Add 4 random minerals. ($200)", 20, 250)
    set_comidity(comidity4, function4, "Expand the map. ($500)", 20, 365)
}

void ShopWidget::function1()
{
    if(game->storage->get_money() < 100){
        QMessageBox::critical(this, "ATTENTION", "Insufficient money!");
        return;
    }
    game->storage->minus_money(100);
    money_table[circle_mineral] += 5;
}

void ShopWidget::function2()
{
    if(game->storage->get_money() < 200){
        QMessageBox::critical(this, "ATTENTION", "Insufficient money!");
        return;
    }
    game->storage->minus_money(200);
    game->map->expand_receiver();
}

void ShopWidget::function3()
{
    if(game->storage->get_money() < 200){
        QMessageBox::critical(this, "ATTENTION", "Insufficient money!");
        return;
    }
    game->storage->minus_money(200);
    int mineral_type;
    do{
        mineral_type = rand() % mineral_type_num;
    } while(mineral_type == none_mineral);
    for(int i = 0; i < 4; i ++)
        game->map->add_mineral(mineral_type);
}

void ShopWidget::function4()
{
    if(game->storage->get_money() < 500){
        QMessageBox::critical(this, "ATTENTION", "Insufficient money!");
        return;
    }
    game->storage->minus_money(500);
    game->map->expand(8, 16);
}
