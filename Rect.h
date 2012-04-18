/* 
 * File:   Rect.h
 * Author: mark
 *
 * Created on September 13, 2009, 5:49 PM
 */

#ifndef _RECT_H
#define	_RECT_H

#include <QtCore/QRectF>
#include <QtCore/QMetaType>
#include <Box2D/Box2D.h>

class Rect : public QRectF {
public:
    Rect();
    Rect(const QPointF & topLeft, const QSizeF & size);
    Rect(const QPointF & topLeft, const QPointF & bottomRight);
    Rect(qreal x, qreal y, qreal width, qreal height);
    Rect(const QRectF & rect);
    Rect(const QRect & rect);
    Rect(const b2AABB & aabb);
    operator b2AABB() const;
};

Q_DECLARE_METATYPE(Rect)

#endif	/* _RECT_H */

