TEMPLATE = lib
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11
CONFIG += staticlib

DESTDIR = $$_PRO_FILE_PWD_/../../Lib

SOURCES += \
    CFBaseTidy.cpp \
    CFPhpTidy.cpp \
    exception.cpp \
    formatter.cpp \
    node.cpp \
    parser.cpp \
    scanner.cpp \
    settings.cpp \
    str.cpp

HEADERS += \
    CFBaseTidy.h \
    CFPhpTidy.h \
    common.h \
    debug.h \
    exception.h \
    formatter.h \
    node.h \
    parser.h \
    scanner.h \
    settings.h \
    str.h \
    tokens.h

