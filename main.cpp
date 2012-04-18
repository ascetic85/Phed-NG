/*
 * Copyright (c) 2012 ascetic85 
 */
#include <QtGui/QApplication>
#include <QDateTime>
#include "EditorWindow.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setOrganizationName("mnbGames");
    QCoreApplication::setOrganizationDomain("http://code.google.com/p/phed/");
    QCoreApplication::setApplicationName("Phed-NG");

    qsrand(QDateTime::currentDateTime().toTime_t());

    QApplication a(argc, argv);
    EditorWindow w;
    w.show();
    
    return a.exec();
}
