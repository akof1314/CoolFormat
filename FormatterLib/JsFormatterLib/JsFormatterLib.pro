TEMPLATE = lib
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11
CONFIG += staticlib

DESTDIR = $$_PRO_FILE_PWD_/../../Lib

SOURCES += \
    CFBaseTidy.cpp \
    CFJsTidy.cpp \
    jsformatString.cpp \
    jsmin.cpp \
    jsminCharArray.cpp \
    jsparser.cpp \
    realjsformatter.cpp

HEADERS += \
    CFBaseTidy.h \
    CFJsTidy.h \
    jsformatString.h \
    jsmin.h \
    jsminCharArray.h \
    jsparser.h \
    realjsformatter.h

