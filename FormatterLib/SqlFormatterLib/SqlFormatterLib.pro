TEMPLATE = lib
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11
CONFIG += staticlib

DESTDIR = $$_PRO_FILE_PWD_/../../Lib
QMAKE_POST_LINK += $$sprintf($$QMAKE_MKDIR_CMD, $$shell_path($$quote($$_PRO_FILE_PWD_/../../Include))) $$escape_expand(\\n\\t)
QMAKE_POST_LINK += $$QMAKE_COPY $$shell_path($$quote($$_PRO_FILE_PWD_/CFSqlTidy.h)) $$shell_path($$quote($$_PRO_FILE_PWD_/../../Include)) $$escape_expand(\\n\\t)

SOURCES += \
    CFBaseTidy.cpp \
    CFSqlTidy.cpp \
    SQLFormatter2.cpp

HEADERS += \
    CFBaseTidy.h \
    CFSqlTidy.h \
    SQLFormatter2.h

