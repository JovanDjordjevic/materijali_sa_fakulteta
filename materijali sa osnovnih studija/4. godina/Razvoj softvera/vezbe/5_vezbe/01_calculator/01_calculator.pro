# ovaj .pro fajl je fajl sa metapodacima

#ovde se dodaju moduli (?) qt-a, po defaultu imamo Core i Gui
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

#verzija c++ koju koristimo, podrazumevano ovde ce pisati c++11
CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

#svi fajlovi sa implementacijom. Primetimo da sa leve strane prozora, kao da su se napravili Sources i Headers fajlovi ali
#u file exploreru, oni ne postoje. Ako hocemo da ih napravimo sami, potrebno je da nakon sto rasporedimo fajlove, ovde u putanje, pre imena fajla
#dodamo lokaciju, npr: src/main.cpp , src/MainWindow.cpp, slicno za ostalo
SOURCES += \
    main.cpp \
    MainWindow.cpp \
    Fraction.cpp

HEADERS += \
    MainWindow.h \
    Fraction.hpp

FORMS += \
    MainWindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
