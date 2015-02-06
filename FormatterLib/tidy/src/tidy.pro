TEMPLATE = lib
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11
CONFIG += staticlib

DEFINES += SUPPORT_UTF16_ENCODINGS SUPPORT_ASIAN_ENCODINGS SUPPORT_ACCESSIBILITY_CHECKS
INCLUDEPATH += ../include
DESTDIR = $$_PRO_FILE_PWD_/../../../Lib

SOURCES += \
    CFBaseTidy.cpp \
    CFHtmlTidy.cpp \
    access.c \
    alloc.c \
    attrask.c \
    attrdict.c \
    attrget.c \
    attrs.c \
    buffio.c \
    clean.c \
    config.c \
    entities.c \
    fileio.c \
    istack.c \
    lexer.c \
    localize.c \
    mappedio.c \
    parser.c \
    pprint.c \
    streamio.c \
    tagask.c \
    tags.c \
    tidylib.c \
    tmbstr.c \
    utf8.c \
    win32tc.c

HEADERS += \
    access.h \
    attrdict.h \
    attrs.h \
    CFBaseTidy.h \
    CFHtmlTidy.h \
    clean.h \
    config.h \
    entities.h \
    fileio.h \
    forward.h \
    lexer.h \
    mappedio.h \
    message.h \
    parser.h \
    pprint.h \
    streamio.h \
    tags.h \
    tidy-int.h \
    tmbstr.h \
    utf8.h \
    version.h \
    win32tc.h \
    buffio.h \
    platform.h \
    tidy.h \
    tidyenum.h

