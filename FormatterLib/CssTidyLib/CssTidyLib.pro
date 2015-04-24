TEMPLATE = lib
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11
CONFIG += staticlib

DESTDIR = $$_PRO_FILE_PWD_/../../Lib
QMAKE_POST_LINK += $$sprintf($$QMAKE_MKDIR_CMD, $$shell_path($$quote($$_PRO_FILE_PWD_/../../Include))) $$escape_expand(\\n\\t)
QMAKE_POST_LINK += $$QMAKE_COPY $$shell_path($$quote($$_PRO_FILE_PWD_/CFCssTidy.h)) $$shell_path($$quote($$_PRO_FILE_PWD_/../../Include)) $$escape_expand(\\n\\t)

SOURCES += \
    CFBaseTidy.cpp \
    background.cpp \
    CFCssTidy.cpp \
    conversions.cpp \
    cssopt.cpp \
    csspp_globals.cpp \
    csstidy.cpp \
    important.cpp \
    misc.cpp \
    parse_css.cpp \
    prepare.cpp \
    print_css.cpp \
    trim.cpp

HEADERS += \
    CFBaseTidy.h \
    background.hpp \
    CFCssTidy.h \
    conversions.hpp \
    cssopt.hpp \
    csspp_globals.hpp \
    csspp_private.h \
    csstidy.hpp \
    datastruct.hpp \
    important.hpp \
    misc.hpp \
    parse_css.hpp \
    prepare.hpp \
    trim.hpp \
    umap.hpp

