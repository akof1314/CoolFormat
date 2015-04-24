TEMPLATE = lib
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11
CONFIG += staticlib

DESTDIR = $$_PRO_FILE_PWD_/../../Lib
QMAKE_POST_LINK += $$sprintf($$QMAKE_MKDIR_CMD, $$shell_path($$quote($$_PRO_FILE_PWD_/../../Include))) $$escape_expand(\\n\\t)
QMAKE_POST_LINK += $$QMAKE_COPY $$shell_path($$quote($$_PRO_FILE_PWD_/CFJsonTidy.h)) $$shell_path($$quote($$_PRO_FILE_PWD_/../../Include)) $$escape_expand(\\n\\t)

SOURCES += \
    json_valueiterator.inl \
    CFBaseTidy.cpp \
    CFJsonTidy.cpp \
    json_reader.cpp \
    json_value.cpp \
    json_writer.cpp

HEADERS += \
    autolink.h \
    CFBaseTidy.h \
    CFJsonTidy.h \
    forwards.h \
    json.h \
    json_batchallocator.h \
    json_tool.h \
    reader.h \
    value.h \
    writer.h \
    json_config.h \
    json_features.h

