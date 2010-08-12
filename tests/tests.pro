QT       += core
QT       -= gui

CONFIG   += console
CONFIG   -= app_bundle

TARGET = TweetAuth_Tests
TEMPLATE = app
INCLUDEPATH = ../src
DEPENDPATH = ../lib

CONFIG(debug, release|debug) {
  LIBS += -L../lib -lOAvisd
} else {
  LIBS += -L../lib -lOAvis
}

SOURCES += main.cpp
