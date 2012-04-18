/*
 * 
 * File:   EditorView.h
 * Author: mark
 * 
 * Created on August 19, 2009, 7:10 PM
 *
 *
 * Copyright (c) 2012 ascetic85 
 */

#ifndef EDITORVIEW_H
#define EDITORVIEW_H


#include <QtOpenGL/QGLWidget>
#include <QtOpenGL/QtOpenGL>
#include <GL/GLU.h>
#include <QMouseEvent>
#include <QResizeEvent>

#include "World.h"

class EditorView : public QGLWidget
{
    Q_OBJECT
public:
    enum Tool {
        Select, Scroll, Lasso, Measure,
        Pencil, Pen, Brush, Ellipse, Polygon, Rectangle, EdgeChain,
        RevoluteJoint, PulleyJoint, PrismaticJoint, LineJoint, GearJoint
    };

    explicit EditorView(World *world, QWidget *parent = 0);

    QPointF mapToWorld(QPoint pos) const;
    
signals:
    void mousePosChanged(QPointF);

public slots:
    void showGrid(bool);
    void setTool(Tool tool);


protected:
    // GL
    void initializeGL();
    void paintGL();
    void updatePM();

    // Event
    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent* event);
    void keyPressEvent(QKeyEvent* event);
    void resizeEvent(QResizeEvent* event);

    // Draw
    void drawCircle(GLfloat x, GLfloat y, GLfloat r);
    void closePoly();
    void drawGrid();

private:
    Tool m_tool;
    World *m_world;
    QPointF m_lastMousePos;
    QPointF m_mousePos;
    QPointF m_viewPos;
    QCursor m_lastCursor;
    QTimer m_redrawTimer;
    QPolygonF m_tmpPoly;
    QColor m_tmpColor;
    bool m_showGrid;
    bool m_readyClosePoly;
    int m_drawFPS;
    qreal m_pixelsPerMeter;
    qreal m_closePolyDist;
};

#endif // EDITORVIEW_H
