#-------------------------------------------------
#
# Project created by QtCreator 2014-03-27T10:50:38
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Taquin
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++11 \
    -pedantic-errors

SOURCES += main.cpp\
        mwtaquin.cpp \
    metier/moteur/Piece.cpp \
    metier/moteur/Taquin.cpp \
    metier/O_SDO/sujetDObservation.cpp \
    dialogdimensions.cpp \
    TexteObservateur.cpp \
    ImageObservateur.cpp \
    GraphiqueObservateur.cpp

HEADERS  += mwtaquin.h \
    metier/moteur/Position.h \
    metier/moteur/Taquin.h \
    metier/moteur/Piece.h \
    metier/moteur/TaquinException.h \
    metier/moteur/Direction.h \
    metier/O_SDO/observateur.h \
    metier/O_SDO/sujetDObservation.h \
    dialogdimensions.h \
    TexteObservateur.h \
    ImageObservateur.h \
    GraphiqueObservateur.h

FORMS    += mwtaquin.ui \
    dialogdimensions.ui

RESOURCES += \
    imgtaquin.qrc
