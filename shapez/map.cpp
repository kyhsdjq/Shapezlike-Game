#include "map.h"

#include "game.h"
#include <QDebug>
#include <QGraphicsPixmapItem>
#include <QMessageBox>

//Map::Map()
//{

//}

Map::Map(int rows_, int cols_, QTimer *timer, QTimer *timer_convey): rows(rows_), cols(cols_), timer(timer), timer_convey(timer_convey)
{
    int x = map_x, y = map_y;
    grid = new Grid **[rows];
    for(int i = 0; i < rows; i ++)
        grid[i] = new Grid*[cols];
    for(int i = 0; i < rows; i ++){
        for(int j = 0; j < cols; j ++){
            grid[i][j] = new Grid;
            grid[i][j]->set_row_col(i, j);
            grid[i][j]->setRect(0, 0, grid_width, grid_height);
            grid[i][j]->setPos(x, y);
            grid[i][j]->set_timer(timer);
            grid[i][j]->set_timer_convey(timer_convey);
            grid[i][j]->setZValue(3.0);
            game->scene->addItem(grid[i][j]);
            x += grid_width;
        }
        x = 0;
        y += grid_height;
    }
    receiver_size = 2;
}

void Map::expand(int rows_, int cols_)
{
    if(rows_ < 0 || cols_ < 0)
        return;
    rows_ += rows;
    cols_ += cols;
    int x = map_x, y = map_y;
    Grid ***new_grid;
    new_grid = new Grid **[rows_];
    for(int i = 0; i < rows_; i ++)
        new_grid[i] = new Grid*[cols_];
    for(int i = 0; i < rows_; i ++){
        for(int j = 0; j < cols_; j ++){
            if(i < rows && j < cols)
                new_grid[i][j] = grid[i][j];
            else{
                new_grid[i][j] = new Grid;
                new_grid[i][j]->set_row_col(i, j);
                new_grid[i][j]->setRect(0, 0, grid_width, grid_height);
                new_grid[i][j]->setPos(x, y);
                new_grid[i][j]->set_timer(timer);
                new_grid[i][j]->set_timer_convey(timer_convey);
                new_grid[i][j]->setZValue(3.0);
                game->scene->addItem(new_grid[i][j]);
            }
            x += grid_width;
        }
        x = 0;
        y += grid_height;
    }
    rows = rows_;
    cols = cols_;
    grid = new_grid;
    game->scene->setSceneRect(0, 0, cols * grid_width, map_y + rows * grid_height);
}

void Map::expand_receiver()
{
    if(receiver_x + receiver_size < rows && receiver_y + receiver_size < cols){
        receiver_size ++;
        set_receiver();
    }
    else{
        game->storage->minus_money(-200);
        QMessageBox::critical(0, "ATTENTION", "The receiver can't be expanded any more!");
    }
}

void Map::generte_mineral()
{
    grid[0][0]->set_mineral_type(circle_mineral);
    grid[0][1]->set_mineral_type(circle_mineral);
    grid[1][0]->set_mineral_type(circle_mineral);
    grid[1][1]->set_mineral_type(circle_mineral);

    grid[4][0]->set_mineral_type(rectangle_mineral);
    grid[5][0]->set_mineral_type(rectangle_mineral);
    grid[4][1]->set_mineral_type(rectangle_mineral);
    grid[5][1]->set_mineral_type(rectangle_mineral);
}

void Map::add_mineral(int mineral_type)
{
    QGraphicsPixmapItem *img;
    int i, j;
    int flag = 50;
    do{
        i = rand() % rows;
        j = rand() % cols;
        if(--flag == 0) return;
    } while(grid[i][j]->get_mineral_type() != none_mineral);
    grid[i][j]->set_mineral_type(mineral_type);
}

void Map::set_receiver()
{
    int x = receiver_x, y = receiver_y;
    grid[x][y]->set_tool_type(receiver, face_left, 0);
    grid[x][y + receiver_size - 1]->set_tool_type(receiver, face_up, 0);
    grid[x + receiver_size - 1][y]->set_tool_type(receiver, face_down, 0);
    grid[x + receiver_size - 1][y + receiver_size - 1]->set_tool_type(receiver, face_right, 0);
    for(int i = 1; i < receiver_size - 1; i ++)
            grid[x][y + i]->set_tool_type(receiver, face_up, 1);
    for(int i = 1; i < receiver_size - 1; i ++)
            grid[x + receiver_size - 1][y + i]->set_tool_type(receiver, face_down, 1);
    for(int i = 1; i < receiver_size - 1; i ++)
            grid[x + i][y]->set_tool_type(receiver, face_left, 1);
    for(int i = 1; i < receiver_size - 1; i ++)
            grid[x + i][y + receiver_size - 1]->set_tool_type(receiver, face_right, 1);
    for(int i = 1; i < receiver_size - 1; i ++)
        for(int j = 1; j < receiver_size - 1; j ++)
            grid[x + i][y + j]->set_tool_type(receiver, face_up, 2);
}

bool Map::check_legal(int i, int j)
{
    return i >= 0 && i < rows && j >= 0 && j < cols;
}

void Map::refresh_frozen_time()
{
    for(int i = 0; i < rows; i ++)
        for(int j = 0; j < cols; j ++)
            grid[i][j]->set_max_frozen_time();
}

void Map::save_all(QTextStream &out)
{
    out << rows << ' ' << cols << '\n';
    for(int i = 0; i < rows; i ++)
        for(int j = 0; j < cols; j ++)
            grid[i][j]->save_all(out);
    out << '\n';
}

void Map::load_all(QTextStream &in)
{
    erase();
    in >> rows >> cols;
    int x = map_x, y = map_y;
    grid = new Grid **[rows];
    for(int i = 0; i < rows; i ++)
        grid[i] = new Grid*[cols];
    for(int i = 0; i < rows; i ++){
        for(int j = 0; j < cols; j ++){
            grid[i][j] = new Grid;
            grid[i][j]->set_row_col(i, j);
            grid[i][j]->setRect(0, 0, grid_width, grid_height);
            grid[i][j]->setPos(x, y);
            grid[i][j]->set_timer(timer);
            grid[i][j]->set_timer_convey(timer_convey);
            grid[i][j]->setZValue(3.0);
            game->scene->addItem(grid[i][j]);
            x += grid_width;
        }
        x = 0;
        y += grid_height;
    }
    for(int i = 0; i < rows; i ++)
        for(int j = 0; j < cols; j ++)
            grid[i][j]->load_all(in);
    game->scene->setSceneRect(0, 0, cols * grid_width, map_y + rows * grid_height);
}

void Map::erase()
{
    for(int i = 0; i < rows; i ++)
        for(int j = 0; j < cols; j ++)
            grid[i][j]->erase();
    for(int i = 0; i < rows; i ++)
        delete grid[i];
    grid = 0;
}
