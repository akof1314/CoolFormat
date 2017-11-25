TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11

DEFINES += USE_LOCAL_CONFIG_FILE
INCLUDEPATH += ../Include
LIBS += -L$$_PRO_FILE_PWD_/../Lib -lAStyleLib -lCssTidyLib -lJsFormatterLib -lJsonCppLib -lPhpFormatterLib -lSqlFormatterLib -ltidy -lVerilogFormatterLib
DESTDIR = $$_PRO_FILE_PWD_/../Bin

SOURCES += CoolFormatExec.cpp \
    FormatterHelp.cpp \
    GlobalTidy.cpp \
    stdafx.cpp

HEADERS += \
    FormatterHelp.h \
    GlobalTidy.h \
    stdafx.h \
    targetver.h

