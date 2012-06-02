#-------------------------------------------------
#
# Project created by QtCreator 2010-10-31T19:59:16
#
#-------------------------------------------------

QT       += core gui

TARGET = tclient
TEMPLATE = app
INCLUDEPATH = /usr/include/telepathy-1.0 /usr/include/qt4 /usr/include/qt4/QtCore /usr/include/qt4/QtDBus /usr/include/qt4/QtNetwork /usr/include/qt4/QtXml
DEFINES = QT_SHARED
LIBS = -ltelepathy-qt4
SOURCES += main.cpp\
        widget.cpp

HEADERS  += widget.h
