TARGET = AStyleLib
TEMPLATE = lib
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11
CONFIG += staticlib

DEFINES += ASTYLE_LIB
DESTDIR = $$_PRO_FILE_PWD_/../../../Lib

SOURCES += \
    ASBeautifier.cpp \
    ASEnhancer.cpp \
    ASFormatter.cpp \
    astyle_main.cpp \
    CFBaseTidy.cpp \
    CFCppTidy.cpp \
    ASResource.cpp

HEADERS += \
    astyle.h \
    astyle_main.h \
    CFBaseTidy.h \
    CFCppTidy.h

