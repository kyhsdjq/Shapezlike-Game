#include "savetext.h"
#include <QFont>
#include <QDebug>
#include <QString>
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include "game.h"

extern int frozen_time_table[];
extern int money_table[];

SaveText::SaveText()
{
    setPlainText(QString("Save"));
    setFont(QFont("savetest", savetext_fontsize));
    setPos(savetext_x, savetext_y);
}

void SaveText::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QString file_name = QFileDialog::getOpenFileName(0, "Shapez Saver");
    QFile file(file_name);
    if(!file.open(QFile::WriteOnly | QFile::Text)){
        QMessageBox::warning(0, "Error", "Can't open the file.");
        return;
    }
    QTextStream out(&file);

    out << move_speed << '\n';
    for(int i = 0; i < tool_type_num; i ++)
        out << frozen_time_table[i] << ' ';
    out << '\n' << '\n';
    for(int i = 0; i < mineral_type_num; i ++)
        out << money_table[i] << ' ';
    out << '\n' << '\n';
    game->save_all(out);
    out.flush();
    file.close();
}
