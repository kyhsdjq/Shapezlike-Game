#ifndef LOADTEXT_H
#define LOADTEXT_H

#include <QGraphicsTextItem>

#define loadtext_x 896
#define loadtext_y 0
#define loadtext_fontsize 20

class LoadText: public QGraphicsTextItem
{
public:
    LoadText();
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
};

#endif // LOADTEXT_H
