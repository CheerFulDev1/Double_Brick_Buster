#-------------------------------------------------
#
# Project created by QtCreator 2016-02-01T14:44:38
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Double_Brick_Buster
TEMPLATE = app


SOURCES += main.cpp\
        introwindow.cpp \
    level_1.cpp \
    paddle.cpp \
    ball.cpp \
    brick.cpp

HEADERS  += introwindow.h \
    level_1.h \
    paddle.h \
    ball.h \
    brick.h

FORMS    += introwindow.ui \
    level_1.ui
