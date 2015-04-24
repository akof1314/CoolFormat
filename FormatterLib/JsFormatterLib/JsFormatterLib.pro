TEMPLATE = lib
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11
CONFIG += staticlib

DESTDIR = $$_PRO_FILE_PWD_/../../Lib
QMAKE_POST_LINK += $$sprintf($$QMAKE_MKDIR_CMD, $$shell_path($$quote($$_PRO_FILE_PWD_/../../Include))) $$escape_expand(\\n\\t)
QMAKE_POST_LINK += $$QMAKE_COPY $$shell_path($$quote($$_PRO_FILE_PWD_/CFJsTidy.h)) $$shell_path($$quote($$_PRO_FILE_PWD_/../../Include)) $$escape_expand(\\n\\t)

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

