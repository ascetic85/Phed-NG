#include "EditorView.h"

EditorView::EditorView(QWidget *parent) :
    QGLWidget(parent)
{
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
//    m_viewPos = QPointF(-width() / 2 / m_pixelsPerMeter,
//            -height() / 2 / m_pixelsPerMeter); // width and height aren't fully initialized in constructor
//    updatePM();
}

void EditorView::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);

//    foreach(Body *obj, m_world->bodies()) { // TODO: query the world for visible objects first!
//        obj->paintGL();
//    }

//    if(m_tmpPoly.size() >= 1) {
//        glLineWidth(1.5);
//        glColor3ub(m_tmpColor.red(), m_tmpColor.green(), m_tmpColor.blue());
//        if(m_tmpPoly.size() >= 2) {
//            glBegin(GL_LINE_STRIP);
//            foreach(QPointF vert, m_tmpPoly) {
//                glVertex2f(vert.x(), vert.y());
//            }
//            glEnd();

//        }
//        glEnable(GL_LINE_STIPPLE);
//        glBegin(GL_LINES);
//        {
//            glVertex2f(m_tmpPoly.last().x(), m_tmpPoly.last().y());
//            glVertex2f(m_mousePos.x(), m_mousePos.y());
//        }
//        glEnd();
//        glDisable(GL_LINE_STIPPLE);

//        if(m_readyClosePoly) {
//            glColor3ub(255, 255, 255);
//            drawCircle(m_tmpPoly.first().x(), m_tmpPoly.first().y(), m_closePolyDist / m_pixelsPerMeter);
//        }
//    }

//    if(m_world->mouseJoint() != NULL) {
//        glLineWidth(1.5);
//        glColor3ub(64,128,255);
//        glBegin(GL_LINES);
//        {
//            glVertex2f(m_world->mouseJoint()->GetAnchorB().x, m_world->mouseJoint()->GetAnchorB().y);
//            glVertex2f(m_mousePos.x(), m_mousePos.y());
//        }
//        glEnd();
//    }

//    if(m_showGrid) drawGrid();
}

void EditorView::showGrid(bool)
{
}
