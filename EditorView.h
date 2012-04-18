/*
 * Copyright (c) 2012 ascetic85 
 */
#ifndef EDITORVIEW_H
#define EDITORVIEW_H


#include <QtOpenGL/QGLWidget>
#include <QtOpenGL/QtOpenGL>
#include <GL/GLU.h>
#include <QMouseEvent>
#include <QResizeEvent>

class EditorView : public QGLWidget
{
    Q_OBJECT
public:
    enum Tool {
        Select, Scroll, Lasso, Measure,
        Pencil, Pen, Brush, Ellipse, Polygon, Rectangle, EdgeChain,
        RevoluteJoint, PulleyJoint, PrismaticJoint, LineJoint, GearJoint
    };

    explicit EditorView(QWidget *parent = 0);

    QPointF mapToWorld(QPoint pos) const;
    
signals:
    void mousePosChanged(QPointF);

public slots:
    void showGrid(bool);
    void setTool(Tool tool);
    void drawGrid();

protected:
    // GL
    void initializeGL();
    void paintGL();
    void updatePM();

    // Event
    void mouseMoveEvent(QMouseEvent* event);
    void resizeEvent(QResizeEvent* event);
    void mousePressEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);

    // Draw
    void drawCircle(GLfloat x, GLfloat y, GLfloat r);
    void closePoly();

private:
    Tool m_tool;
//    World *m_world;
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
