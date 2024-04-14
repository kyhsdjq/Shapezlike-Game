#ifndef MINERALWIDGET_H
#define MINERALWIDGET_H

#include <QLabel>
#include <QWidget>

#define mineralwidget_width 360
#define mineralwidget_height 64
#define mineralwidget_font 16
#define mineralwidget_margin 20

class MineralWidget: public QWidget
{
    QLabel **label;
public:
    MineralWidget();
    void refresh();
};

#endif // MINERALWIDGET_H
