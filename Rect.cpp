/* 
 * File:   Rect.cpp
 * Author: mark
 * 
 * Created on September 13, 2009, 5:49 PM
 */

#include "Rect.h"
#include "Point.h"
Rect::Rect(): QRectF() {}
Rect::Rect(const QPointF& topLeft, const QSizeF& size): QRectF(topLeft, size) {}
Rect::Rect(const QPointF& topLeft, const QPointF& bottomRight): QRectF(topLeft, bottomRight) {}
Rect::Rect(qreal x, qreal y, qreal width, qreal height): QRectF(x, y, width, height) {}
Rect::Rect(const QRectF& rect): QRectF(rect) {}
Rect::Rect(const QRect& rect): QRectF(rect) {}
Rect::Rect(const b2AABB& aabb): QRectF((Point) aabb.lowerBound, (Point) aabb.upperBound) {}

Rect::operator b2AABB() const {
    b2AABB aabb;
    aabb.lowerBound = (Point) topLeft();
    aabb.upperBound = (Point) bottomRight();
    return aabb;
}