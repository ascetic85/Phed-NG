/*
 * 
 * File:   EditorView.cpp
 * Author: mark
 * 
 * Created on August 19, 2009, 7:10 PM
 *
 *
 * Copyright (c) 2012 ascetic85 
 */

#include "EditorView.h"
#include "point.h"
#include "Body.h"

EditorView::EditorView(World *world, QWidget *parent)
    : QGLWidget(QGLFormat(QGL::DoubleBuffer), parent)
    , m_world(world)
    , m_pixelsPerMeter(50)
    , m_showGrid(true)
    , m_drawFPS(60)
    , m_closePolyDist(7.5)
{
    setMouseTracking(true);
    m_redrawTimer.start(1000 / m_drawFPS);
    connect(&m_redrawTimer, SIGNAL(timeout()), this, SLOT(updateGL()));
    setFocus(); // accept keyboard events
    setFocusPolicy(Qt::ClickFocus);
}

QPointF EditorView::mapToWorld(QPoint pos) const
{
    return QPointF(pos.x() / m_pixelsPerMeter + m_viewPos.x(),
                   (height() - pos.y()) / m_pixelsPerMeter + m_viewPos.y());
}

void EditorView::initializeGL()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_COLOR_MATERIAL);
    glEnable(GL_BLEND);
    glEnable(GL_LINE_SMOOTH);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0, 0, 0, 0);
    glLineWidth(1.5);
    glLineStipple(1, 0x1111);
    m_viewPos = QPointF(-width() / 2 / m_pixelsPerMeter,
            -height() / 2 / m_pixelsPerMeter); // width and height aren't fully initialized in constructor
    updatePM();
}

void EditorView::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);

    foreach(Body *obj, m_world->bodies()) { // TODO: query the world for visible objects first!
        obj->paintGL();
    }

    if(m_tmpPoly.size() >= 1) {
        glLineWidth(1.5);
        glColor3ub(m_tmpColor.red(), m_tmpColor.green(), m_tmpColor.blue());
        if(m_tmpPoly.size() >= 2) {
            glBegin(GL_LINE_STRIP);
            foreach(QPointF vert, m_tmpPoly) {
                glVertex2f(vert.x(), vert.y());
            }
            glEnd();

        }
        glEnable(GL_LINE_STIPPLE);
        glBegin(GL_LINES);
        {
            glVertex2f(m_tmpPoly.last().x(), m_tmpPoly.last().y());
            glVertex2f(m_mousePos.x(), m_mousePos.y());
        }
        glEnd();
        glDisable(GL_LINE_STIPPLE);

        if(m_readyClosePoly) {
            glColor3ub(255, 255, 255);
            drawCircle(m_tmpPoly.first().x(), m_tmpPoly.first().y(), m_closePolyDist / m_pixelsPerMeter);
        }
    }

    if(m_world->mouseJoint() != NULL) {
        glLineWidth(1.5);
        glColor3ub(64,128,255);
        glBegin(GL_LINES);
        {
            glVertex2f(m_world->mouseJoint()->GetAnchorB().x, m_world->mouseJoint()->GetAnchorB().y);
            glVertex2f(m_mousePos.x(), m_mousePos.y());
        }
        glEnd();
    }

    if(m_showGrid) drawGrid();
}

void EditorView::updatePM()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(m_viewPos.x(), m_viewPos.x() + width() / m_pixelsPerMeter,
            m_viewPos.y(), m_viewPos.y() + height() / m_pixelsPerMeter);
    glMatrixMode(GL_MODELVIEW);
}

void EditorView::mouseMoveEvent(QMouseEvent *event)
{
    m_mousePos = mapToWorld(event->pos());
    emit mousePosChanged(m_mousePos);

    Point mouseDiff = m_mousePos - m_lastMousePos;
    if(m_tool == Select && event->buttons() & Qt::LeftButton) {
        if(m_world->mouseJoint() == NULL) {
            foreach(Object *obj, m_world->selectedObjects()) {
                if(obj->inherits("Body")) {
                    static_cast<Body*>(obj)->translate(mouseDiff);
                }
            }
        } else {
            m_world->updateMouseJoint(m_mousePos);
        }
    }
    if(event->buttons() & Qt::MidButton) {
        m_viewPos -= mouseDiff;
        updatePM();
    }
    if(m_tool == Polygon) {
        m_readyClosePoly = (m_tmpPoly.size() >= 3 && QLineF(m_mousePos, m_tmpPoly.first()).length() * m_pixelsPerMeter <= m_closePolyDist);
    }
    m_lastMousePos = mapToWorld(event->pos());
}

void EditorView::resizeEvent(QResizeEvent *event)
{
    QSize diff = size() - event->oldSize();
    m_viewPos.ry() -= diff.height() / m_pixelsPerMeter; // anchor view at top left when resizing
    glViewport(0, 0, width(), height());
    updatePM();
}

void EditorView::mousePressEvent(QMouseEvent *event)
{
    QPointF mousePos = mapToWorld(event->pos());
    m_lastMousePos = mousePos;
    switch(event->button()) {
        case Qt::LeftButton:
            switch(m_tool) {
                case Select:
                    m_world->setSelectedObjects(m_world->query(mousePos));
                    if(m_world->simulating() && !m_world->selectedObjects().isEmpty()) {
                        if(m_world->selectedObjects().first()->inherits("Body")) {
                            m_world->addMouseJoint((Body*)m_world->selectedObjects().first(), mousePos);
                        }
                    }
                    break;

                case Polygon:
                    if(m_readyClosePoly) {
                        closePoly();
                    } else {
                        if(m_tmpPoly.isEmpty()) {
                            m_tmpColor.setHsv(qrand()%360, qrand()%192+64, qrand()%64+192);
                            m_tmpPoly.append(mousePos);
                        } else if(mousePos != m_tmpPoly.last()) {
                            m_tmpPoly.append(mousePos);
                        }
                    }
                    break;
                default:
                    break;
            }
            break;
        case Qt::MidButton:
            m_lastCursor = cursor();
            setCursor(Qt::ClosedHandCursor);
            break;
        case Qt::RightButton:
            if(m_tool == Polygon && !m_tmpPoly.isEmpty()) {
                m_tmpPoly.pop_back();
            }
            break;
        default:
            break;
    }
}

void EditorView::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton && m_tool == Polygon && m_tmpPoly.size() >= 3) {
        closePoly();
    }
}

void EditorView::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton && m_tool == Select) {
        m_world->destroyMouseJoint();
    } else if(event->button() == Qt::MidButton) {
        setCursor(m_lastCursor);
    }
}

void EditorView::wheelEvent(QWheelEvent *event)
{
    double scaleFactor = event->delta() / 100.;
    QSizeF oldSize(width() / m_pixelsPerMeter, height() / m_pixelsPerMeter);

    if(event->delta() > 0) m_pixelsPerMeter *= scaleFactor;
    else m_pixelsPerMeter /= -scaleFactor;

    if(m_pixelsPerMeter > 500) m_pixelsPerMeter = 500;
    else if(m_pixelsPerMeter < 10) m_pixelsPerMeter = 10;

    QSizeF newSize(width() / m_pixelsPerMeter, height() / m_pixelsPerMeter);
    QSizeF deltaSize = newSize - oldSize;
    QPointF mousePos(event->x() / (qreal) width(), event->y() / (qreal) height()); // calc mouse pos as percent

    m_viewPos.rx() -= deltaSize.width() * mousePos.x(); // anchor at mouse pos
    m_viewPos.ry() -= deltaSize.height() * (1 - mousePos.y());

    updatePM();
}

void EditorView::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Delete) {
        foreach(Object *qobj, m_world->selectedObjects()) {
            if(qobj->inherits("Body")) {
                m_world->removeObject(static_cast<Body*>(qobj));
            }
        }
    }
}

void EditorView::drawCircle(GLfloat x, GLfloat y, GLfloat r)
{
    static const double inc = M_PI / 12;
    static const double max = 2 * M_PI;
    glBegin(GL_LINE_LOOP);
    for(double d = 0; d < max; d += inc) {
        glVertex2f(cos(d) * r + x, sin(d) * r + y);
    }
    glEnd();
}

void EditorView::closePoly()
{
    Body *body = new Body(m_world);
    body->addPolygon(m_tmpPoly);
    body->setColor(m_tmpColor);
    m_world->addBody(body);
    m_tmpPoly.clear();

    QSet<Body*> qobjs;
    qobjs.insert(body);
    m_world->setSelectedObjects(qobjs);
}

void EditorView::showGrid(bool flag)
{
    m_showGrid = flag;
}

void EditorView::setTool(EditorView::Tool tool)
{
    m_tool = tool;
    switch(tool) {
        case Polygon:
            setCursor(Qt::CrossCursor);
            break;
        default:
            setCursor(Qt::ArrowCursor);
            break;
    }
}

void EditorView::drawGrid()
{
    glDisable(GL_LINE_SMOOTH);
    glLineWidth(1);
    glColor4ub(128, 128, 128, 128);
    float xMin, xMax, yMin, yMax;

    // vertical lines
    glBegin(GL_LINES);
    xMin = ceil(m_viewPos.x());
    xMax = floor(m_viewPos.x() + width() / m_pixelsPerMeter);
    yMin = m_viewPos.y();
    yMax = m_viewPos.y() + height() / m_pixelsPerMeter;
    for(int i = xMin; i <= xMax; ++i) {
        glVertex2f(i, yMin);
        glVertex2f(i, yMax);
    }
    glEnd();

    // horizontal lines
    glBegin(GL_LINES);
    xMin = m_viewPos.x();
    xMax = m_viewPos.x() + width() / m_pixelsPerMeter;
    yMin = ceil(m_viewPos.y());
    yMax = floor(m_viewPos.y() + height() / m_pixelsPerMeter);
    for(int i = yMin; i <= yMax; ++i) {
        glVertex2f(xMin, i);
        glVertex2f(xMax, i);
    }
    glEnd();
    glEnable(GL_LINE_SMOOTH);
}
