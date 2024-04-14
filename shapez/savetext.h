#ifndef SAVETEXT_H
#define SAVETEXT_H

#include <QGraphicsTextItem>

#define savetext_x 768
#define savetext_y 0
#define savetext_fontsize 20

class SaveText: public QGraphicsTextItem
{
public:
    SaveText();
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
};

#endif // SAVETEXT_H
