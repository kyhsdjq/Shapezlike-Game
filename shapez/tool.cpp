#include "tool.h"
#include "game.h"
#include <QDebug>

Tool::Tool(int type, int direction, int special_type): QGraphicsPixmapItem()
{
    switch(type){
    case miner:
        setPixmap(QPixmap(":/pic/miner.png").scaled(62, 62));
        break;
    case conveyor:
        setPixmap(QPixmap(":/pic/conveyor.png").scaled(62, 62));
        break;
    case cutter:
        setPixmap(QPixmap(":/pic/cutter.png").scaled(62, 62));
        break;
    case cutter_main:
        setPixmap(QPixmap(":/pic/cutter_main.png").scaled(62, 62));
        break;
    case cutter_side:
        setPixmap(QPixmap(":/pic/cutter_side.png").scaled(62, 62));
        break;
    case eraser:
        setPixmap(QPixmap(":/pic/eraser.png").scaled(62, 62));
        break;
    case receiver:
        if(special_type == 0)
            setPixmap(QPixmap(":/pic/receiver.png").scaled(62, 62));
        else if(special_type == 1)
            setPixmap(QPixmap(":/pic/receiver_edge.png").scaled(62, 62));
        else if(special_type == 2)
            setPixmap(QPixmap(":/pic/receiver_content.png").scaled(62, 62));
        break;
    case spinner:
        setPixmap(QPixmap(":/pic/spinner.png").scaled(62, 62));
        break;
    default:
        break;
    }
    if(type == conveyor)
        setZValue(0.9);
    else
        setZValue(2.0);
    for(int i = 0; i < direction; i ++)
        rotate_clockwise();
}

void Tool::rotate_clockwise()
{
    setTransformOriginPoint(31, 31);
//    qDebug() << x() + tool_width / 2 << y() + tool_height / 2;
    setRotation(rotation() + 90);
}
