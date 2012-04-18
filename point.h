/*
 * Copyright (c) 2012 ascetic85
 */
#ifndef POINT_H
#define POINT_H

#include <QPointF>
#include <QMetaType>
#include <Box2D/Common/b2Math.h>

class Point : public QPointF
{
public:
    Point();
    Point(qreal x, qreal y);
    Point(const QPoint &p);
    Point(const QPointF &p);
    Point(const b2Vec2 &p);
    qreal lengthSquared() const;
    operator b2Vec2() const;
};

Q_DECLARE_METATYPE(Point)

#endif // POINT_H
