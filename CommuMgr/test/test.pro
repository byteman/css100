#-------------------------------------------------
#
# Project created by QtCreator 2012-09-21T20:30:16
#
#-------------------------------------------------

QT       -= core

QT       -= gui

TARGET = test
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

INCLUDEPATH+=../include
INCLUDEPATH+=../../Common/bycore/include
SOURCES += main.cpp \
    ../../Common/bycore/src/bythread.cpp
LIBS+=-L../../Target/lib
LIBS+=-L../Extlib/lib/x86
LIBS+=-lyate -lPocoNet -lglog -lcommu




