######################################################################
# Automatically generated by qmake (2.01a) ven 22. ago 11:57:33 2008
######################################################################

TEMPLATE = app
TARGET = xx
DEPENDPATH += .
INCLUDEPATH += .


MOC_DIR = build/.moc
RCC_DIR = build/.rcc
OBJECTS_DIR = build/.obj

CONFIG +=  qt release warn_on console
DESTDIR	+= ./

QT += xml
QT += network
QT += svg 
contains(QT_CONFIG, opengl):QT += opengl




# Input
HEADERS += BookMarkModel.h BookTree.h XML_Editor.h TranslateModel.h
SOURCES += BookMarkModel.cpp BookTree.cpp main.cpp XML_Editor.cpp TranslateModel.cpp
