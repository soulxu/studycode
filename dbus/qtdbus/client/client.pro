TARGET = client
CONFIG += debug
QT += dbus

SOURCES += CarInterface.cpp ../CustomType.cpp main.cpp \
    Test.cpp
HEADERS += CarInterface.h ../CustomType.h \
    Test.h
