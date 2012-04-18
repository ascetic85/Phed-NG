/*
 *
 * File:   point.h
 * Author: mark
 *
 * Created on August 19, 2009, 7:10 PM
 *
 *
 * Copyright (c) 2012 ascetic85
 */
#include "point.h"

Point::Point() : QPointF() {}
Point::Point(qreal x, qreal y) : QPointF(x, y) {}
Point::Point(const QPoint& p) : QPointF(p) {}
Point::Point(const QPointF& p) : QPointF(p) {}
Point::Point(const b2Vec2& p) : QPointF(p.x, p.y) {}

Point::operator b2Vec2() const {
    return b2Vec2(x(), y());
}

qreal Point::lengthSquared() const {
    return x()*x() + y()*y();
}
