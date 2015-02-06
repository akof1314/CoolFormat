TEMPLATE = lib
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11
CONFIG += staticlib

DESTDIR = $$_PRO_FILE_PWD_/../../Lib

SOURCES += \
    CFBaseTidy.cpp \
    CFSqlTidy.cpp \
    SQLFormatter2.cpp

HEADERS += \
    CFBaseTidy.h \
    CFSqlTidy.h \
    SQLFormatter2.h

