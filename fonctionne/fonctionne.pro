#-------------------------------------------------
#
# Project created by QtCreator 2017-03-01T17:32:38
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PeyretWilhelm
TEMPLATE = app


SOURCES += main.cpp\
    Modèle/Porte.cpp \
    Modèle/Vanne.cpp \
    Modèle/Signal.cpp \
    Vue/MainWindow.cpp \
    Modèle/Ecluse.cpp \
    Modèle/Alarmable.cpp

HEADERS  += \
    Modèle/Porte.h \
    Modèle/Vanne.h \
    Modèle/Signal.h \
    Vue/MainWindow.h \
    Modèle/Ecluse.h \
    Modèle/Alarmable.h

FORMS    += \
    MainWindow.ui
