/* 
 * File:   Circle.h
 * Author: mark
 *
 * Created on September 13, 2009, 5:16 PM
 */

#ifndef _CIRCLE_H
#define	_CIRCLE_H

#include <Box2D/Box2D.h>
#include "Point.h"

class Circle {
public:
    Circle(Point p = Point(0,0), qreal r = 0);
    Circle(const b2CircleShape & circleShape);
    Point center() const;
    qreal radius() const;
    void setCenter(const Point& p);
    void setRadius(qreal r);
    operator b2CircleShape() const;
private:
    Point m_center;
    qreal m_radius;
};

Q_DECLARE_METATYPE(Circle)

#endif	/* _CIRCLE_H */

