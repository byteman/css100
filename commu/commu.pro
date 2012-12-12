#-------------------------------------------------
#
# Project created by QtCreator 2012-09-19T19:46:53
#
#-------------------------------------------------

QT       -= core gui

TARGET = commu
TEMPLATE = lib

DEFINES += COMMU_LIBRARY

SOURCES += \
    src/udpdtu.cpp \
    src/termcommu.cpp \
    src/dtubase.cpp \
    src/commu.cpp

HEADERS += \
    include/udpdtu.h \
    include/termcommu.h \
    include/dtubase.h \
    include/commu.h

INCLUDEPATH+=../Extlib/include/yate
INCLUDEPATH+=../Common/bycore/include
INCLUDEPATH+=./include
LIBS+=-L../Extlib/lib/x86
LIBS+=-lyate -lPocoNet

DESTDIR =../Target/lib
