#-------------------------------------------------
#
# Project created by QtCreator 2010-11-01T21:35:22
#
#-------------------------------------------------

QT       += core gui

TARGET = quickreply
TEMPLATE = app
INCLUDEPATH = /usr/include/telepathy-1.0 /usr/include/qt4 /usr/include/qt4/QtCore /usr/include/qt4/QtDBus /usr/include/qt4/QtNetwork /usr/include/qt4/QtXml
DEFINES = QT_SHARED
LIBS = -ltelepathy-qt4

SOURCES += main.cpp\
        widget.cpp \
    TpListener.cpp \
    AccountListener.cpp \
    TipWidget.cpp \
    ConnectionListener.cpp

HEADERS  += widget.h \
    TpListener.h \
    AccountListener.h \
    TipWidget.h \
    ConnectionListener.h
