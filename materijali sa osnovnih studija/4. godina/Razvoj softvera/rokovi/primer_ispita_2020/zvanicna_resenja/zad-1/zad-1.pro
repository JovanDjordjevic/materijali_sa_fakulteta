TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

TARGET = zad-1
INCLUDEPATH += . \
    catch/single_include

# Input
HEADERS += encoder.hpp 

SOURCES += test.cpp
