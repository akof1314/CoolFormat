TEMPLATE = lib
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11
CONFIG += staticlib

DESTDIR = $$_PRO_FILE_PWD_/../../Lib

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
    config.h \
    features.h \
    forwards.h \
    json.h \
    json_batchallocator.h \
    json_tool.h \
    reader.h \
    value.h \
    writer.h

