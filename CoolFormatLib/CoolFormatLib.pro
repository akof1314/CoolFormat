TEMPLATE = lib
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11
CONFIG += shared

DEFINES += COOLFORMATLIB_EXPORTS
INCLUDEPATH += ../Include
LIBS += -L$$_PRO_FILE_PWD_/../Lib -lAStyleLib -lCssTidyLib -lJsFormatterLib -lJsonCppLib -lPhpFormatterLib -lSqlFormatterLib -ltidy
DESTDIR = $$_PRO_FILE_PWD_/../Bin

win32:QMAKE_LFLAGS += -shared
SOURCES += \
    CoolFormatLib.cpp \
    dllmain.cpp \
    FormatterHelp.cpp \
    GlobalTidy.cpp \
    stdafx.cpp

HEADERS += \
    CFBaseTidy.h \
    CoolFormatLib.h \
    FormatterHelp.h \
    GlobalTidy.h \
    stdafx.h \
    StrUseful.h \
    SynLanguage.h \
    targetver.h

