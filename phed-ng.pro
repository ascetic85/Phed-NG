#-------------------------------------------------
#
# Project created by QtCreator 2012-04-17T15:18:51
#
#-------------------------------------------------

QT       += core gui opengl

TARGET = phed-ng
TEMPLATE = app

INCLUDEPATH += Box2d
LIBS += -lQtSolutions_PropertyBrowser-headd

include(Box2d/box2d.pri)
include(qtpropertybrowser/qtpropertybrowser.pri)

SOURCES += main.cpp \
    EditorWindow.cpp \
    EditorView.cpp \
    point.cpp \
    Rect.cpp \
    Color.cpp \
    Circle.cpp \
    Polygon.cpp \
    Object.cpp \
    PropertyBrowser.cpp \
    Body.cpp \
    Shape.cpp \
    Fixture.cpp \
    ContactListener.cpp \
    World.cpp

HEADERS  += \
    EditorWindow.h \
    EditorView.h \
    point.h \
    Rect.h \
    Color.h \
    Circle.h \
    Polygon.h \
    Object.h \
    PropertyBrowser.h \
    Body.h \
    ScopedPointer.h \
    Shape.h \
    Fixture.h \
    ContactListener.h \
    World.h

RESOURCES += \
    icons.qrc
