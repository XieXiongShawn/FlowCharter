#-------------------------------------------------
#
# Project created by QtCreator 2019-09-01T18:30:10
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FloChater
TEMPLATE = app

SOURCES += main.cpp\
    MnWin/cgraphicsview.cpp \
    MnWin/mainwindow.cpp \
    TxtProc/TxtOperation/txtreader.cpp \
    TxtProc/CodeBlocks/states.cpp \
    TxtProc/CodeBlocks/stateextractor.cpp \
    TxtProc/CodeExtractor/codeextractor.cpp \
    Painter/Linker/clineitem.cpp \
    Painter/Linker/stepnbr.cpp \
    Painter/Linker/linkers.cpp \
    Painter/Symbols/symtxt.cpp \
    Painter/Symbols/symbols.cpp \
    Painter/Scene/cgraphicsscene.cpp \
    Painter/Scene/scene.cpp \
    PaintingAlgorithm/middleware.cpp

HEADERS  += \
    MnWin/mainwindow.h \
    MnWin/ui_mainwindow.h \
    MnWin/cgraphicsview.h \
    TxtProc/TxtOperation/txtreader.h \
    TxtProc/CodeBlocks/stateextractor.h \
    TxtProc/CodeBlocks/states.h \
    TxtProc/CodeExtractor/codeextractor.h \
    Painter/Linker/stepnbr.h \
    Painter/Linker/clineitem.h \
    Painter/Linker/linkers.h \
    Painter/Symbols/symtxt.h \
    Painter/Symbols/symbols.h \
    Painter/Scene/cgraphicsscene.h \
    Painter/Scene/scene.h \
    Painter/MacroForElements.h \
    PaintingAlgorithm/middleware.h \
    PaintingAlgorithm/MacroForMiddleware.h

RESOURCES += \
    icon.qrc
