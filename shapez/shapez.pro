#-------------------------------------------------
#
# Project created by QtCreator 2023-12-20T15:41:14
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = shapez
TEMPLATE = app


SOURCES += main.cpp \
    game.cpp \
    map.cpp \
    grid.cpp \
    toolbar.cpp \
    tool.cpp \
    toolgrid.cpp \
    mineral.cpp \
    mineralcore.cpp \
    frozen_time_table.cpp \
    storage.cpp \
    money_table.cpp \
    mission.cpp \
    mission_table.cpp \
    upgrader.cpp \
    moneytext.cpp \
    shopwidget.cpp \
    cuttable.cpp \
    savetext.cpp \
    loadtext.cpp \
    mineralwidget.cpp \
    mineral_table.cpp \
    cursortracker.cpp \
    spin_table.cpp \
    pixmap_table.cpp

HEADERS  += \
    game.h \
    map.h \
    grid.h \
    toolbar.h \
    tool.h \
    toolgrid.h \
    mineral.h \
    mineralcore.h \
    storage.h \
    mission.h \
    mission_table.h \
    upgrader.h \
    moneytext.h \
    shopwidget.h \
    savetext.h \
    loadtext.h \
    mineralwidget.h \
    mineral_table.h \
    cursortracker.h \
    spin_table.h \
    pixmap_table.h

FORMS    +=

RESOURCES += \
    res.qrc
