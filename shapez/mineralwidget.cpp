#include "mineralwidget.h"
#include "mineral.h"
#include "mineral_table.h"
#include "game.h"
#include <QFont>
#include <QDebug>

MineralWidget::MineralWidget()
{
    setFixedSize(2 * mineralwidget_margin + mineralwidget_width, mineralwidget_margin + (mineral_type_num - 1) * (mineralwidget_height + mineralwidget_margin));
    label = new QLabel *[mineral_type_num];
    for(int i = 1; i < mineral_type_num; i ++){
        label[i] = new QLabel(this);
        label[i]->setFont(QFont("mineralwidgetlabel", mineralwidget_font));
        label[i]->setGeometry(mineralwidget_margin, mineralwidget_margin + (i - 1) * (mineralwidget_height + mineralwidget_margin), mineralwidget_width, mineralwidget_height);
    }
}

void MineralWidget::refresh()
{
    for(int i = 1; i < mineral_type_num; i ++)
        label[i]->setText(mineral_name_table[i] + QString(": ") + QString::number(game->storage->get_num(i)));
}
