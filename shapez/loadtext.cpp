#include "loadtext.h"
#include <QFont>
#include <QDebug>
#include <QString>
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include "game.h"
#include "grid.h"

extern int frozen_time_table[];
extern int money_table[];

LoadText::LoadText()
{
    setPlainText(QString("Load"));
    setFont(QFont("loadtest", loadtext_fontsize));
    setPos(loadtext_x, loadtext_y);
}

void LoadText::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QString file_name = QFileDialog::getOpenFileName(0, "Shapez Saver");
    QFile file(file_name);
    if(!file.open(QFile::ReadOnly | QFile::Text)){
        QMessageBox::warning(0, "Error", "Can't open the file.");
        return;
    }
    QTextStream in(&file);

    in >> move_speed;
    for(int i = 0; i < tool_type_num; i ++)
        in >> frozen_time_table[i];
    for(int i = 0; i < mineral_type_num; i ++)
        in >> money_table[i];
    game->load_all(in);
    file.close();
}
