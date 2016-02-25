QT += core
QT -= gui

CONFIG += c++11

TARGET = harfbuzz-ng
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

include ($$PWD/harfbuzz-ng-external/harfbuzz-ng-external.pri)
include ($$PWD/freetype/freetype_lib.pri)

INCLUDEPATH += D:/Qt/5.5.1/qtbase/src/3rdparty/harfbuzz-ng/include/harfbuzz
LIBS += D:/Qt/5.5.1/qtbase/lib/libqtharfbuzzng.a

SOURCES += main.cpp
