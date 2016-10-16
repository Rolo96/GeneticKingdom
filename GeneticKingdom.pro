#-------------------------------------------------
#
# Project created by QtCreator 2016-10-14T23:26:57
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GeneticKingdom
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    tower.cpp \
    juego.cpp \
    enemigo.cpp \
    Array.cpp \
    List.cpp \
    Node.cpp

HEADERS  += mainwindow.h \
    tower.h \
    juego.h \
    enemigo.h \
    Array.h \
    List.h \
    Node.h

FORMS    += mainwindow.ui

RESOURCES += \
    resources.qrc
