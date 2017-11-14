TEMPLATE = lib
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11
CONFIG += staticlib

DEFINES += ASTYLE_LIB
DESTDIR = $$_PRO_FILE_PWD_/../../Lib
QMAKE_POST_LINK += $$sprintf($$QMAKE_MKDIR_CMD, $$shell_path($$quote($$_PRO_FILE_PWD_/../../Include))) $$escape_expand(\\n\\t)
QMAKE_POST_LINK += $$QMAKE_COPY $$shell_path($$quote($$_PRO_FILE_PWD_/CFVerilogTidy.h)) $$shell_path($$quote($$_PRO_FILE_PWD_/../../Include)) $$escape_expand(\\n\\t)

SOURCES += \
    CFBaseTidy.cpp \
    CFVerilogTidy.cpp \
    ASBeautifier.cpp \
    ASFormatter.cpp \
    ASResource.cpp \
    ASStreamIterator.cpp \
    astyle_main.cpp

HEADERS += \
    CFBaseTidy.h \
    CFVerilogTidy.h \
    astyle.h \
    astyle_main.h \
    compiler_defines.h

