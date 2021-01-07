VPATH += ../shared
INCLUDEPATH += ../shared
LIBS += -lGL -lGLU
HEADERS       = DisplayWidget.h \
                Model.h
SOURCES       = DisplayWidget.cpp \
                Model.cpp \
                main.cpp
QT           += opengl

