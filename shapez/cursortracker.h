#ifndef CURSORTRACKER_H
#define CURSORTRACKER_H

#include <QObject>
#include "tool.h"

class CursorTracker: public QObject
{
    Q_OBJECT
private:
    Tool *tool;
public:
    CursorTracker();
public slots:
    void track_curse();
};

#endif // CURSORTRACKER_H
