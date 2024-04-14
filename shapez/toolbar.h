#ifndef TOOLBAR_H
#define TOOLBAR_H

#include "toolgrid.h"

#define toolbar_x 704
#define toolbar_y 96

class ToolBar
{
private:
    ToolGrid *toolgrid[tool_type_num + 1];

public:
    ToolBar();
    void rotate_clockwise();
};

#endif // TOOLBAR_H
