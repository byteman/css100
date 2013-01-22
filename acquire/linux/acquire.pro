TEMPLATE = lib
CONFIG += console
CONFIG -= qt

SOURCES += \ 
    ../src/filter.cpp \
    ../src/dataacquire.cpp \
    ../src/acquire.cpp \
    ../src/adc.cpp \
    ../src/normalizeconfig.cpp \
    ../src/normalizer.cpp \
    ../../utils/byconfig/src/ByDBConfig.cpp \
    ../../utils/byconfig/src/ByConfigMgr.cpp \
    ../../utils/byconfig/src/ByConfig.cpp \
    ../../utils/byconfig/src/ByIniConfig.cpp \
    ../../utils/byconfig/src/CppSQLite3.cpp \
    ../src/virtualadc.cpp \
    ../src/netutils.cpp \
    ../src/acquiremgr.cpp \
    ../src/bythread.cpp

OUTPUT+= ../../target
UTILS_DIR+=../../utils
INCLUDEPATH += ../include
INCLUDEPATH += ../../common/include
INCLUDEPATH += $$UTILS_DIR/serialport/include
INCLUDEPATH += $$UTILS_DIR/byconfig/include
LIBS+=-lbySerialPort -lrt -lPocoFoundation -lsqlite3
LIBS+=-lPocoNet
OBJECTS_DIR += ./obj

linux-arm-g++ {
    message(g++ = linux-arm-g++ compile)
    LIBS += -L$$OUTPUT/lib/arm
    DESTDIR += $$OUTPUT/lib/arm
}

linux-g++ {
    message(g++ = linux-g++)
    LIBS += -L$$OUTPUT/lib/x86
    DESTDIR += $$OUTPUT/lib/x86
}
QMAKE_CXX += -g
HEADERS += \
    ../src/filter.h \
    ../src/dataacquire.h \
    ../include/acquire.h \
    ../src/adc.h \
    ../src/normalizeconfig.h \
    ../../common/include/css100.h \
    ../src/virtualadc.h \
    ../src/acquiremgr.h
