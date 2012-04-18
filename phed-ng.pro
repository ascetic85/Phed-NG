#-------------------------------------------------
#
# Project created by QtCreator 2012-04-17T15:18:51
#
#-------------------------------------------------

QT       += core gui opengl

TARGET = phed-ng
TEMPLATE = app

INCLUDEPATH += Box2d

include(Box2d/box2d.pri)

SOURCES += main.cpp \
    EditorWindow.cpp \
    EditorView.cpp \
    point.cpp

HEADERS  += \
    EditorWindow.h \
    EditorView.h \
    point.h

RESOURCES += \
    icons.qrc
