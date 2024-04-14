#include "upgrader.h"
#include "game.h"

Upgrader::Upgrader()
{
    setRect(0, 0, upgrader_width, upgrader_height);
    setPos(upgrader_x, upgrader_y);
    icon = new QGraphicsPixmapItem;
    icon->setPos(upgrader_x + 1, upgrader_y + 1);
    icon->setPixmap(QPixmap(":/pic/upgrader.png").scaled(62, 62));
    game->scene->addItem(icon);
}

void Upgrader::erase()
{
    game->scene->removeItem(icon);
    game->scene->removeItem(this);
    delete icon;
    delete this;
    game->upgrader = 0;
}

void Upgrader::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    game->upgrading = true;
    game->mission->display_updating();
    erase();
}


