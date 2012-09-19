#-------------------------------------------------
#
# Project created by QtCreator 2012-09-19T19:09:23
#
#-------------------------------------------------

QT       -= gui core

TARGET = css100
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

INCLUDEPATH+=../Extlib/include/yate
LIBS+=-L../Extlib/lib/x86
LIBS+=-lyate
SOURCES += main.cpp


