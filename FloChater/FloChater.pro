#-------------------------------------------------
#
# Project created by QtCreator 2019-09-22T18:26:02
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FloChater
TEMPLATE = app

SOURCES += main.cpp \
    MnWin/cgraphicsview.cpp \
    MnWin/mainwindow.cpp \
    Painter/Linker/clineitem.cpp \
    Painter/Linker/linkers.cpp \
    Painter/Linker/stepnbr.cpp \
    Painter/Scene/cgraphicsscene.cpp \
    Painter/Scene/scene.cpp \
    Painter/Symbols/symbols.cpp \
    Painter/Symbols/symtxt.cpp

HEADERS  += \
    MnWin/cgraphicsview.h \
    MnWin/mainwindow.h \
    MnWin/ui_mainwindow.h \
    Painter/Linker/clineitem.h \
    Painter/Linker/linkers.h \
    Painter/Linker/stepnbr.h \
    Painter/Scene/cgraphicsscene.h \
    Painter/Scene/scene.h \
    Painter/Symbols/symbols.h \
    Painter/Symbols/symtxt.h \
    Painter/MacroForElements.h

FORMS    +=

OTHER_FILES +=
