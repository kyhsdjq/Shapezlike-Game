#include "moneytext.h"
#include <QFont>
#include "game.h"

MoneyText::MoneyText()
{
    set_money(0);
    setFont(QFont("moneytext", moneytext_fontsize));
    setPos(moneytext_x, moneytext_y);
}

void MoneyText::set_money(int money)
{
    setPlainText(QString("Money: $") + QString::number(money));
}

void MoneyText::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    game->storage->open_shopwidget();
}
