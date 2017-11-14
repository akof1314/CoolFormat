TEMPLATE = lib
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11
CONFIG += staticlib

DEFINES += SUPPORT_UTF16_ENCODINGS SUPPORT_ASIAN_ENCODINGS SUPPORT_ACCESSIBILITY_CHECKS SUPPORT_LOCALIZATIONS=0 LIBTIDY_VERSION=\\\"5.4.0\\\" RELEASE_DATE=\\\"2017/03/01\\\"
DEFINES -= UNICODE
INCLUDEPATH += ../include
DESTDIR = $$_PRO_FILE_PWD_/../../../Lib
QMAKE_POST_LINK += $$sprintf($$QMAKE_MKDIR_CMD, $$shell_path($$quote($$_PRO_FILE_PWD_/../../../Include))) $$escape_expand(\\n\\t)
QMAKE_POST_LINK += $$QMAKE_COPY $$shell_path($$quote($$_PRO_FILE_PWD_/CFHtmlTidy.h)) $$shell_path($$quote($$_PRO_FILE_PWD_/../../../Include)) $$escape_expand(\\n\\t)

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
    mappedio.c \
    parser.c \
    pprint.c \
    streamio.c \
    tagask.c \
    tags.c \
    tidylib.c \
    tmbstr.c \
    utf8.c \
    charsets.c \
    gdoc.c \
    language.c \
    message.c \
    sprtf.c

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
    tidy.h \
    tidyenum.h \
    sprtf.h \
    language_en.h \
    language.h \
    gdoc.h \
    charsets.h

