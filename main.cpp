/*
 * Copyright (c) 2012 ascetic85 
 */
#include <QtGui/QApplication>
#include <QDateTime>

#include "EditorWindow.h"
#include "Rect.h"
#include "Circle.h"
#include "Polygon.h"
#include "point.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setOrganizationName("mnbGames");
    QCoreApplication::setOrganizationDomain("http://code.google.com/p/phed/");
    QCoreApplication::setApplicationName("Phed-NG");

    qsrand(QDateTime::currentDateTime().toTime_t());

    QApplication a(argc, argv);

    qRegisterMetaType<Rect>("Rect");
    qRegisterMetaType<Circle>("Circle");
    qRegisterMetaType<BPolygon>("BPolygon");
    qRegisterMetaType<Point>("Point");
    qRegisterMetaType<PolygonList>("PolygonList");
    qRegisterMetaTypeStreamOperators<PolygonList>("PolygonList");


    EditorWindow w;
    w.show();
    
    return a.exec();
}
