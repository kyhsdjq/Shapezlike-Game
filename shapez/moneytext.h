#ifndef MONEYTEXT_H
#define MONEYTEXT_H

#include <QGraphicsTextItem>

#define moneytext_x 0
#define moneytext_y 0
#define moneytext_fontsize 20

class MoneyText: public QGraphicsTextItem
{
public:
    MoneyText();
    void set_money(int money);
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
};

#endif // MONEYTEXT_H
