QT       += core
QT       -= gui

CONFIG   += console
CONFIG   -= app_bundle

TARGET = QLibOA_Tests
TEMPLATE = app
INCLUDEPATH = ../src
DEPENDPATH = ../lib

CONFIG(debug, release|debug) {
  LIBS += -L../lib -lQLibOAd
} else {
  LIBS += -L../lib -lQLibOA
}

SOURCES += main.cpp
