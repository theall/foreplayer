#-------------------------------------------------
#
# Project created by QtCreator 2016-08-25T15:03:11
#
#-------------------------------------------------

QT -= core

TARGET = plugin
TEMPLATE = lib
CONFIG += c++11

INCLUDEPATH += ../\
    ../../pluginutils \
    ../../../thirdparty/unrar/include

LIBS += -lunrar
LIBS += -LF:/opensource/foreplayer/dist/lib -lgme -lunzip

SOURCES += \
    main.cpp \
    gmewrap.cpp \
    rarparse.cpp \
    fileparse.cpp \
    abstractparse.cpp \
    zipparse.cpp \
    ../../pluginutils/pluginutils.cpp

HEADERS += \  
    gmewrap.h \
    rarparse.h \
    fileparse.h \
    abstractparse.h \
    zipparse.h \
    ../../pluginutils/pluginutils.h

win32 {
    DLLDESTDIR = Z:/build/foreplayer/debug/debug/plugins/backend/gme
}
unix {
    target.path = /usr/lib
    INSTALLS += target
}