#-------------------------------------------------
#
# Project created by QtCreator 2012-09-19T19:46:53
#
#-------------------------------------------------

QT       -= core gui

TARGET = commu
TEMPLATE = lib

DEFINES += COMMU_LIBRARY

SOURCES += commu.cpp

HEADERS += commu.h

INCLUDEPATH+=../Extlib/include/yate
LIBS+=-L../Extlib/lib/x86
LIBS+=-lyate

DESTDIR =../Target/lib
