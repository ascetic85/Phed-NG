#ifndef EDITORVIEW_H
#define EDITORVIEW_H

#include <QGLWidget>

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
    
signals:
    
public slots:
    void showGrid(bool);

protected:
    void initializeGL();
    void paintGL();
};

#endif // EDITORVIEW_H
