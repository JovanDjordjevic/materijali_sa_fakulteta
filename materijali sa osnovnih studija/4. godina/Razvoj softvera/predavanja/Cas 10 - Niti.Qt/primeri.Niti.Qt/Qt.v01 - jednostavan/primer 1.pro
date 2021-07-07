TARGET = ThreadExample
QT -= gui
CONFIG += console
CONFIG -= app_bundle
TEMPLATE = app

SOURCES += \
    main.cpp \
    MyThread.cpp

HEADERS += MyThread.h
